#pragma once

#include "Vector3D.h"
#include <stdexcept>
#include <vector>

struct SHSample
{
  Vector3D            sh;
  Vector3D            vec;
  std::vector<double> coefficient;
};

class SphericalHarmonics
{
public:
  // Rule of 5
  SphericalHarmonics(); // default constructor
                        // countSample must be sqrt of the desired total sample
  SphericalHarmonics(int countSample, int nBands); // special constructor
  SphericalHarmonics(const SphericalHarmonics& other) =
    default;                                                // copy constructor
  SphericalHarmonics(SphericalHarmonics&& other) = default; // move constructor
  SphericalHarmonics& operator=(const SphericalHarmonics& other) =
    default;                       // move assignment
  ~SphericalHarmonics() = default; // deconstructor

  // Calculate with different samples and nBands
  void ReCalculate(int _countSamples, int _nBands);

  inline std::vector<SHSample> GetSamples() { return samples; }
  inline size_t                GetSampleCount() { return samples.size(); }
  inline int                   GetBandsCount() { return nBands; }
  inline int                   GetCoefficientSize() { return nBands * nBands; }

  std::vector<float> GetCoefficients(float a, float b, int nBands);

  SHSample operator[](int index)
  {
    if (index >= samples.size() || index < 0) {
      throw std::out_of_range(
        "::EXCEPTION:: Spherical Harmonics - Index Out Of Range");
    }

    return samples[index];
  }

  const SHSample operator[](int index) const
  {
    if (index >= samples.size() || index < 0) {
      throw std::out_of_range(
        "::EXCEPTION:: Spherical Harmonics - Index Out Of Range");
    }

    return samples[index];
  }

private:
  void  Setup();
  void  PreCalculateFactorials();
  float Factorial(int n);

  // associeated legendre polynomial at x | P
  double GetLegendrePolynomialValue(int l, int m, double x);
  // scaling factor to normalize the function | K
  double GetScalingFactor(int l, int m);
  double SH(int l, int m, double theta, double phi);

private:
  std::vector<SHSample> samples;
  int                   nBands;
  int                   countOfSamples;
  float                 factorials[34] = { 0.0 };
};
