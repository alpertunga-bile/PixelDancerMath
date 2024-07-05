#include "Transform4D.h"

Transform4D::Transform4D(double n00,
                         double n01,
                         double n02,
                         double n03,
                         double n10,
                         double n11,
                         double n12,
                         double n13,
                         double n20,
                         double n21,
                         double n22,
                         double n23)
{
  m[0]  = n00;
  m[1]  = n10;
  m[2]  = n20;
  m[3]  = 0.0;
  m[4]  = n01;
  m[5]  = n11;
  m[6]  = n21;
  m[7]  = 0.0;
  m[8]  = n02;
  m[9]  = n12;
  m[10] = n22;
  m[11] = 0.0;
  m[12] = n03;
  m[13] = n13;
  m[14] = n23;
  m[15] = 1.0;
}

Transform4D::Transform4D(const Vector3D& a,
                         const Vector3D& b,
                         const Vector3D& c,
                         const Point3D&  d)
{
  m[0]  = a.x;
  m[1]  = a.y;
  m[2]  = a.z;
  m[3]  = 0.0;
  m[4]  = b.x;
  m[5]  = b.y;
  m[6]  = b.z;
  m[7]  = 0.0;
  m[8]  = c.x;
  m[9]  = c.y;
  m[10] = c.z;
  m[11] = 0.0;
  m[12] = d.x;
  m[13] = d.y;
  m[14] = d.z;
  m[15] = 1.0;
}
