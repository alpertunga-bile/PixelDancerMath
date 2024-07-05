#include "Transform.h"
#include "ConstantValues.h"

namespace pxd {
Matrix3D
MakeRotationX(float angle)
{
  double rad    = DegToRad(angle);
  float  cosine = cos(rad);
  float  sine   = sin(rad);

  return Matrix3D(1.0f, 0.0f, 0.0f, 0.0f, cosine, -sine, 0.0f, sine, cosine);
}

Matrix3D
MakeRotationY(float angle)
{
  double rad    = DegToRad(angle);
  float  cosine = cos(rad);
  float  sine   = sin(rad);

  return Matrix3D(cosine, 0.0f, sine, 0.0f, 1.0f, 0.0f, -sine, 0.0f, cosine);
}

Matrix3D
MakeRotationZ(float angle)
{
  double rad    = DegToRad(angle);
  float  cosine = cos(rad);
  float  sine   = sin(rad);

  return Matrix3D(cosine, -sine, 0.0f, sine, cosine, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3D
MakeRotation(const Vector3D& axis, float angle)
{
  double rad       = DegToRad(angle);
  float  sine      = sin(rad);
  float  cosine    = cos(rad);
  float  oneMinCos = 1.0f - cosine;

  float x = axis.x * oneMinCos;
  float y = axis.y * oneMinCos;
  float z = axis.z * oneMinCos;

  float axay = x * axis.y;
  float axaz = x * axis.z;
  float ayaz = y * axis.z;

  return Matrix3D(cosine + x * axis.x,
                  axay - sine * axis.z,
                  axaz + sine * axis.y,
                  axay + sine * axis.z,
                  cosine + y * axis.y,
                  ayaz - sine * axis.x,
                  axaz - sine * axis.y,
                  ayaz + sine * axis.x,
                  cosine + z * axis.z);
}

Matrix3D
MakeReflection(const Vector3D& axis)
{
  float x = axis.x * -2.0f;
  float y = axis.y * -2.0f;
  float z = axis.z * -2.0f;

  float axay = x * axis.y;
  float axaz = x * axis.z;
  float ayaz = y * axis.z;

  return Matrix3D(x * axis.x + 1.0f,
                  axay,
                  axaz,
                  axay,
                  y * axis.y + 1.0f,
                  ayaz,
                  axaz,
                  ayaz,
                  z * axis.z + 1.0f);
}

Matrix3D
MakeInvolution(const Vector3D& axis)
{
  float x = axis.x * 2.0f;
  float y = axis.y * 2.0f;
  float z = axis.z * 2.0f;

  float axay = x * axis.y;
  float axaz = x * axis.z;
  float ayaz = y * axis.z;

  return Matrix3D(x * axis.x - 1.0f,
                  axay,
                  axaz,
                  axay,
                  y * axis.y - 1.0f,
                  ayaz,
                  axaz,
                  ayaz,
                  z * axis.z - 1.0f);
}

Matrix3D
MakeScale(float sx, float sy, float sz)
{
  return Matrix3D(sx, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, sz);
}

Matrix3D
MakeScale(float scale, const Vector3D& v)
{
  scale -= 1.0f;

  float x = v.x * scale;
  float y = v.y * scale;
  float z = v.z * scale;

  float axay = x * v.y;
  float axaz = x * v.z;
  float ayaz = y * v.z;

  return Matrix3D(x * v.x + 1.0f,
                  axay,
                  axaz,
                  axay,
                  y * v.y + 1.0f,
                  ayaz,
                  axaz,
                  ayaz,
                  z * v.z + 1.0f);
}
Matrix3D
MakeSkew(float angle, const Vector3D& dir, const Vector3D& height)
{
  angle   = std::tan(angle);
  float x = dir.x * angle;
  float y = dir.y * angle;
  float z = dir.z * angle;

  return Matrix3D(x * height.x + 1.0f,
                  x * height.y,
                  x * height.z,
                  y * height.x,
                  y * height.y + 1.0f,
                  y * height.z,
                  z * height.x,
                  y * height.y,
                  z * height.z + 1.0f);
}
}