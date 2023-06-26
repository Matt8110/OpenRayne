#include "Vector.h"

CVector::CVector()
{
	x = 0;
	y = 0;
	z = 0;
}

CVector::CVector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

CVector::CVector(const CVector& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

void CVector::normalize()
{
	float temp = std::sqrt(z * z + x * x + y * y);

	if (temp <= 0.0f)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	else
	{
		float scalar = 1.0f / temp;
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}
}