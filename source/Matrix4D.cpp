#include "Matrix4D.h"
#include <iostream>

Matrix4D::Matrix4D(double n00,
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
                   double n23,
                   double n30,
                   double n31,
                   double n32,
                   double n33)
{
  m[0]  = n00;
  m[1]  = n10;
  m[2]  = n20;
  m[3]  = n30;
  m[4]  = n01;
  m[5]  = n11;
  m[6]  = n21;
  m[7]  = n31;
  m[8]  = n02;
  m[9]  = n12;
  m[10] = n22;
  m[11] = n32;
  m[12] = n03;
  m[13] = n13;
  m[14] = n23;
  m[15] = n33;
}

Matrix4D::Matrix4D(const Vector4D& a,
                   const Vector4D& b,
                   const Vector4D& c,
                   const Vector4D& d)
{
  m[0]  = a.x;
  m[1]  = a.y;
  m[2]  = a.z;
  m[3]  = a.w;
  m[4]  = b.x;
  m[5]  = b.y;
  m[6]  = b.z;
  m[7]  = b.w;
  m[8]  = c.x;
  m[9]  = c.y;
  m[10] = c.z;
  m[11] = c.w;
  m[12] = d.x;
  m[13] = d.y;
  m[14] = d.z;
  m[15] = d.w;
}