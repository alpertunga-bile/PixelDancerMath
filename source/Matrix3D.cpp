#include "Matrix3D.h"

#include "Matrix4D.h"

Matrix3D::Matrix3D()
{
  for (int i = 0; i < 9; ++i) {
    m[i] = 0.0;
  }
}

Matrix3D::Matrix3D(double n00,
                   double n01,
                   double n02,
                   double n10,
                   double n11,
                   double n12,
                   double n20,
                   double n21,
                   double n22)
{
  m[0] = n00;
  m[1] = n10;
  m[2] = n20;
  m[3] = n01;
  m[4] = n11;
  m[5] = n21;
  m[6] = n02;
  m[7] = n12;
  m[8] = n22;
}

Matrix3D::Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
  m[0] = a.x;
  m[1] = a.y;
  m[2] = a.z;
  m[3] = b.x;
  m[4] = b.y;
  m[5] = b.z;
  m[6] = c.x;
  m[7] = c.y;
  m[8] = c.z;
}

Matrix3D::Matrix3D(const Matrix4D& fromMat)
{
  m[0] = fromMat(0, 0);
  m[1] = fromMat(1, 0);
  m[2] = fromMat(2, 0);
  m[3] = fromMat(0, 1);
  m[4] = fromMat(1, 1);
  m[5] = fromMat(2, 1);
  m[6] = fromMat(0, 2);
  m[7] = fromMat(1, 2);
  m[8] = fromMat(2, 2);
}