#include "pch.h"
#include <iostream>
#include "include/Matrix4D.h"

Matrix4D::Matrix4D(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23, float n30, float n31, float n32, float n33)
{
	m[ 0] = n00; m[ 1] = n10; m[ 2] = n20; m[ 3] = n30;
	m[ 4] = n01; m[ 5] = n11; m[ 6] = n21; m[ 7] = n31;
	m[ 8] = n02; m[ 9] = n12; m[10] = n22; m[11] = n32;
	m[12] = n03; m[13] = n13; m[14] = n23; m[15] = n33;
}

Matrix4D::Matrix4D(const Vector4D& a, const Vector4D& b, const Vector4D& c, const Vector4D& d)
{
	m[ 0] = a.x; m[ 1] = a.y; m[ 2] = a.z; m[ 3] = a.w;
	m[ 4] = b.x; m[ 5] = b.y; m[ 6] = b.z; m[ 7] = b.w;
	m[ 8] = c.x; m[ 9] = c.y; m[10] = c.z; m[11] = c.w;
	m[12] = d.x; m[13] = d.y; m[14] = d.z; m[15] = d.w;
}

void Matrix4D::Print(const char* name)
{
	std::cout << "--------------------------------------------------------------------------\n";
	std::cout << name << " (Matrix4D) Variables : \n";
	for (int index = 0; index < 16; index++)
	{
		std::cout << m[index] << "\t";
		if (index == 3 || index == 7 || index == 11 || index == 15)
		{
			std::cout << "\n";
		}
	}
	std::cout << "--------------------------------------------------------------------------\n";
}