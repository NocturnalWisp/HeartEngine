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

#include "heart/component.h"

namespace sol { class state; }

namespace HeartModules
{
//typedef std::pair<Vector3, float> RotationAxisAngle;
typedef struct RotationAxisAngle
{
    Vector3 axis;
    float   angle;
} RotationAxisAngle;

class Transform3D : public HeartEngine::Component
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
    Vector3 getLocalPosition() const;
    void setLocalPosition(Vector3 localPosition);
    // World.
    Vector3 getWorldPosition() const;

    // ROTATION PROPERTY.
    // Local.
    RotationAxisAngle getLocalRotation() const;
    void setLocalRotation(RotationAxisAngle rotation);
    // World.
    RotationAxisAngle getWorldRotation() const;

    // SCALE PROPERTY.
    // Local.
    Vector3 getLocalScale() const;
    void setLocalScale(Vector3 localScale);
    // World.
    Vector3 getWorldScale() const;

    // SPACE TRANSFORMATIONS.
    // Local to world space.
    Matrix getLocalToWorldMatrix() const;
    // World to local space.
    Matrix getWorldToLocalMatrix() const;

    static Vector3 extractTranslation(Matrix transform);
    static Matrix  extractRotation(Matrix transform);
    static Vector3 extractScale(Matrix transform);

    // HIERARCHY OPERATIONS.
    void setParent(Transform3D* newParent, unsigned int childIndex = 0);

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