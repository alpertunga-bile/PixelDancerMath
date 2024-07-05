#include "Plane.h"

#include <cfloat>

bool
IntersectLinePlane(const Point3D&  p,
                   const Vector3D& dir,
                   const Plane&    f,
                   Point3D&        q)
{
  float fv = Dot(f, dir);

  // Check if line coming from front side of the plane f
  if (std::fabs(fv) <= FLT_MIN)
    return false;

  Vector3D temp = p - dir * (Dot(f, p) / fv);
  q             = Point3D(temp.x, temp.y, temp.z);
  return true;
}

Transform4D
MakeReflection(const Plane& f)
{
  float x = f.x * -2.0f;
  float y = f.y * -2.0f;
  float z = f.z * -2.0f;

  float nxny = x * f.y;
  float nxnz = x * f.z;
  float nynz = y * f.z;

  return Transform4D(x * f.x + 1.0f,
                     nxny,
                     nxnz,
                     x * f.w,
                     nxny,
                     y * f.y + 1.0f,
                     nynz,
                     y * f.w,
                     nxnz,
                     nynz,
                     z * f.z + 1.0f,
                     z * f.w);
}

bool
IntersectThreePlanes(const Plane& f1,
                     const Plane& f2,
                     const Plane& f3,
                     Point3D&     p)
{
  const Vector3D n1 = f1.GetNormal();
  const Vector3D n2 = f2.GetNormal();
  const Vector3D n3 = f3.GetNormal();

  Vector3D n1n2 = Cross(n1, n2);
  float    det  = Dot(n1n2, n3);

  if (std::fabs(det) <= FLT_MIN)
    return false;

  Vector3D temp =
    (Cross(n3, n2) * f1.w + Cross(n1, n3) * f2.w - n1n2 * f3.w) / det;
  p = Point3D(temp.x, temp.y, temp.z);
  return true;
}

bool
IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D& p, Vector3D& v)
{
  const Vector3D n1 = f1.GetNormal();
  const Vector3D n2 = f2.GetNormal();

  v         = Cross(n1, n2);
  float det = Dot(v, v);

  if (std::fabs(det) <= FLT_MIN)
    return false;

  Vector3D temp = (Cross(v, n2) * f1.w + Cross(n1, v) * f2.w) / det;
  p             = Point3D(temp.x, temp.y, temp.z);
  return true;
}
