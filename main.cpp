#include "Vector4D.h"

#include <iostream>

int
main()
{
  Vector4D vec(1.0, 2.0, 3.0, 4.0);

  vec[0] = 5.0;

  vec = vec + Vector4D(1.0);

  std::printf("%.2f %.2f %.2f %.2f\n", vec.x, vec[1], vec[2], vec[3]);

  return 0;
}