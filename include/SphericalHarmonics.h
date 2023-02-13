#pragma once

#include "Vector3D.h"
#include <vector>

struct SHSample
{
	Vector3D sh;
	Vector3D vec;
	std::vector<double> coefficient;
};

class SphericalHarmonics
{
public:
	// Rule of 5
	PXDMATH_API SphericalHarmonics(); // default constructor
	// countSample must be sqrt of the desired total sample
	PXDMATH_API SphericalHarmonics(int countSample, int nBands); // special constructor
	PXDMATH_API SphericalHarmonics(const SphericalHarmonics& other) = default; // copy constructor
	PXDMATH_API SphericalHarmonics(SphericalHarmonics&& other) = default; // move constructor
	PXDMATH_API SphericalHarmonics& operator=(const SphericalHarmonics& other) = default; // move assignment
	PXDMATH_API ~SphericalHarmonics() = default; // deconstructor

	PXDMATH_API void Print();
	// Calculate with different samples and nBands
	PXDMATH_API void ReCalculate(int _countSamples, int _nBands);

	PXDMATH_API inline std::vector<SHSample> GetSamples() { return samples; }

private:
	PXDMATH_API void Setup();
	void PreCalculateFactorials();
	float Factorial(int n);

	// associeated legendre polynomial at x | P
	double GetLegendrePolynomialValue(int l, int m, double x);
	// scaling factor to normalize the function | K 
	double GetScalingFactor(int l, int m);
	double SH(int l, int m, double theta, double phi);

private:
	std::vector<SHSample> samples;
	int nBands;
	int countOfSamples;
	float factorials[34] = { 0.0 };
};
