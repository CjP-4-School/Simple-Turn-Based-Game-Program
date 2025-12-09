#pragma once
#include "CharacterBase.h"
class FireEmblem :
    public CharacterBase
{
private:
	string WeaponClassColor;
    int magic;
	int speed;

public:
	FireEmblem(const string& cn, int lvl, int hp, int atk, int stg, int vit, int dex, int ag, int lck, int def, string& wn, int wp, string wcc, int mgc, int spd)
		: CharacterBase(cn, lvl, hp, atk, stg, vit, dex, ag, lck, def, wn, wp), magic(mgc), speed(spd), WeaponClassColor(wcc)
	{
	}
	~FireEmblem() = default;
	string GetWeaponClassColor() const;
	int GetMagic() const;
	int GetSpeed() const;

};

