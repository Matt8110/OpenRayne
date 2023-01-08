#pragma once

#include "Actor.h"

class CBarrier: public CDemonActor
{
public:
    CVector size;
    int addToPathGrid;
	char* effectClassNameList;
	static int fileVersion;

    //Matching
    virtual void archive();//override
    virtual int renderTransparent() override;

    //Should be equivelent, not sure why it won't match...
    void setHasChanged();
};