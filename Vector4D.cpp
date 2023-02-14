#include "pch.h"
#include <iostream>
#include "include/Vector4D.h"

Vector4D::Vector4D()
{
	x = 0.0f; y = 0.0f; z = 0.0f, w = 0.0f;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
}

Vector4D::Vector4D(float _x, float _y, float _z, float _w)
{
	x = _x; y = _y; z = _z; w = _w;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
}

void Vector4D::Print(const char* name)
{
	std::cout << name << " (Vector4D) => x : " << x << " | y : " << y << " | z : " << z << " | w : " << w << '\n';
}

PXDMATH_API float& Vector4D::operator[](int i)
{
	return (v_ptr[i]);
}

const float& Vector4D::operator[](int i) const
{
	return (v_ptr[i]);
}

Vector4D& Vector4D::operator*=(float s)
{
	x *= s; y *= s; z *= s; w *= s;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
	return (*this);
}

Vector4D& Vector4D::operator/=(float s)
{
	s = 1.0f / s;
	x *= s; y *= s; z *= s; w *= s;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
	return (*this);
}

Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x;
	y += v.x;
	z += v.z;
	w += v.w;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
	return (*this);
}

Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x;
	y -= v.x;
	z -= v.z;
	w -= v.w;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z; v_ptr[3] = w;
	return (*this);
}

float Vector4D::Magnitude()
{
	return std::sqrtf(x * x + y * y + z * z + w * w);
}

void Vector4D::Normalize()
{
	(*this) /= Magnitude();
}