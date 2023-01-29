#include "pch.h"
#include <iostream>
#include "include/Matrix3D.h"

Matrix3D::Matrix3D(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22)
{
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

Matrix3D::Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
	n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
	n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
	n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
}

void Matrix3D::Print(const char* name)
{
	std::cout << "--------------------------------------------------------------------------\n";
	std::cout << name << " (Matrix3D) Variables : \n";
	(*this)[0].Print("First  Column");
	(*this)[1].Print("Second Column");
	(*this)[2].Print("Third  Column");
	std::cout << "--------------------------------------------------------------------------\n";
}
