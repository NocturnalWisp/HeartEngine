#include "../include/node.h"

const float EPSILON = 0.001;

node_ptr Node::getNode(const char* path) const
{
    std::vector<std::string> tokens = std::vector<std::string>();

    std::string current {""};

    const char* c = &path[0];
    while (*c != '\0')
    {
        bool nextIsEnd = *(c+1) == '\0';
        if (*c == '/' || nextIsEnd)
        {
            if (nextIsEnd && *c != '/')
            {
                current.push_back(*c);
            }
            
            if (current != "")
            {
                tokens.push_back(current);
                current = {""};
            }
        }
        else
        {
            current.push_back(*c);
        }

        ++c;
    }

    node_ptr currentNode;
    // Determine starting node.
    if (tokens[0] == "root")
    {
        currentNode = root;
        tokens.erase(tokens.begin());
    }
    else
    {
        currentNode = self;
    }

    // Follow token path.
    for (std::string& token : tokens)
    {
        currentNode = getNodeByToken(currentNode, token);

        if (currentNode.expired())
        {
            // Break early and the function will return the expired pointer.
            Debug::printerr("Invalid token in getNode, fix path. (" + token + ")");
            break;
        }
    }

    return currentNode;
}

void Node::addChild(node_ptr child)
{
    if (auto child_ptr = child.lock())
    {
        // Remove this child from current parent.
        child_ptr->removeParent();

        // Add as child to this.
        children.push_back(child_ptr);

        // Set parent to new parent.
        child_ptr->parent = self;
    }
    else
    {
        Debug::printerr("Couldn't add invalid child.");
    }
}

void Node::destroy()
{
    if (auto self_ptr = self.lock())
    {
        runRemove(self_ptr);
    }

    EarlyResourceReleaseCallback();
}

node_ptr Node::getNodeByToken(node_ptr currentNode, std::string& token) const
{
    if (auto currentNode_ptr = currentNode.lock())
    {
        if (token == "..")
        {
            return currentNode_ptr->parent;
        }
        else
        {
            // Loop through children to find by name.
            for (auto child : currentNode_ptr->children)
            {
                if (child->name == token)
                {
                    return child;
                }
            }
        }
    }

    return node_ptr();
}

void Node::removeParent()
{
    if (auto parent_ptr = parent.lock())
    {
        auto captureName = name;
        auto at = std::remove_if(parent_ptr->children.begin(),
                                        parent_ptr->children.end(),
                                        [captureName](const shared_node_ptr& node) {
                                            return node->name.compare(captureName) == 0;
                                        });

        parent_ptr->children.erase(at);

        parent = node_ptr();
    }
}

// Transform
Vector3 Node::getLocalPosition() const
{
    return position;
}
void Node::setLocalPosition(Vector3 localPosition)
{
    position = localPosition;
}
Vector3 Node::getWorldPosition() const
{
    Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);

    return Extensions::extractTranslation(ltwMat);
}

RotationAxisAngle Node::getLocalRotation() const
{
    Vector3 rotationAxis = {0, 0, 0};
    float rotationAngle = 0;
    QuaternionToAxisAngle(rotation, &rotationAxis, &rotationAngle);
    return { rotationAxis, rotationAngle * RAD2DEG };
}
void Node::setLocalRotation(RotationAxisAngle rotation)
{
    this->rotation = QuaternionFromAxisAngle(rotation.axis, rotation.angle * DEG2RAD);
}
RotationAxisAngle Node::getWorldRotation() const
{
    // Get transformation matrix.
    Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);
    Matrix rotationMatrix = Extensions::extractRotation(ltwMat);

    // Check to see if rotation is non-zero.
    float matrixAngle = acos((rotationMatrix.m0 + rotationMatrix.m5 + rotationMatrix.m10 - 1) / 2);
    // If rotation is zero, do not proceed to quaternion conversion.
    if (matrixAngle <= EPSILON && matrixAngle >= -EPSILON)
    {
        return { {0, 0, 0}, 0 };
    }

    // Get quaternion from matrix.
    Quaternion rotationQuat = QuaternionFromMatrix(rotationMatrix);
    if (isnan(rotationQuat.w) || isnan(rotationQuat.x) || isnan(rotationQuat.y) || isnan(rotationQuat.z))
    {
        throw std::runtime_error("Invalid quaternion created from rotation matrix!");
    }
    Vector3 rotationAxis = {0.0, 0.0, 0.0};
    float rotationAngle = 0.0;
    QuaternionToAxisAngle(rotationQuat, &rotationAxis, &rotationAngle);

    return { rotationAxis, rotationAngle * RAD2DEG };
}

