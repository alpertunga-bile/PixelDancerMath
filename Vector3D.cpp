#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <iostream>
#include "include/Vector3D.h"

Vector3D::Vector3D()
{
	x = 0.0f; y = 0.0f; z = 0.0f;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

void Vector3D::Print(const char* name)
{
	std::cout << name << " (Vector3D) => x : " << x << " | y : " << y << " | z : " << z << '\n';
}

PXDMATH_API float& Vector3D::operator[](int i)
{
	float nullValue = 0.0f;

	if (i < 0 || i > 2)
	{
		return nullValue;
	}

	return ((&x)[i]);
}

const float& Vector3D::operator[](int i) const
{
	const float nullValue = 0.0f;

	if (i < 0 || i > 2)
	{
		return nullValue;
	}

	return ((&x)[i]);
}

Vector3D& Vector3D::operator*=(float s)
{
	x *= s; y *= s; z *= s;
	return (*this);
}

Vector3D& Vector3D::operator/=(float s)
{
	s = 1.0f / s;
	x *= s; y *= s; z *= s;
	return (*this);
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	x += v.x;
	y += v.x;
	z += v.z;
	return (*this);
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	x -= v.x;
	y -= v.x;
	z -= v.z;
	return (*this);
}

float Vector3D::Magnitude()
{
	return std::sqrtf(x * x + y * y + z * z);
}

void Vector3D::Normalize()
{
	(*this) /= (*this).Magnitude();
}
