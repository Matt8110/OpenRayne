#include "Actor.h"

CDemonActor::CDemonActor()
{
    field_D4 = 0x78A123;
    name[0] = '\0';
    field_148 = 0;
    field_14C = 0;
    position.x = 0;
    position.y = 0;
    position.z = 0;
    unkInt0 = 0;
    orientation.x = 0;
    orientation.y = 0;
    orientation.z = 0;
    orientationMatrix.Identity();
    field_68 = 150.0f;
    field_94 = 0xFFFFFFFF;
    field_A0 = 0xFFFFFFFF;
    group = nullptr;
    field_E4 = nullptr;
    field_E8 = 0;
    field_EC = nullptr;
    field_F0 = 1;
    field_F4 = 0;
    selfIlluminated = 0;
    field_FC = 0;
    field_100 = 0;
    field_64 = 100;
    field_98 = 0;
    field_9C = nullptr;
    field_B0 = 0;
    field_A4 = 0;
    field_A8 = 0;
    attachListStart = nullptr;
    attachListNext = nullptr;
    attachListPrev = nullptr;
    gettingHarpooned = 0;

    CBoundingBox3D tempBB;
    tempBB.x1 = 4.0f;
    tempBB.y1 = 8.0f;
    tempBB.z1 = 4.0f;
    tempBB.x2 = -4.0f;
    tempBB.y2 = 0.0f;
    tempBB.z2 = -4.0f;
    setBoundingBox(tempBB);
    
    computeDirMat();

    field_108 = 0;
    field_AC = 0;
}

void CDemonActor::setBoundingBox(CBoundingBox3D& bb)
{
    boundingBox.x1 = bb.x1;
    boundingBox.y1 = bb.y1;
    boundingBox.z1 = bb.z1;
    boundingBox.x2 = bb.x2;
    boundingBox.y2 = bb.y2;
    boundingBox.z2 = bb.z2;
    boundingBoxSize = bb.computeBoundingSphereRadiusFromCenter();
    b2w();
}

CVector CDemonActor::getFocusPoint()
{
    CVector ret;
    ret.x = focusPoint.x;
    ret.y = focusPoint.y;
    ret.z = focusPoint.z;

    return ret;
}

CVector CDemonActor::getLookAtPoint()
{
    CVector ret;
    ret.x = position.x;
    ret.y = position.y;
    ret.z = position.z;

    return ret;
}

void CDemonActor::applyAttachedListPosAndOrient()
{
    if (attachListStart != nullptr)
    {
        CXForm tempForm;
        CXForm tempFormB;
        tempForm.setupLocalToParent(position, orientation);

        for (CDemonActor* tempActor = attachListStart; tempActor != nullptr; tempActor = tempActor->attachListNext)
        {
            tempFormB.mul(tempActor->xForm, tempForm);//Updated, should still match
            tempActor->warpTo(tempFormB.extractPos_L2P(), tempFormB.extractPBH_L2P());
        }
    }
}

void CDemonActor::computeDirMat()
{
    orientation.x = CUtils::wrapPi(orientation.x);
    orientation.z = CUtils::wrapPi(orientation.z);
    orientation.y = CUtils::wrapPi(orientation.y);

    orientationMatrix.genMatrix(orientation);
    b2w();
}

void CDemonActor::warpTo(const CVector& newPos, const CVector& newOrient)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
    orientation.x = newOrient.x;
    orientation.y = newOrient.y;
    orientation.z = newOrient.z;
    computeDirMat();
    applyAttachedListPosAndOrient();
}

void CDemonActor::b2w()
{
    float fVar1 = orientationMatrix.m11;
    float fVar2 = orientationMatrix.m01;
    float fVar3 = orientationMatrix.m21;
    float fVar4 = position.y;
    float fVar5 = orientationMatrix.m12;
    float fVar6 = orientationMatrix.m02;
    float fVar7 = orientationMatrix.m22;
    float fVar8 = position.z;
    float fVar9 = boundingBox.x1 + boundingBox.x2 * 0.5f;
    float fVar10 = boundingBox.y2 + boundingBox.y1 * 0.5f;
    float fVar11 = orientationMatrix.m10;
    float fVar12 = orientationMatrix.m00;
    float fVar13 = orientationMatrix.m20 + position.x;

    focusPoint.x = fVar10 * fVar11 + fVar9 * fVar12 + fVar11 * fVar13;
    focusPoint.y = fVar3 * fVar11 + fVar2 * fVar9 + fVar1 * fVar10 + fVar4;
    focusPoint.z = fVar11 * fVar7 + fVar5 * fVar10 + fVar6 * fVar9 + fVar8;
    FUN_0040d790();
}

void CDemonActor::FUN_0040d790()
{
    if (field_94 >= 0)
    {
        //gPortalSet->PutActorIntoBsp(this);
    }
}

bool CDemonActor::amIVisible()
{
    if (!field_F0 && !field_F4)
    {
        return 0;
    }

    //return gPortalSet->isActorVisible(this);
}

int CDemonActor::getHarpoonBone()
{
    return 0xFFFFFFFF;
}

void CDemonActor::setup()
{
    computeDirMat();

    if (attachListPrev != nullptr)
    {
        attachListPrev->attachActor(this);
    }
}

