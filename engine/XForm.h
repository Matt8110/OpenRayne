#pragma once

#include <math.h>
#include "Vector.h"

class CXForm
{
public:
	float a, b, c;
	float d, e, f;
	float g, h, i;
	float j, k, l;

	void setupLocalToParent(const CVector& position, const CVector& orientation);
	void setupParentToLocal(const CVector& position, const CVector& orientation);
	CVector extractPos_L2P();
	CVector extractPBH_L2P();

	//Matches
	void mul(const CXForm& Main, const CXForm& other);
};

