#pragma once

#include "Matrix3D.h"

namespace pxd {
Matrix3D
MakeRotationX(float angle);
Matrix3D
MakeRotationY(float angle);
Matrix3D
MakeRotationZ(float angle);
Matrix3D
MakeRotation(const Vector3D& axis, float angle);
Matrix3D
MakeReflection(const Vector3D& axis);
Matrix3D
MakeInvolution(const Vector3D& axis);
Matrix3D
MakeScale(float sx, float sy, float sz);
Matrix3D
MakeScale(float scale, const Vector3D& v);
Matrix3D
MakeSkew(float angle, const Vector3D& dir, const Vector3D& height);
}