Vector3 Node::getLocalScale() const
{
    return scale;
}
void Node::setLocalScale(Vector3 localScale)
{
    scale = localScale;
}
Vector3 Node::getWorldScale() const
{
    // Get transformation matrix.
    Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);
    // Extract world scale.
    return Extensions::extractScale(ltwMat);
}

// Node Extensions
Matrix Node::Extensions::makeLocalToParent(node_ptr node)
{
    if (auto node_ptr = node.lock())
    {
        auto scale = node_ptr->scale;
        auto rotation = node_ptr->rotation;
        auto position = node_ptr->position;
        // Get matrices for transformation from local to parent.
        Matrix scaleMatrix = MatrixScale(scale.x, scale.y, scale.z);
        Matrix rotationMatrix = QuaternionToMatrix(QuaternionNormalize(rotation));
        Matrix translationMatrix = MatrixTranslate(position.x, position.y, position.z);

        // Order matters: scale -> rotation -> translation.
        return MatrixMultiply(MatrixMultiply(scaleMatrix, rotationMatrix), translationMatrix);
    }
    return MatrixIdentity();
}
Matrix Node::Extensions::makeParentToLocal(node_ptr node)
{
    return MatrixInvert(makeLocalToParent(node));
}

Matrix Node::Extensions::getLocalToWorldMatrix(node_ptr node)
{
    if (auto node_ptr = node.lock())
    {
        if (auto parent_ptr = node_ptr->parent.lock())
        {
            // Get parent matrix.
            Matrix parentMatrix = getLocalToWorldMatrix(node_ptr->parent);
            Matrix childMatrix = makeLocalToParent(node);
            // Multiply matrices.
            return MatrixMultiply(childMatrix, parentMatrix);
        }

        return makeLocalToParent(node);
    }
    else
    {
        // Base case: root node.
        return MatrixIdentity();
    }
}
Matrix Node::Extensions::getWorldToLocalMatrix(node_ptr node)
{
    return MatrixInvert(getLocalToWorldMatrix(node));
}

Vector3 Node::Extensions::extractTranslation(Matrix transform)
{
    float position_x = transform.m12;
    float position_y = transform.m13;
    float position_z = transform.m14;
    return { position_x, position_y, position_z };
}
Matrix Node::Extensions::extractRotation(Matrix transform)
{
    // Extract scale.
    Vector3 scale = extractScale(transform);
    // Extract rotation matrix.
    return {
        transform.m0 / scale.x, transform.m4 / scale.y, transform.m8 / scale.z,  0.0f,
        transform.m1 / scale.x, transform.m5 / scale.y, transform.m9 / scale.z,  0.0f,
        transform.m2 / scale.x, transform.m6 / scale.y, transform.m10 / scale.z, 0.0f,
        0.0f,                0.0f,                0.0f,                 1.0f
    };
}
Vector3 Node::Extensions::extractScale(Matrix transform)
{
    float scale_x = Vector3Length({ transform.m0, transform.m1, transform.m2 });
    float scale_y = Vector3Length({ transform.m4, transform.m5, transform.m6 });
    float scale_z = Vector3Length({ transform.m8, transform.m9, transform.m10 });
    return {
        scale_x,
        scale_y,
        scale_z
    };
}