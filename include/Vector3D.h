#pragma once

#include <cmath>

#ifdef __AVX__
#include <immintrin.h>
#else
std::cout << "AVX is not supported! You have to have AVX compatibility to compile";
exit(0);
#endif

#ifdef PXDMATH_EXPORTS
#define PXDMATH_API __declspec(dllexport)
#else
#define PXDMATH_API __declspec(dllimport)
#endif

class Vector3D
{
public:
	// Rule of 5
	PXDMATH_API Vector3D(); // default constructor
	PXDMATH_API Vector3D(double _x, double _y, double _z); // special constructor
	PXDMATH_API Vector3D(__m256d newVector);
	PXDMATH_API Vector3D(const Vector3D& other) = default; // copy constructor
	PXDMATH_API Vector3D(Vector3D&& other) = default; // move constructor
	PXDMATH_API Vector3D& operator=(const Vector3D& other) = default; // move assignment
	PXDMATH_API ~Vector3D() = default; // deconstructor

	PXDMATH_API void Print(const char* name);

	// accessing variables with indicies
	PXDMATH_API double& operator[] (int i);
	PXDMATH_API const double& operator[](int i) const;

	// math operator overloads
	PXDMATH_API Vector3D& operator*=(float s);
	PXDMATH_API Vector3D& operator/=(float s);
	PXDMATH_API Vector3D& operator+=(const Vector3D& v);
	PXDMATH_API Vector3D& operator-=(const Vector3D& v);

	PXDMATH_API double Magnitude();
	PXDMATH_API void Normalize();

	double x, y, z;
	double v_ptr[3];
	__m256d _vector;

private:
	void SetVariables();
};

inline Vector3D operator* (const Vector3D& v, double s)
{
	return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(s)));
}

inline Vector3D operator/ (const Vector3D& v, double s)
{
	return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(1.0 / s)));
}

inline Vector3D operator- (const Vector3D& v)
{
	return Vector3D(_mm256_mul_pd(v._vector, _mm256_set1_pd(-1.0)));
}

inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(_mm256_add_pd(a._vector, b._vector));
}

inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(_mm256_sub_pd(a._vector, b._vector));
}

inline double Magnitude(const Vector3D& v)
{
	double tempPtr[4];
	__m256d temp = _mm256_set1_pd(v.x * v.x + v.y * v.y + v.z * v.z);
	_mm256_store_pd(tempPtr, _mm256_sqrt_pd(temp));
	return tempPtr[0];
}

inline Vector3D Normalize(const Vector3D& v)
{
	return (v / Magnitude(v));
}

inline float Dot(const Vector3D& a, const Vector3D& b)
{
	double tempPtr[4];
	__m256d xy = _mm256_mul_pd(a._vector, b._vector);
	__m256d temp = _mm256_hadd_pd(xy, xy);
	_mm256_store_pd(tempPtr, temp);
	return tempPtr[0] + tempPtr[2];
}

inline Vector3D Cross(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

inline Vector3D Project(const Vector3D& a, const Vector3D& b)
{
	return (b * (Dot(a, b) / Dot(b, b)));
}

inline Vector3D Reject(const Vector3D& a, const Vector3D& b)
{
	return (a - b * (Dot(a, b) / Dot(b, b)));
}