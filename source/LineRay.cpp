#include "LineRay.h"
#include "Matrix3D.h"
#include <cfloat>

Line
Transform(const Line& line, const Transform4D& h)
{
  Matrix3D       adj(Cross(h[1], h[2]), Cross(h[2], h[0]), Cross(h[0], h[1]));
  const Point3D& t = h.GetTranslation();

  Vector3D v = h * line.direction;
  Vector3D m = adj * line.moment + Cross(t, v);
  return Line(v, m);
}

double
DistancePointLine(const Point3D& p, const Point3D& start, const Vector3D& dir)
{
  Vector3D a = Cross(p - start, dir);
  return (std::sqrt(Dot(a, a) / Dot(dir, dir)));
}

double
DistanceLineLine(const Point3D&  p1,
                 const Vector3D& dir1,
                 const Point3D&  p2,
                 const Vector3D& dir2)
{
  Vector3D dp = p2 - p1;

  double dir1Sqr  = Dot(dir1, dir1);
  double dir2Sqr  = Dot(dir2, dir2);
  double dir1dir2 = Dot(dir1, dir2);

  double det = dir1dir2 * dir1dir2 - dir1Sqr * dir2Sqr;

  if (std::fabs(det) <= FLT_MIN) {
    Vector3D a = Cross(dp, dir1);
    return std::sqrt(Dot(a, a) / dir1dir2);
  }

  det = 1.0f / det;

  double dpdir1 = Dot(dp, dir1);
  double dpdir2 = Dot(dp, dir2);
  double t1     = (dir1dir2 * dpdir2 - dir2Sqr * dpdir1) * det;
  double t2     = (dir1dir2 * dpdir2 - dir1dir2 * dpdir1) * det;

  return Magnitude(dp + dir2 * t2 - dir1 * t1);
}
