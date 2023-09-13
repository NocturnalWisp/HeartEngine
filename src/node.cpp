#include "node.h"

const float EPSILON = 0.001;

void Node::destroy()
{
    onDestroy(*this);

    //TODO: engine->EarlyResourceReleaseCallback();
}

// // Transform
// Vector3 Node::getLocalPosition() const
// {
//     return position;
// }
// void Node::setLocalPosition(Vector3 localPosition)
// {
//     position = localPosition;
// }
// Vector3 Node::getWorldPosition() const
// {
//     Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);

//     return Extensions::extractTranslation(ltwMat);
// }

// RotationAxisAngle Node::getLocalRotation() const
// {
//     Vector3 rotationAxis = {0, 0, 0};
//     float rotationAngle = 0;
//     QuaternionToAxisAngle(rotation, &rotationAxis, &rotationAngle);
//     return { rotationAxis, rotationAngle * RAD2DEG };
// }
// void Node::setLocalRotation(RotationAxisAngle rotation)
// {
//     this->rotation = QuaternionFromAxisAngle(rotation.axis, rotation.angle * DEG2RAD);
// }
// RotationAxisAngle Node::getWorldRotation() const
// {
//     // Get transformation matrix.
//     Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);
//     Matrix rotationMatrix = Extensions::extractRotation(ltwMat);

//     // Check to see if rotation is non-zero.
//     float matrixAngle = acos((rotationMatrix.m0 + rotationMatrix.m5 + rotationMatrix.m10 - 1) / 2);
//     // If rotation is zero, do not proceed to quaternion conversion.
//     if (matrixAngle <= EPSILON && matrixAngle >= -EPSILON)
//     {
//         return { {0, 0, 0}, 0 };
//     }

//     // Get quaternion from matrix.
//     Quaternion rotationQuat = QuaternionFromMatrix(rotationMatrix);
//     if (isnan(rotationQuat.w) || isnan(rotationQuat.x) || isnan(rotationQuat.y) || isnan(rotationQuat.z))
//     {
//         throw std::runtime_error("Invalid quaternion created from rotation matrix!");
//     }
//     Vector3 rotationAxis = {0.0, 0.0, 0.0};
//     float rotationAngle = 0.0;
//     QuaternionToAxisAngle(rotationQuat, &rotationAxis, &rotationAngle);

//     return { rotationAxis, rotationAngle * RAD2DEG };
// }

// Vector3 Node::getLocalScale() const
// {
//     return scale;
// }
// void Node::setLocalScale(Vector3 localScale)
// {
//     scale = localScale;
// }
// Vector3 Node::getWorldScale() const
// {
//     // Get transformation matrix.
//     Matrix ltwMat = Extensions::getLocalToWorldMatrix(self);
//     // Extract world scale.
//     return Extensions::extractScale(ltwMat);
// }

// // Node Extensions
// Matrix Node::Extensions::makeLocalToParent(node_ptr node)
// {
//     if (auto node_ptr = node.lock())
//     {
//         auto scale = node_ptr->scale;
//         auto rotation = node_ptr->rotation;
//         auto position = node_ptr->position;
//         // Get matrices for transformation from local to parent.
//         Matrix scaleMatrix = MatrixScale(scale.x, scale.y, scale.z);
//         Matrix rotationMatrix = QuaternionToMatrix(QuaternionNormalize(rotation));
//         Matrix translationMatrix = MatrixTranslate(position.x, position.y, position.z);

//         // Order matters: scale -> rotation -> translation.
//         return MatrixMultiply(MatrixMultiply(scaleMatrix, rotationMatrix), translationMatrix);
//     }
//     return MatrixIdentity();
// }
// Matrix Node::Extensions::makeParentToLocal(node_ptr node)
// {
//     return MatrixInvert(makeLocalToParent(node));
// }

// Matrix Node::Extensions::getLocalToWorldMatrix(node_ptr node)
// {
//     if (auto node_ptr = node.lock())
//     {
//         if (auto parent_ptr = node_ptr->parent.lock())
//         {
//             // Get parent matrix.
//             Matrix parentMatrix = getLocalToWorldMatrix(node_ptr->parent);
//             Matrix childMatrix = makeLocalToParent(node);
//             // Multiply matrices.
//             return MatrixMultiply(childMatrix, parentMatrix);
//         }

//         return makeLocalToParent(node);
//     }
//     else
//     {
//         // Base case: root node.
//         return MatrixIdentity();
//     }
// }
// Matrix Node::Extensions::getWorldToLocalMatrix(node_ptr node)
// {
//     return MatrixInvert(getLocalToWorldMatrix(node));
// }

// Vector3 Node::Extensions::extractTranslation(Matrix transform)
// {
//     float position_x = transform.m12;
//     float position_y = transform.m13;
//     float position_z = transform.m14;
//     return { position_x, position_y, position_z };
// }
// Matrix Node::Extensions::extractRotation(Matrix transform)
// {
//     // Extract scale.
//     Vector3 scale = extractScale(transform);
//     // Extract rotation matrix.
//     return {
//         transform.m0 / scale.x, transform.m4 / scale.y, transform.m8 / scale.z,  0.0f,
//         transform.m1 / scale.x, transform.m5 / scale.y, transform.m9 / scale.z,  0.0f,
//         transform.m2 / scale.x, transform.m6 / scale.y, transform.m10 / scale.z, 0.0f,
//         0.0f,                0.0f,                0.0f,                 1.0f
//     };
// }
// Vector3 Node::Extensions::extractScale(Matrix transform)
// {
//     float scale_x = Vector3Length({ transform.m0, transform.m1, transform.m2 });
//     float scale_y = Vector3Length({ transform.m4, transform.m5, transform.m6 });
//     float scale_z = Vector3Length({ transform.m8, transform.m9, transform.m10 });
//     return {
//         scale_x,
//         scale_y,
//         scale_z
//     };
// }