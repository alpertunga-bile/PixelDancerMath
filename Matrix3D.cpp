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
	m[0] = (float)a.x; m[1] = (float)a.y; m[2] = (float)a.z;
	m[3] = (float)b.x; m[4] = (float)b.y; m[5] = (float)b.z;
	m[6] = (float)c.x; m[7] = (float)c.y; m[8] = (float)c.z;
}

Matrix3D::Matrix3D(const Matrix4D& fromMat)
{
	m[0] = fromMat(0, 0); m[1] = fromMat(1, 0); m[2] = fromMat(2, 0);
	m[3] = fromMat(0, 1); m[4] = fromMat(1, 1); m[5] = fromMat(2, 1);
	m[6] = fromMat(0, 2); m[7] = fromMat(1, 2); m[8] = fromMat(2, 2);
}

void Matrix3D::Print(const char* name)
{
	std::cout << "--------------------------------------------------------------------------\n";
	std::cout << name << " (Matrix3D) Variables : \n";
	for (int index = 0; index < 9; index++)
	{
		std::cout << m[index] << "\t";
		if (index == 2 || index == 5 || index == 8)
		{
			std::cout << "\n";
		}
	}
	std::cout << "--------------------------------------------------------------------------\n";
}
