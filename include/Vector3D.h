#pragma once

#include <cmath>

#ifdef PXDMATH_EXPORTS
#define PXDMATH_API __declspec(dllexport)
#else
#define PXDMATH_API __declspec(dllimport)
#endif

struct Vector3D
{
	// Rule of 5
	PXDMATH_API Vector3D(); // default constructor
	PXDMATH_API Vector3D(float _x, float _y, float _z); // special constructor
	PXDMATH_API Vector3D(const Vector3D& other) = default; // copy constructor
	PXDMATH_API Vector3D(Vector3D&& other) = default; // move constructor
	PXDMATH_API Vector3D& operator=(const Vector3D& other) = default; // move assignment
	PXDMATH_API ~Vector3D() = default; // deconstructor

	PXDMATH_API void Print(const char* name);

	// accessing variables with indicies
	PXDMATH_API float& operator[] (int i);
	PXDMATH_API const float& operator[](int i) const;

	// math operator overloads
	PXDMATH_API Vector3D& operator*=(float s);
	PXDMATH_API Vector3D& operator/=(float s);
	PXDMATH_API Vector3D& operator+=(const Vector3D& v);
	PXDMATH_API Vector3D& operator-=(const Vector3D& v);

	PXDMATH_API float Magnitude();
	PXDMATH_API void Normalize();

	float x, y, z;
};

inline Vector3D operator* (const Vector3D& v, float s)
{
	return Vector3D(v.x * s, v.y * s, v.z * s);
}

inline Vector3D operator/ (const Vector3D& v, float s)
{
	s = 1.0f / s;
	return Vector3D(v.x * s, v.y * s, v.z * s);
}

inline Vector3D operator- (const Vector3D& v)
{
	return Vector3D(-v.x, -v.y, -v.z);
}

inline Vector3D operator+(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3D operator-(const Vector3D& a, const Vector3D& b)
{
	return Vector3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline float Magnitude(const Vector3D& v)
{
	return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vector3D Normalize(const Vector3D& v)
{
	return (v / Magnitude(v));
}

inline float Dot(const Vector3D& a, const Vector3D& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
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