#include "Quaternion.h"

#include "Matrix3D.h"
#include <cmath>

Quaternion::Quaternion(double a, double b, double c, double d)
{
  v = Vector3D(a, b, c);
  w = d;
}

Quaternion::Quaternion(const Vector3D& _v, double s)
{
  v = _v;
  w = s;
}

Matrix3D
Quaternion::GetRotationMatrix()
{
  double x2 = v.x * v.x;
  double y2 = v.y * v.y;
  double z2 = v.z * v.z;
  double xy = v.x * v.y;
  double xz = v.x * v.z;
  double yz = v.y * v.z;
  double wx = w * v.x;
  double wy = w * v.y;
  double wz = w * v.z;

  return Matrix3D(1.0f - 2.0f * (y2 + z2),
                  2.0f * (xy - wz),
                  2.0f * (xz + wy),
                  2.0f * (xy + wz),
                  1.0f - 2.0f * (x2 + z2),
                  2.0f * (yz - wx),
                  2.0f * (xz - wy),
                  2.0f * (yz + wx),
                  1.0f - 2.0f * (x2 + y2));
}

void
Quaternion::SetRotationMatrix(const Matrix3D& m)
{
  if (Determinant(m) != 1)
    return;

  double m00 = m(0, 0);
  double m11 = m(1, 1);
  double m22 = m(2, 2);

  double diagonalSum = m00 + m11 + m22;

  if (diagonalSum > 0.0f) {
    w        = std::sqrt(diagonalSum + 1.0) * 0.5;
    double f = 0.25 / w;

    v = Vector3D(
      m(2, 1) - m(1, 2) * f, m(0, 2) - m(2, 0) * f, m(1, 0) - m(0, 1) * f);
  } else if ((m00 > m11) && (m00 > m22)) {
    v.x      = std::sqrt(m00 - m11 - m22 + 1.0) * 0.5;
    double f = 0.25 / v.x;

    v.y = (m(1, 0) + m(0, 1)) * f;
    v.z = (m(0, 2) + m(2, 0)) * f;
    w   = (m(2, 1) - m(1, 2)) * f;
  } else if (m11 > m22) {
    v.y      = std::sqrt(m11 - m00 - m22 + 1.0) * 0.5;
    double f = 0.25 / v.y;

    v.x = (m(1, 0) + m(0, 1)) * f;
    v.z = (m(2, 1) + m(1, 2)) * f;
    w   = (m(0, 2) - m(2, 0)) * f;
  } else {
    v.z      = std::sqrt(m22 - m00 - m11 + 1.0) * 0.5;
    double f = 0.25 / v.z;

    v.x = (m(0, 2) + m(2, 0)) * f;
    v.y = (m(2, 1) + m(0, 1)) * f;
    w   = (m(1, 0) - m(0, 1)) * f;
  }
}