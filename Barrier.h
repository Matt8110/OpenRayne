#pragma once

#include "Actor.h"

class CBarrier: public CDemonActor
{
public:
    CVector size;
    int addToPathGrid;
	char* effectClassNameList;
	static int fileVersion;

    //Probably matching, but hard to tell
    CBarrier();

    //Matching
    virtual void archive();//override
    virtual int renderTransparent() override;

    //Should be equivelent, not sure why it won't match...
    void setHasChanged();

    //Not sure why it won't match, 4 instructions happen out of order
    //for seemingly no reason, should still be equivelent and may
    //actually be matching.
    void setup() override;
};