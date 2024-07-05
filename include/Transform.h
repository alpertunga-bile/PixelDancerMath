#pragma once

struct Matrix3D;
struct Vector3D;

namespace pxd {
Matrix3D
MakeRotationX(double angle);

Matrix3D
MakeRotationY(double angle);

Matrix3D
MakeRotationZ(double angle);

Matrix3D
MakeRotation(const Vector3D& axis, double angle);

Matrix3D
MakeReflection(const Vector3D& axis);

Matrix3D
MakeInvolution(const Vector3D& axis);

Matrix3D
MakeScale(double sx, double sy, double sz);

Matrix3D
MakeScale(double scale, const Vector3D& v);

Matrix3D
MakeSkew(double angle, const Vector3D& dir, const Vector3D& height);
}
