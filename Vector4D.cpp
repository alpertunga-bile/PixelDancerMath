#include "pch.h"
#include <iostream>
#include "include/Vector4D.h"

Vector4D::Vector4D()
{
	x = 0.0f; y = 0.0f; z = 0.0f, w = 0.0f;
}

Vector4D::Vector4D(float _x, float _y, float _z, float _w)
{
	x = _x; y = _y; z = _z; w = _w;
}

void Vector4D::Print(const char* name)
{
	std::cout << name << " (Vector4D) => x : " << x << " | y : " << y << " | z : " << z << " | w : " << w << '\n';
}

PXDMATH_API float& Vector4D::operator[](int i)
{
	return ((&x)[i]);
}

const float& Vector4D::operator[](int i) const
{
	return ((&x)[i]);
}

Vector4D& Vector4D::operator*=(float s)
{
	x *= s; y *= s; z *= s; w *= s;
	return (*this);
}

Vector4D& Vector4D::operator/=(float s)
{
	s = 1.0f / s;
	x *= s; y *= s; z *= s; w *= s;
	return (*this);
}

Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x;
	y += v.x;
	z += v.z;
	w += v.w;
	return (*this);
}

Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x;
	y -= v.x;
	z -= v.z;
	w -= v.w;
	return (*this);
}

float Vector4D::Magnitude()
{
	return std::sqrtf(x * x + y * y + z * z + w * w);
}

void Vector4D::Normalize()
{
	(*this) /= (*this).Magnitude();
}