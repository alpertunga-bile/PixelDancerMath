#include "Matrix4D.h"

#include <iostream>

int
main()
{
  Matrix4D m(1.0,
             2.0,
             3.0,
             4.0,
             5.0,
             6.0,
             7.0,
             8.0,
             9.0,
             10.0,
             11.0,
             12.0,
             13.0,
             14.0,
             15.0,
             16.0);

  Vector4D col_0 = m.cols[0];

  std::printf("%.2f %.2f %.2f %.2f\n", col_0.x, col_0.y, col_0.z, col_0.w);

  return 0;
}