#include "Barrier.h"

int CBarrier::fileVersion = 0; //Hmm...

//What's up with that string? Pointer to a pointer?
void CBarrier::archive()
{
    //CDemonActor::archive();
    archiveVector(&size,"size");

    if (fileVersion >= 2) 
    {
        //archiveString((char*)&effectClassNameList,"effectClassNameList");
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
        //gSet->addBarier();
    }
}