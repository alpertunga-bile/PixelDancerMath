#pragma once

constexpr double PI = 3.14159265358979323846;

inline double
DegToRad(double angle)
{
  return angle * (PI / 180.0);
}

inline double
RadToDeg(double rad)
{
  return rad * (180.0 / PI);
}
