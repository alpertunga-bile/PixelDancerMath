#include "pch.h"
#include "include/Transform4D.h"

Transform4D::Transform4D(float n00, float n01, float n02, float n03, float n10, float n11, float n12, float n13, float n20, float n21, float n22, float n23)
{
	m[0] = n00; m[1] = n10; m[2] = n20; m[3] = 0.0f;
	m[4] = n01; m[5] = n11; m[6] = n21; m[7] = 0.0f;
	m[8] = n02; m[9] = n12; m[10] = n22; m[11] = 0.0f;
	m[12] = n03; m[13] = n13; m[14] = n23; m[15] = 1.0f;
}

Transform4D::Transform4D(const Vector3D& a, const Vector3D& b, const Vector3D& c, const Point3D& d)
{
	m[0] = (float)a.x; m[1] = (float)a.y; m[2] = (float)a.z; m[3] = 0.0f;
	m[4] = (float)b.x; m[5] = (float)b.y; m[6] = (float)b.z; m[7] = 0.0f;
	m[8] = (float)c.x; m[9] = (float)c.y; m[10] = (float)c.z; m[11] = 0.0f;
	m[12] = (float)d.x; m[13] = (float)d.y; m[14] = (float)d.z; m[15] = 1.0f;
}
