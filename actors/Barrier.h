#pragma once

#include "Actor.h"

class CBarrier: public CDemonActor
{
public:
    CVector size;
    int addToPathGrid;
	char effectClassNameList[64];
	static int fileVersion;

    //Matching
    CBarrier();
    virtual void archive();//override
    virtual int renderTransparent() override;
    //collideWithMe(CCollisionInfo* collisionInfo);
    void setHasChanged();

    //Not sure why it won't match, 4 instructions happen out of order
    //for seemingly no reason, should still be equivelent and may
    //actually be matching.
    void setup() override;
};