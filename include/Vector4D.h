#pragma once

#include <cmath>

#ifdef PXDMATH_EXPORTS
#define PXDMATH_API __declspec(dllexport)
#else
#define PXDMATH_API __declspec(dllimport)
#endif

struct Vector4D
{
	// Rule of 5
	PXDMATH_API Vector4D(); // default constructor
	PXDMATH_API Vector4D(float _x, float _y, float _z, float _w); // special constructor
	PXDMATH_API Vector4D(const Vector4D& other) = default; // copy constructor
	PXDMATH_API Vector4D(Vector4D&& other) = default; // move constructor
	PXDMATH_API Vector4D& operator=(const Vector4D& other) = default; // move assignment
	PXDMATH_API ~Vector4D() = default; // deconstructor

	PXDMATH_API void Print(const char* name);

	// accessing variables with indicies
	PXDMATH_API float& operator[] (int i);
	PXDMATH_API const float& operator[](int i) const;

	// math operator overloads
	PXDMATH_API Vector4D& operator*=(float s);
	PXDMATH_API Vector4D& operator/=(float s);
	PXDMATH_API Vector4D& operator+=(const Vector4D& v);
	PXDMATH_API Vector4D& operator-=(const Vector4D& v);

	PXDMATH_API float Magnitude();
	PXDMATH_API void Normalize();

	float x, y, z, w;
	float v_ptr[4];
};

inline Vector4D operator* (const Vector4D& v, float s)
{
	return Vector4D(v.x * s, v.y * s, v.z * s, v.w * s);
}

inline Vector4D operator/ (const Vector4D& v, float s)
{
	s = 1.0f / s;
	return Vector4D(v.x * s, v.y * s, v.z * s, v.w * s);
}

inline Vector4D operator- (const Vector4D& v)
{
	return Vector4D(-v.x, -v.y, -v.z, -v.w);
}

inline Vector4D operator+(const Vector4D& a, const Vector4D& b)
{
	return Vector4D(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline Vector4D operator-(const Vector4D& a, const Vector4D& b)
{
	return Vector4D(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline float Magnitude(const Vector4D& v)
{
	return std::sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

inline Vector4D Normalize(const Vector4D& v)
{
	return (v / Magnitude(v));
}

inline float Dot(const Vector4D& a, const Vector4D& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vector4D Project(const Vector4D& a, const Vector4D& b)
{
	return (b * (Dot(a, b) / Dot(b, b)));
}

inline Vector4D Reject(const Vector4D& a, const Vector4D& b)
{
	return (a - b * (Dot(a, b) / Dot(b, b)));
}
