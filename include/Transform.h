#pragma once

#include "include/Matrix3D.h"

namespace pxd
{
	PXDMATH_API Matrix3D MakeRotationX(float angle);
	PXDMATH_API Matrix3D MakeRotationY(float angle);
	PXDMATH_API Matrix3D MakeRotationZ(float angle);
	PXDMATH_API Matrix3D MakeRotation(const Vector3D& axis, float angle);
	PXDMATH_API Matrix3D MakeReflection(const Vector3D& axis);
	PXDMATH_API Matrix3D MakeInvolution(const Vector3D& axis);
}
