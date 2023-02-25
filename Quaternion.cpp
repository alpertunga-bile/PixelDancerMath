#include "pch.h"
#include "include/Quaternion.h"

Quaternion::Quaternion(double a, double b, double c, double d)
{
	v = Vector3D(a, b, c); w = d;
}

Quaternion::Quaternion(const Vector3D& _v, double s)
{
	v = _v; w = s;
}
