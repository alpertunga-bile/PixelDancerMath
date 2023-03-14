#include "pch.h"
#include "include/SphericalHarmonics.h"
#include "include/ConstantValues.h"

#include <random>
#include <string>


SphericalHarmonics::SphericalHarmonics()
{
	PreCalculateFactorials();
}

SphericalHarmonics::SphericalHarmonics(int countSample, int nBands)
{
	samples.resize(countSample * countSample);
	this->countOfSamples = countSample;
	this->nBands = nBands;
	PreCalculateFactorials();
	Setup();
}

void SphericalHarmonics::Setup()
{
	const int size = countOfSamples;
	int index = 0;
	double oneOverSamples = 1.0 / (countOfSamples * countOfSamples);

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<std::mt19937::result_type> randGen(0, countOfSamples * countOfSamples - 10);

	for (int a = 0; a < size; a++)
	{
		for (int b = 0; b < size; b++)
		{
			double x = (a + randGen(generator)) * oneOverSamples;
			double y = (b + randGen(generator)) * oneOverSamples;

			x = x < 0.0 ? 0.0 : x;
			x = x > 1.0 ? 1.0 : x;
			y = y < 0.0 ? 0.0 : x;
			y = y > 1.0 ? 1.0 : y;

			double theta = 2.0 * acos(sqrt(1.0 - x));
			double phi = 2.0 * PI * y;

			samples[index].sh = Vector3D(theta, phi, 1.0);
			// spherical coords to cartesian coordinate
			samples[index].vec = Vector3D(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
			samples[index].coefficient.resize(nBands * nBands);

			for (int l = 0; l < nBands; l++)
			{
				for (int m = -l; m <= l; m++)
				{
					int coefIndex = l * (l + 1) + m;
					samples[index].coefficient[coefIndex] = SH(l, m, theta, phi);
				}
			}

			index++;
		}
	}
}

void SphericalHarmonics::Print()
{
	const int totalSize = countOfSamples * countOfSamples;

	for (int i = 0; i < totalSize; i++)
	{
		printf("\n> %d -----------------------------------------\n", i);
		samples[i].sh.Print("Sphere Coordinates");
		samples[i].vec.Print("Cartesian Coordinate");
		
		int coSize = samples[i].coefficient.size();
		for (int j = 0; j < coSize; j++)
		{
			printf("%.5f ", samples[i].coefficient[j]);
		}
	}
}

void SphericalHarmonics::ReCalculate(int _countSamples, int _nBands)
{
	samples.clear();
	samples.resize(_countSamples * _countSamples);
	countOfSamples = _countSamples;
	nBands = _nBands;
	Setup();
}

std::vector<float> SphericalHarmonics::GetCoefficients(float a, float b, int nBands)
{
	std::vector<float> coeffs(nBands * nBands);

	double theta = 2.0 * acos(sqrt(1.0 - a));
	double phi = 2.0 * PI * b;

	for (int l = 0; l < nBands; l++)
	{
		for (int m = -l; m <= l; m++)
		{
			int coefIndex = l * (l + 1) + m;
			coeffs[coefIndex] = SH(l, m, theta, phi);
		}
	}

	return coeffs;
}

void SphericalHarmonics::PreCalculateFactorials()
{
	for (int i = 0; i < 34; i++)
	{
		factorials[i] = Factorial(i);
	}
}

float SphericalHarmonics::Factorial(int n)
{
	if (n == 1 || n == 0) return 1.0f;
	
	return n * Factorial(n - 1);
}

double SphericalHarmonics::GetLegendrePolynomialValue(int l, int m, double x)
{
	double pmm = 1.0;

	// rule 2
	if (m > 0)
	{
		double somx2 = sqrt((1.0 - x) * (1.0 + x));
		double fact = 1.0;
		for (int i = 1; i <= m; i++)
		{
			pmm *= (-fact) * somx2;
			fact += 2.0;
		}
	}
	if (l == m) return pmm;

	// rule 3
	double pmmp1 = x * (2.0 * m + 1.0) * pmm;
	if (l == m + 1) return pmmp1;

	// rule 1
	double pll = 0.0;
	for (int ll = m + 2; ll <= l; ll++)
	{
		pll = ((2.0 * ll - 1.0) * x * pmmp1 - (ll + m - 1.0) * pmm) / (ll - m);
		pmm = pmmp1;
		pmmp1 = pll;
	}

	return pll;
}

double SphericalHarmonics::GetScalingFactor(int l, int m)
{
	double temp = ((2.0 * l + 1.0) * factorials[l - m]) / (4.0 * PI * factorials[l + m]);
	return sqrt(temp);
}

double SphericalHarmonics::SH(int l, int m, double theta, double phi)
{
	// l -> band ; [0, N]
	// m -> [-l, l]
	// theta -> [0, PI]
	// phi -> [0, 2 * PI]

	const double sqrt2 = sqrt(2.0);

	if (m == 0)
	{
		return GetScalingFactor(l, 0) * GetLegendrePolynomialValue(l, m, cos(theta));
	}
	else if (m > 0)
	{
		return sqrt2 * GetScalingFactor(l, m) * cos(m * phi) * GetLegendrePolynomialValue(l, m, cos(theta));
	}
	else
	{
		return sqrt2 * GetScalingFactor(l, -m) * sin(-m * phi) * GetLegendrePolynomialValue(l, -m, cos(theta));
	}
}


