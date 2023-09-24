/*******************************************************************************************
*
*   Transform3D.h
*   Definition of a Transform3D component. Gives an object a position, rotation,
*   and scale in world and local space. Rotation is get/set by euler angles, but uses
*   quaternions under the hood to avoid gimbal lock and other problems.
*
*   Partially inspired by http://graphics.cs.cmu.edu/courses/15-466-f17/notes/hierarchy.html
*
*   LICENSE: GPLv3
*
*   Copyright (c) 2021 Juniper Dusk (@juniper-dusk)
*
*******************************************************************************************/

#pragma once

#include <list>
#include <memory>
#include <utility>
#include <iostream>
#include <string>

#include <raylib-cpp.hpp>

#include "component.h"

namespace sol { class state; }

namespace HeartEngine
{
//typedef std::pair<Vector3, float> RotationAxisAngle;
typedef struct RotationAxisAngle
{
    Vector3 axis;
    float   angle;
} RotationAxisAngle;

class Transform3D : public Component
{
public:
    void populateLuaData() override;

    // INITIALIZATION.
    // Default constructor.
    Transform3D(std::string name);
    Transform3D(std::string name, sol::variadic_args va);
    // Verbose constructor in local space.
    Transform3D(std::string name, Vector3 localPosition, RotationAxisAngle rotation, Vector3 localScale);
    // Default destructor.
    virtual ~Transform3D();

    // POSITION PROPERTY.
    // Local.
    Vector3 GetLocalPosition() const;
    void SetLocalPosition(Vector3 localPosition);
    // World.
    Vector3 GetWorldPosition() const;

    // ROTATION PROPERTY.
    // Local.
    RotationAxisAngle GetLocalRotation() const;
    void SetLocalRotation(RotationAxisAngle rotation);
    // World.
    RotationAxisAngle GetWorldRotation() const;

    // SCALE PROPERTY.
    // Local.
    Vector3 GetLocalScale() const;
    void SetLocalScale(Vector3 localScale);
    // World.
    Vector3 GetWorldScale() const;

    // SPACE TRANSFORMATIONS.
    // Local to world space.
    Matrix GetLocalToWorldMatrix() const;
    // World to local space.
    Matrix GetWorldToLocalMatrix() const;

    static Vector3 ExtractTranslation(Matrix transform);
    static Matrix  ExtractRotation(Matrix transform);
    static Vector3 ExtractScale(Matrix transform);

    // HIERARCHY OPERATIONS.
    void SetParent(Transform3D* newParent, unsigned int childIndex = 0);

protected:
    // Parent transform.
    Transform3D* parent;
    // Child transforms.
    std::list<Transform3D*> children;

    // (X, Y, Z) coordinates of position.
    Vector3 position = {0, 0, 0};
    // (W, X, Y, Z) quaternion describing rotation.
    Quaternion rotation = {0, 0, 0, 1};
    // (X, Y, Z) scalar amounts.
    Vector3 scale = {1, 1, 1};
    // Used as rotation axis.
    Vector3 origin = {0, 0, 0};

    // Matrices.
    Matrix MakeLocalToParent() const;
    Matrix MakeParentToLocal() const;
};
}