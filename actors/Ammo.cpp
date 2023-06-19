#include "Ammo.h"



void CAmmo::archive()
{
    //CDemonActor::archiive();
    //FUN_0040CB60(&unk0, "modelName");

    //archiveString((char*)&weaponClassName, "weaponClassName");
    archiveInt(&ammoCount, "ammoCount");
    archiveInt(&ammoType, "ammoType");
}