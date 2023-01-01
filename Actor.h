#pragma once

#include <stdio.h>
#include "Matrix.h"
#include "Vector.h"
#include "XForm.h"
#include "BoundingBox3D.h"
#include "Utils.h"

class CDemonActor
{
public:
    char name[32];
	CVector position;
	int unkInt0;
	CVector orientation;
	CMatrix orientationMatrix;
	int field_64;
	float field_68; //Always 150.0 and resets when jumping (to 150)
	float boundingBoxSize;
	CVector focusPoint;
	CBoundingBox3D boundingBox;
	int field_94;
	int field_98;
	CDemonActor* field_9C; //Next actor?
	int field_A0;
	int field_A4;
	int field_A8;
	int field_AC;
	int field_B0;
	int field_B4;
	int field_B8;
	int field_BC;
	int field_C0;
	int field_C4;
	float lightMin;
	float lightMax;
	int field_D0;
	int field_D4;
	char* group;
	int field_DC;
	int field_E0;
	CDemonActor* field_E4;
	CDemonActor* field_E8;
	CDemonActor* field_EC;
	int field_F0;
	int field_F4;
	int selfIlluminated;
	int field_FC;
	int field_100;
	int gettingHarpooned; //I think?
	int field_108;
	CDemonActor* attachListStart;
	CDemonActor* attachListNext;
	CDemonActor* attachListPrev; //Could possibly be attachListParent?
	CXForm xForm;
	CDemonActor* field_148;
	CDemonActor* field_14C;

	//Should be equivelent. Works when replaced in game
	CDemonActor();
	//Should be equivelent. Works when replaced in game
	void b2w();
	//Close to matching, but can't quite get it. Should be equivelent
	void attachActor(CDemonActor* actorToAttach);
	//Matching
	void detachMe();
	//Matching
	void FUN_0040d790();
	//Matching
	void applyAttachedListPosAndOrient();
	//Matching
	void computeDirMat();
	//Matching
	void setBoundingBox(CBoundingBox3D& bb);
	//Matching
	virtual void warpTo(const CVector& newPos, const CVector& newOrient);
	//Matching
	virtual bool amIVisible();
	//Matching
	virtual CVector getFocusPoint();
	//Matching
	virtual int getHarpoonBone();
	//Matching
	virtual CVector getLookAtPoint();
	//Matching?? For some reason my test uses JMP instead of CALL.
	virtual void process();
	//Matching
	virtual int renderTransparent();
	//Matching
	virtual void setHasChanged(){};
	//Matching
	virtual void setup();

};