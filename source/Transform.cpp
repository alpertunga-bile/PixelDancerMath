#include "Transform.h"

#include "ConstantValues.h"
#include "Matrix3D.h"
#include "Vector3D.h"

namespace pxd {
Matrix3D
MakeRotationX(double angle)
{
  double rad    = DegToRad(angle);
  double cosine = cos(rad);
  double sine   = sin(rad);

  return Matrix3D(1.0f, 0.0f, 0.0f, 0.0f, cosine, -sine, 0.0f, sine, cosine);
}

Matrix3D
MakeRotationY(double angle)
{
  double rad    = DegToRad(angle);
  double cosine = cos(rad);
  double sine   = sin(rad);

  return Matrix3D(cosine, 0.0f, sine, 0.0f, 1.0f, 0.0f, -sine, 0.0f, cosine);
}

Matrix3D
MakeRotationZ(double angle)
{
  double rad    = DegToRad(angle);
  double cosine = cos(rad);
  double sine   = sin(rad);

  return Matrix3D(cosine, -sine, 0.0f, sine, cosine, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix3D
MakeRotation(const Vector3D& axis, double angle)
{
  double rad       = DegToRad(angle);
  double sine      = sin(rad);
  double cosine    = cos(rad);
  double oneMinCos = 1.0f - cosine;

  double x = axis.x * oneMinCos;
  double y = axis.y * oneMinCos;
  double z = axis.z * oneMinCos;

  double axay = x * axis.y;
  double axaz = x * axis.z;
  double ayaz = y * axis.z;

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
  double x = axis.x * -2.0f;
  double y = axis.y * -2.0f;
  double z = axis.z * -2.0f;

  double axay = x * axis.y;
  double axaz = x * axis.z;
  double ayaz = y * axis.z;

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
  double x = axis.x * 2.0f;
  double y = axis.y * 2.0f;
  double z = axis.z * 2.0f;

  double axay = x * axis.y;
  double axaz = x * axis.z;
  double ayaz = y * axis.z;

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
MakeScale(double sx, double sy, double sz)
{
  return Matrix3D(sx, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, sz);
}

Matrix3D
MakeScale(double scale, const Vector3D& v)
{
  scale -= 1.0f;

  double x = v.x * scale;
  double y = v.y * scale;
  double z = v.z * scale;

  double axay = x * v.y;
  double axaz = x * v.z;
  double ayaz = y * v.z;

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
MakeSkew(double angle, const Vector3D& dir, const Vector3D& height)
{
  angle    = std::tan(angle);
  double x = dir.x * angle;
  double y = dir.y * angle;
  double z = dir.z * angle;

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