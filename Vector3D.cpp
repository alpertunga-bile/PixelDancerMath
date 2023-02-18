#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <iostream>
#include "include/Vector3D.h"

Vector3D::Vector3D()
{
	x = 0.0f; y = 0.0f; z = 0.0f;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z;
	_vector = _mm256_set1_pd(0.0);
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
	x = _x; y = _y; z = _z;
	v_ptr[0] = x; v_ptr[1] = y; v_ptr[2] = z;
	_vector = _mm256_set_pd(0.0, z, y, x);
}

Vector3D::Vector3D(__m256d newVector)
{
	_vector = newVector;
	SetVariables();
}

void Vector3D::Print(const char* name)
{
	std::cout << name << " (Vector3D) => x : " << x << " | y : " << y << " | z : " << z << '\n';
}

PXDMATH_API double& Vector3D::operator[](int i)
{
	return (v_ptr[i]);
}

const double& Vector3D::operator[](int i) const
{
	return (v_ptr[i]);
}

Vector3D& Vector3D::operator*=(float s)
{
	__m256d temp = _mm256_set1_pd(s);
	_vector = _mm256_mul_pd(_vector, temp);
	SetVariables();
	return (*this);
}

Vector3D& Vector3D::operator/=(float s)
{
	__m256d temp = _mm256_set1_pd(1.0 / s);
	_vector = _mm256_mul_pd(_vector, temp);
	SetVariables();
	return (*this);
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	_vector = _mm256_add_pd(_vector, v._vector);
	SetVariables();
	return (*this);
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	_vector = _mm256_sub_pd(_vector, v._vector);
	SetVariables();
	return (*this);
}

double Vector3D::Magnitude()
{
	double tempPtr[4];
	__m256d temp = _mm256_set1_pd(x * x + y * y + z * z);
	_mm256_store_pd(tempPtr, _mm256_sqrt_pd(temp));
	return tempPtr[0];
}

void Vector3D::Normalize()
{
	if (Magnitude() == 0.0) return;

	_vector = _mm256_div_pd(_vector, _mm256_set1_pd(Magnitude()));
	SetVariables();
}

void Vector3D::SetVariables()
{
	double tempPtr[4];
	_mm256_store_pd(tempPtr, _vector);
	v_ptr[0] = tempPtr[0]; v_ptr[1] = tempPtr[1]; v_ptr[2] = tempPtr[2];
	x = v_ptr[0]; y = v_ptr[1]; z = v_ptr[2];
}
