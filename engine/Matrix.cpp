#include "Matrix.h"

void CMatrix::genMatrix(const CVector& vector)
{
	float sinX = sinf(vector.x);
	float cosX = cosf(vector.x);
	float sinZ = sinf(vector.z);
	float cosZ = cosf(vector.z);
	float sinY = sinf(vector.y);
	float cosY = cosf(vector.y);

	m00 = cosY * cosZ + sinZ * sinY * sinX;
	m10 = -cosY * sinZ + cosZ * sinY * sinX;
	m20 = sinY * cosX;
	m01 = sinZ * cosX;
	m11 = cosZ * cosX;
	m21 = -sinX;
	m02 = -sinY * cosZ + sinZ * cosY * sinX;
	m12 = sinZ * sinY + cosZ * cosY * sinX;
	m22 = cosY * cosX;
}

void CMatrix::Identity()
{
	m22 = 1.0f;
	m11 = 1.0f;
	m00 = 1.0f;
	m02 = 0.0f;
	m01 = 0.0f;
	m12 = 0.0f;
	m10 = 0.0f;
	m21 = 0.0f;
	m20 = 0.0f;
}

void CMatrix::invert()
{
	float temp = (m12 * m01 - m02 * m11) * m20 + ((m22 * m11 - m12 * m21) * m00 - (m22 * m01 - m02 * m21) * m10);

	if (temp == 0)
	{
		CUtils::reallyGTFO("CMatrix::invert - Singular matrix");
	}

	temp = 1.0f / temp;

	m00 = temp * (m22 * m11 - m12 * m21);
	m10 = -(m22 * m10 - m20 * m12) * temp;
	m20 = (m21 * m10 - m20 * m11) * temp;
	m01 = -(m22 * m01 - m02 * m21) * temp;
	m11 = (m00 * m22 - m20 * m02) * temp;
	m21 = -(m21 * m00 - m20 * m01) * temp;
	m02 = (m12 * m01 - m02 * m11) * temp;
	m12 = -(m12 * m00 - m02 * m10) * temp;
	m22 = temp * (m00 * m11 - m10 * m10);
}