/*******************************************************************************************
*
*   GameTransform.cpp
*   Implementation of a GameTransform component. Gives an object a position, rotation,
*   and scale in world and local space.
*   
*   Partially inspired by http://graphics.cs.cmu.edu/courses/15-466-f17/notes/hierarchy.html.
*   Matrix decomposition from https://math.stackexchange.com/questions/237369/.
*
*   LICENSE: GPLv3
*
*   Copyright (c) 2021 Juniper Dusk (@juniper-dusk)
*
*******************************************************************************************/

#include "components/game_transform.h"

#include <sol.hpp>

void GameTransform::populateLuaData()
{
    auto type = CREATEUSERTYPE(GameTransform);

    type["position"] = &GameTransform::position;
}

Matrix QuatToMat(Quaternion q)
{
    Matrix result = MatrixIdentity();

    float a2 = 2*(q.x*q.x), b2=2*(q.y*q.y), c2=2*(q.z*q.z); //, d2=2*(q.w*q.w);

    float ab = 2*(q.x*q.y), ac=2*(q.x*q.z), bc=2*(q.y*q.z);
    float ad = 2*(q.x*q.w), bd=2*(q.y*q.w), cd=2*(q.z*q.w);

    result.m0 = 1 - b2 - c2;
    result.m1 = ab + cd;
    result.m2 = ac - bd;

    result.m4 = ab - cd;
    result.m5 = 1 - a2 - c2;
    result.m6 = bc + ad;

    result.m8 = ac + bd;
    result.m9 = bc - ad;
    result.m10 = 1 - a2 - b2;

    return result;
}

const float EPSILON = 0.001;

GameTransform::GameTransform(std::string name) : Component(name)
{
    // Zero out data, exists at (0, 0, 0) world space.
    SetLocalPosition({0, 0, 0});
    SetLocalRotation({ {0, 0, 0}, 0 });
    SetLocalScale({1, 1, 1});
    // Root node.
    parent = nullptr;
}

//TODO: Move the following two to utility header somewhere.
Vector3 tableToVector3(const std::vector<float>& table)
{
    Vector3 result;
    result.x = table[0];
    result.y = table[1];
    result.z = table[2];
    return result;
}

RotationAxisAngle tableToRotationAxisAngle(const std::vector<float>& table)
{
    RotationAxisAngle result;
    result.axis.x = table[0];
    result.axis.y = table[1];
    result.axis.z = table[2];
    result.angle = table[3];
    return result;
}

GameTransform::GameTransform(std::string name, sol::variadic_args args) : Component(name)
{
    //TODO: seg fault if bad table given.
    // Zero out data, exists at (0, 0, 0) world space.
    if (args.size() > 0)
        SetLocalPosition(tableToVector3(args[0].as<std::vector<float>>()));
    if (args.size() > 1)
        SetLocalRotation(tableToRotationAxisAngle(args[1].as<std::vector<float>>()));
    if (args.size() > 2)
        SetLocalScale(tableToVector3(args[2].as<std::vector<float>>()));
    
    Debug::print(position.y);
    // Root node.
    parent = nullptr;
}

GameTransform::GameTransform(
    std::string name,
    Vector3 localPosition,
    RotationAxisAngle localRotation,
    Vector3 localScale) : Component(name)
{
    SetLocalPosition(localPosition);
    SetLocalRotation(localRotation);
    SetLocalScale(localScale);
    // Root node.
    parent = nullptr;
}

GameTransform::~GameTransform()
{
    // Remove dangling pointers from children and parent.
    for (GameTransform* child: children)
    {
        child->SetParent(nullptr);
    }
    if (parent)
    {
        this->SetParent(nullptr);
    }
}

Vector3 GameTransform::GetLocalPosition() const
{
    return position;
}

void GameTransform::SetLocalPosition(Vector3 localPosition)
{
    position = localPosition;
}