void CDemonActor::process()
{
    applyAttachedListPosAndOrient();
}

int CDemonActor::renderTransparent()
{
    return 0;
}

void CDemonActor::detachMe()
{
    CDemonActor* tempAttachListStart;
    CDemonActor* tempAttachListPrev = attachListPrev;

    if (tempAttachListPrev != nullptr)
    {
        CDemonActor* tempAttachListNext = attachListNext;
        attachListPrev = nullptr;
        attachListNext = nullptr;
        tempAttachListStart = tempAttachListPrev->attachListStart;

        if (tempAttachListPrev->attachListStart == this)
        {
            tempAttachListPrev->attachListStart = tempAttachListNext;
            return;
        }

        while(true)
        {
            tempAttachListPrev = tempAttachListStart;
            if (tempAttachListPrev == nullptr)
            {
                //gtfoSourceFile = "ACTOR.CPP";
                //gtfoSourceLine = 0xcd2;
                CUtils::reallyGTFO("Attach list corruption detected detaching \'%s\'", name);
            }

            if (tempAttachListPrev->attachListNext == this)
                break;

            tempAttachListStart = tempAttachListPrev->attachListNext;
        }

        tempAttachListStart->attachListNext = tempAttachListNext;
    }
}

void CDemonActor::attachActor(CDemonActor* actorToAttach)
{

    if (actorToAttach != nullptr)
    {
        actorToAttach->detachMe();

        for (CDemonActor* tempActor = this; tempActor != nullptr; tempActor = tempActor->attachListPrev)
        {
            if (tempActor == actorToAttach)
            {
                //reallyGTFOFile = "ACTOR.CPP";
                //reallyGTFOLine = 0xC91;
                CUtils::reallyGTFO("CDemonActor::attachActor - circular involving \'%s\' and \'%s\'", name, actorToAttach->name);
            }
        }

        actorToAttach->attachListPrev = this;
        actorToAttach->attachListNext = attachListStart;
        attachListStart = actorToAttach;

        CXForm localToParent;
        CXForm parentToLocal;

        localToParent.setupLocalToParent(actorToAttach->position, actorToAttach->orientation);
        parentToLocal.setupParentToLocal(position, orientation);

        CXForm res;
        res.mul(localToParent, parentToLocal);

        actorToAttach->xForm = res;
    }
}

int CDemonActor::amIHidden()
{
    return 0;
}

int CDemonActor::render()
{
    return 0;
}

void CDemonActor::archiveInt(int* val, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%d", val) != 1)
        {
            failedToLoadProperty("Integer value", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%d", archiveIndentString, *val);
    }
    FUN_0040C490("Integer value", name);*/
}

void CDemonActor::archiveFloat(float* val, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f", val) != 1)
        {
            failedToLoadProperty("Floating point value", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g", archiveIndentString, *val);
    }

    FUN_0040C490("Floating point value", name);*/
}

void CDemonActor::archiveVector(CVector* vec, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f,%f,%f", &vec->x, &vec->y, &vec->z) != 3)
        {
            failedToLoadProperty("3D vector", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g,%g,%g", archiveIndentString, vec->x, vec->y, vec->z);
    }

    FUN_0040C490("3D vector", name);*/
}

void CDemonActor::archiveOrient(CVector* vec, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f,%f,%f", &vec->x, &vec->y, &vec->z) != 3)
        {
            failedToLoadProperty("Euler PBH orientation", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g,%g,%g", archiveIndentString, vec->x, vec->y, vec->z);
    }

    FUN_0040C490("Euler PBH orientation", name);*/
}

char* CDemonActor::getActorType()
{
    //gtfoSourceFile = "ACTOR.CPP";
    //gtfoSourceLine = 0x346;
    CUtils::reallyGTFO("CDemonActor::getActorType called for %s.  Should never be called for this base class!", name);

    return nullptr;
}

void CDemonActor::setHasChanged()
{
    return;
}

bool CDemonActor::collideWithMe()
{
    return 0;
}

int CDemonActor::vfunction15()
{
    return 0;
}

int CDemonActor::vfunction17()
{
    return 0;
}

int CDemonActor::vfunction19()
{
    return 0;
}

int CDemonActor::vfunction21()
{
    return 0;
}

void CDemonActor::vfunction22()
{
    return;
}

void CDemonActor::getHurt()
{
    return;
}

void CDemonActor::vfunction24()
{
    return;
}

void CDemonActor::vfunction25()
{
    return;
}

void CDemonActor::vfunction26()
{
    return;
}

int CDemonActor::vfunction27()
{
    return 0;
}

int CDemonActor::vfunction30()
{
    return 0;
}

void CDemonActor::vfunction31()
{
    return;
}

void CDemonActor::vfunction32()
{
    return;
}

void CDemonActor::vfunction33()
{
    return;
}

int CDemonActor::vfunction34()
{
    return 0;
}

int CDemonActor::vfunction35()
{
    return 0;
}

bool CDemonActor::vfunction42()
{
    return 0;
}

int CDemonActor::vfunction44()
{
    return 0;
}

int CDemonActor::vfunction5()
{
    return 0;
}

int CDemonActor::vfunction7()
{
    return 1;
}