#pragma once

#include "Actor.h"

class CAmmo : public CDemonActor
{
public:
	int unk0;
	char unk1[0x58];
	char weaponClassName[64];
	int ammoCount;
	int ammoType;

	CAmmo();
	virtual void archive(); //override
};