Vector3 GameTransform::GetWorldPosition() const
{
    // Get transformation matrix.
    Matrix ltwMat = GetLocalToWorldMatrix();
    // Extract translation.
    return ExtractTranslation(ltwMat);
}

RotationAxisAngle GameTransform::GetLocalRotation() const
{
    Vector3 rotationAxis = {0, 0, 0};
    float rotationAngle = 0;
    QuaternionToAxisAngle(rotation, &rotationAxis, &rotationAngle);
    return { rotationAxis, rotationAngle * RAD2DEG };
}

void GameTransform::SetLocalRotation(RotationAxisAngle rotation)
{
    this->rotation = QuaternionFromAxisAngle(rotation.axis, rotation.angle * DEG2RAD);
}

RotationAxisAngle GameTransform::GetWorldRotation() const
{
    // Get transformation matrix.
    Matrix ltwMat = GetLocalToWorldMatrix();
    Matrix rotationMatrix = ExtractRotation(ltwMat);

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

Vector3 GameTransform::GetLocalScale() const
{
    return scale;
}

void GameTransform::SetLocalScale(Vector3 localScale)
{
    scale = localScale;
}

Vector3 GameTransform::GetWorldScale() const
{
    // Get transformation matrix.
    Matrix ltwMat = GetLocalToWorldMatrix();
    // Extract world scale.
    return ExtractScale(ltwMat);
}

Matrix GameTransform::GetLocalToWorldMatrix() const
{
    if (parent)
    {
        // Get parent matrix.
        Matrix parentMatrix = parent->GetLocalToWorldMatrix();
        Matrix childMatrix = MakeLocalToParent();
        // Multiply matrices.
        return MatrixMultiply(childMatrix, parentMatrix);
    }
    else
    {
        // Base case: root node.
        return MakeLocalToParent();
    }
}

Matrix GameTransform::GetWorldToLocalMatrix() const
{
    return MatrixInvert(GetLocalToWorldMatrix());
}

Matrix GameTransform::MakeLocalToParent() const
{
    // Get matrices for transformation from local to parent.
    Matrix scaleMatrix = MatrixScale(scale.x, scale.y, scale.z);
    Matrix rotationMatrix = QuaternionToMatrix(QuaternionNormalize(rotation));
    Matrix translationMatrix = MatrixTranslate(position.x, position.y, position.z);

    // Order matters: scale -> rotation -> translation.
    return MatrixMultiply(MatrixMultiply(scaleMatrix, rotationMatrix), translationMatrix);
}

Matrix GameTransform::MakeParentToLocal() const
{
    return MatrixInvert(MakeLocalToParent());
}

Vector3 GameTransform::ExtractTranslation(Matrix transform)
{
    float position_x = transform.m12;
    float position_y = transform.m13;
    float position_z = transform.m14;
    return { position_x, position_y, position_z };
}

Matrix GameTransform::ExtractRotation(Matrix transform)
{
    // Extract scale.
    Vector3 scale = ExtractScale(transform);
    // Extract rotation matrix.
    return {
        transform.m0 / scale.x, transform.m4 / scale.y, transform.m8 / scale.z,  0.0f,
        transform.m1 / scale.x, transform.m5 / scale.y, transform.m9 / scale.z,  0.0f,
        transform.m2 / scale.x, transform.m6 / scale.y, transform.m10 / scale.z, 0.0f,
        0.0f,                0.0f,                0.0f,                 1.0f
    };
}

Vector3 GameTransform::ExtractScale(Matrix transform)
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

void GameTransform::SetParent(GameTransform* newParent, unsigned int childIndex)
{
    if (parent)
    {
        // Remove pointer to current node from parent.
        parent->children.remove(this);
    }
    // Update pointer.
    parent = newParent;
    if (parent)
    {
        // Insert pointer to current node at given index in parent's children.
        auto iterator = children.begin();
        std::advance(iterator, childIndex);
        parent->children.insert(iterator, this);
    }
}