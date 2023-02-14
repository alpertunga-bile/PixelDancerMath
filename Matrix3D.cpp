#include "pch.h"
#include <iostream>
#include "include/Matrix3D.h"

Matrix3D::Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
{
	m[0] = n00; m[1] = n10; m[2] = n20;
	m[3] = n01; m[4] = n11; m[5] = n21;
	m[6] = n02; m[7] = n12; m[8] = n22;
}

Matrix3D::Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
	m[0] = a.x; m[1] = a.y; m[2] = a.z;
	m[3] = b.x; m[4] = b.y; m[5] = b.z;
	m[6] = c.x; m[7] = c.y; m[8] = c.z;
}

void Matrix3D::Print(const char* name)
{
	std::cout << "--------------------------------------------------------------------------\n";
	std::cout << name << " (Matrix3D) Variables : \n";
	for (int column = 0; column < 3; column++)
	{
		for (int row = 0; row < 3; row++)
		{
			std::cout << m[column * 3 + row] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "--------------------------------------------------------------------------\n";
}
