#include "module/raymath.h"

namespace HeartModules
{
void RayMath::SetupVector2(sol::state& lua)
{
    auto vec2Type = lua.new_usertype<Vector2>("Vector2");
    vec2Type[sol::call_constructor] = [](float x, float y) -> Vector2 { return {x, y}; };

    vec2Type["x"] = &Vector2::x;
    vec2Type["y"] = &Vector2::y;

    vec2Type[sol::meta_function::addition] = &Vector2Add;
    vec2Type["AddValue"] = &Vector2AddValue;
    vec2Type[sol::meta_function::subtraction] = &Vector2Subtract;
    vec2Type["SubValue"] = &Vector2SubtractValue;
    vec2Type[sol::meta_function::multiplication] = &Vector2Multiply;
    vec2Type["Scale"] = &Vector2Scale;
    vec2Type[sol::meta_function::division] = &Vector2Divide;

    vec2Type["Zero"] = Vector2Zero;
    vec2Type["One"] = &Vector2One;

    vec2Type["Angle"] = &Vector2Angle;
    vec2Type["Clamp"] = &Vector2Clamp;
    vec2Type["ClampValue"] = &Vector2ClampValue;
    vec2Type["Distance"] = &Vector2Distance;
    vec2Type["DistanceSquared"] = &Vector2DistanceSqr;
    vec2Type["Dot"] = &Vector2DotProduct;
    vec2Type[sol::meta_function::equal_to] = &Vector2Equals;
    vec2Type["Inverted"] =  &Vector2Invert;
    vec2Type["Length"] =  &Vector2Length;
    vec2Type["LengthSquared"] =  &Vector2LengthSqr;
    vec2Type["Lerp"] =  &Vector2Lerp;
    vec2Type["LineAngle"] = &Vector2LineAngle;
    vec2Type["MoveTowards"] = &Vector2MoveTowards;
    vec2Type["Negate"] =  &Vector2Negate;
    vec2Type["Normalized"] =  &Vector2Normalize;
    vec2Type["Reflect"] = &Vector2Reflect;
    vec2Type["Rotate"] = &Vector2Rotate;
    vec2Type["Transform"] =  &Vector2Transform;

    vec2Type[sol::meta_function::to_string] =
        [](Vector2& self) -> std::string { return std::string("(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ")" ); };
}
void RayMath::SetupVector3(sol::state& lua)
{
    auto vec3Type = lua.new_usertype<Vector3>("Vector3");
    vec3Type[sol::call_constructor] = [](float x, float y, float z) -> Vector3 { return {x, y, z}; };

    vec3Type["x"] = &Vector3::x;
    vec3Type["y"] = &Vector3::y;
    vec3Type["z"] = &Vector3::z;

    vec3Type[sol::meta_function::addition] = &Vector3Add;
    vec3Type["AddValue"] = &Vector3AddValue;
    vec3Type[sol::meta_function::subtraction] = &Vector3Subtract;
    vec3Type["SubValue"] = &Vector3SubtractValue;
    vec3Type[sol::meta_function::multiplication] = &Vector3Multiply;
    vec3Type["Scale"] = &Vector3Scale;
    vec3Type[sol::meta_function::division] = &Vector3Divide;

    vec3Type["Zero"] = &Vector3Zero;
    vec3Type["One"] = &Vector3One;

    vec3Type["Angle"] = &Vector3Angle;
    vec3Type["Clamp"] = &Vector3Clamp;
    vec3Type["ClampValue"] = &Vector3ClampValue;
    vec3Type["Distance"] = &Vector3Distance;
    vec3Type["DistanceSquared"] = &Vector3DistanceSqr;
    vec3Type["Cross"] = &Vector3CrossProduct;
    vec3Type["Dot"] = &Vector3DotProduct;
    vec3Type[sol::meta_function::equal_to] = &Vector3Equals;
    vec3Type["Inverted"] = &Vector3Invert;
    vec3Type["Length"] = &Vector3Length;
    vec3Type["LengthSquared"] = &Vector2LengthSqr;
    vec3Type["Lerp"] = &Vector3Lerp;
    vec3Type["Perpendicular"] = &Vector3Perpendicular;
    vec3Type["Negate"] = &Vector3Negate;
    vec3Type["Normalized"] = &Vector3Normalize;
    vec3Type["OrthoNormalized"] = &Vector3OrthoNormalize;
    vec3Type["Reflect"] = &Vector3Reflect;
    vec3Type["Refract"] = &Vector3Refract;
    vec3Type["Transform"] = &Vector3Transform;
    vec3Type["RotateByQuaternion"] = &Vector3RotateByQuaternion;
    vec3Type["RotateByAxisAngle"] = &Vector3RotateByAxisAngle;
    vec3Type["Min"] = &Vector3Min;
    vec3Type["Max"] = &Vector3Max;
    vec3Type["Barycenter"] = &Vector3Barycenter;
    vec3Type["Unproject"] = &Vector3Unproject;
    vec3Type["ToFloatV"] = &Vector3ToFloatV;

    vec3Type[sol::meta_function::to_string] =
        [](Vector3& self) -> std::string
        { return std::string("(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " + std::to_string(self.z) + ")" ); };
}
void RayMath::SetupMatrix(sol::state& lua)
{
    auto matrixType = lua.new_usertype<Matrix>("Matrix");
    matrixType[sol::call_constructor] = []() -> Matrix { return Matrix(); };

    matrixType["m0"] = &Matrix::m0;
    matrixType["m1"] = &Matrix::m1;
    matrixType["m2"] = &Matrix::m2;
    matrixType["m3"] = &Matrix::m3;
    matrixType["m4"] = &Matrix::m4;
    matrixType["m5"] = &Matrix::m5;
    matrixType["m6"] = &Matrix::m6;
    matrixType["m7"] = &Matrix::m7;
    matrixType["m8"] = &Matrix::m8;
    matrixType["m9"] = &Matrix::m9;
    matrixType["m10"] = &Matrix::m10;
    matrixType["m11"] = &Matrix::m11;
    matrixType["m12"] = &Matrix::m12;
    matrixType["m13"] = &Matrix::m13;
    matrixType["m14"] = &Matrix::m14;
    matrixType["m15"] = &Matrix::m15;

    matrixType[sol::meta_function::addition] = &MatrixAdd;
    matrixType[sol::meta_function::subtraction] = &MatrixSubtract;

    matrixType[sol::meta_function::multiplication] = &MatrixMultiply;

    matrixType["scale"] = &MatrixScale;
    matrixType["Determinant"] = &MatrixDeterminant;
    matrixType["Frustum"] = &MatrixFrustum;
    matrixType["Identity"] = &MatrixIdentity;
    matrixType["Invert"] = &MatrixInvert;
    matrixType["LookAt"] = &MatrixLookAt;
    matrixType["Ortho"] = &MatrixOrtho;
    matrixType["Perspective"] = &MatrixPerspective;
    matrixType["Rotate"] = &MatrixRotate;
    matrixType["RotateX"] = &MatrixRotateX;
    matrixType["RotateY"] = &MatrixRotateY;
    matrixType["RotateZ"] = &MatrixRotateZ;
    matrixType["RotateXYZ"] = &MatrixRotateXYZ;
    matrixType["RotateZYX"] = &MatrixRotateZYX;
    matrixType["Perspective"] = &MatrixPerspective;
    matrixType["FloatV"] = &MatrixToFloatV;
    matrixType["translate"] = &MatrixTranslate;
    matrixType["Transpose"] = &MatrixTranspose;
    matrixType["Trace"] = &MatrixTrace;

    matrixType[sol::meta_function::to_string] =
        [](Matrix& self) -> std::string
        { return std::string("(" +
            std::to_string(self.m0) + ", " +
            std::to_string(self.m1) + ", " +
            std::to_string(self.m2) + ", " +
            std::to_string(self.m3) + ",\n" +
            std::to_string(self.m4) + ", " +
            std::to_string(self.m5) + ", " +
            std::to_string(self.m6) + ", " +
            std::to_string(self.m7) + ",\n" +
            std::to_string(self.m8) + ", " +
            std::to_string(self.m9) + ", " +
            std::to_string(self.m10) + ", " +
            std::to_string(self.m11) + ",\n" +
            std::to_string(self.m12) + ", " +
            std::to_string(self.m13) + ", " +
            std::to_string(self.m14) + ", " +
            std::to_string(self.m15) + ")" ); };
}
void RayMath::SetupQuaternion(sol::state& lua)
{
    auto quaternionType = lua.new_usertype<Quaternion>("Quaternion");
    quaternionType["x"] = &Quaternion::x;
    quaternionType["y"] = &Quaternion::y;
    quaternionType["z"] = &Quaternion::z;
    quaternionType["w"] = &Quaternion::w;

    quaternionType[sol::meta_function::addition] = &QuaternionAdd;
    quaternionType["AddValue"] = &QuaternionAddValue;
    quaternionType[sol::meta_function::subtraction] = &QuaternionSubtract;
    quaternionType["SubValue"] = &QuaternionSubtractValue;
    quaternionType[sol::meta_function::multiplication] = &QuaternionMultiply;
    quaternionType["Scale"] = &QuaternionScale;
    quaternionType[sol::meta_function::division] = &QuaternionDivide;

    quaternionType["Identity"] = &QuaternionIdentity;
    quaternionType[sol::meta_function::equal_to] = &QuaternionEquals;
    quaternionType["Inverted"] = &QuaternionInvert;
    quaternionType["Length"] = &QuaternionLength;
    quaternionType["LengthSquared"] = &Vector2LengthSqr;
    quaternionType["Lerp"] = &QuaternionLerp;
    quaternionType["Nlerp"] = &QuaternionNlerp;
    quaternionType["Slerp"] = &QuaternionSlerp;
    quaternionType["Normalized"] = &QuaternionNormalize;
    quaternionType["Transform"] = &QuaternionTransform;

    quaternionType["FromToVector3"] = &QuaternionFromVector3ToVector3;
    quaternionType["FromMatrix"] = &QuaternionFromMatrix;
    quaternionType["FromAxisAngle"] = &QuaternionFromAxisAngle;
    quaternionType["FromEuler"] = &QuaternionFromEuler;
    quaternionType["ToEuler"] = &QuaternionToEuler;
    quaternionType["ToMatrix"] = &QuaternionToMatrix;
    quaternionType["ToAxisAngle"] = &QuaternionToAxisAngle;

    quaternionType[sol::meta_function::to_string] =
        [](Quaternion& self) -> std::string
        { return std::string("(" + std::to_string(self.x) + ", " + std::to_string(self.y) + ", " + std::to_string(self.z) + ", " + std::to_string(self.w) + ")" ); };
}
void RayMath::SetupOther(sol::state& lua)
{
    lua["deg2rad"] = DEG2RAD;
    lua["rad2deg"] = RAD2DEG;

    ADD_LUA_FUNCTION(lua, Clamp);
    ADD_LUA_FUNCTION(lua, Normalize);
    ADD_LUA_FUNCTION(lua, Remap);
    ADD_LUA_FUNCTION(lua, Wrap);
    ADD_LUA_FUNCTION(lua, FloatEquals);
}
}