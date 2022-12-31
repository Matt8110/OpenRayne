#include "Actor.h"

void CDemonActor::applyAttachedListPosAndOrient()
{
    if (attachListStart != nullptr)
    {
        CXForm tempForm;
        CXForm tempFormB;
        tempForm.setupLocalToParent(position, orientation);

        for (CDemonActor* tempActor = attachListStart; tempActor != nullptr; tempActor = tempActor->attachListNext)
        {
            tempActor->xForm.mul(&tempFormB, tempForm);
            tempActor->warpTo(tempFormB.extractPos_L2P(), tempFormB.extractPBH_L2P());
        }
    }
}

void CDemonActor::computeDirMat()
{
    orientation.x = Utils::wrapPi(orientation.x);
    orientation.z = Utils::wrapPi(orientation.z);
    orientation.y = Utils::wrapPi(orientation.y);

    orientationMatrix.genMatrix(orientation);
    //FUN_0040DCC0();
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
