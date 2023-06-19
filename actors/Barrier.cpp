#include "Barrier.h"

int CBarrier::fileVersion = 0; //Hmm...

CBarrier::CBarrier()
{
    size.z = 5.0f;
    size.y = 5.0f;
    size.x = 5.0f;
    effectClassNameList[0] = 0;
    addToPathGrid = 1;
}

void CBarrier::archive()
{
    //CDemonActor::archive();
    archiveVector(&size,"size");

    if (fileVersion >= 2) 
    {
        //archiveString(effectClassNameList,"effectClassNameList");
        archiveInt(&addToPathGrid,"addToPathGrid");
    }
}

int CBarrier::renderTransparent()
{
    return 0;
}

void CBarrier::setHasChanged()
{
    if (addToPathGrid != 0)
    {
        //gSet->addBarier(this);
    }
}

void CBarrier::setup()
{
    CBoundingBox3D bb;

    CDemonActor::setup();
    
    //field_F4 = gSit[0x402]; 0x1008
    field_F0 = 0;

    bb.x1 = -size.x * 0.5f;
    bb.y1 = -0.1f;
    bb.z1 = -size.z * 0.5f;
    bb.x2 = size.x * 0.5f;
    bb.y2 = size.y + 0.1f;
    bb.z2 = size.z *0.5f;

    setBoundingBox(bb);
}

/*int CBarrier::collideWithMe(CCollisionInfo* collisionInfo)
{

    if (collisionInfo->unk2 != 0)
    {
        return 0;
    }

    if (effectClassNameList[0] == '\0')
    {
        return 0;
    }

    if (gSimActor == 0 || gSimActor->isOfType(effectClassNameList))
    {
        return collideWithMyBoundingBox(collisionInfo);;
    }

    return 0;
    
}*/