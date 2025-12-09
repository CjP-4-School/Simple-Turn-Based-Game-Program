#pragma once
#include "CharacterBase.h"
class MegumiTensei :
    public CharacterBase
{
private:
    int magicAttack;
    int magicDefense;
public:
	MegumiTensei(const string& cn, int lvl, int hp, int atk, int stg, int vit, int dex, int ag, int lck, int def, string& wn, int wp, int mgcAtk, int mgcDef)
		: CharacterBase(cn, lvl, hp, atk, stg, vit, dex, ag, lck, def, wn, wp), magicAttack(mgcAtk), magicDefense(mgcDef)
	{
	}
	~MegumiTensei() = default;
	int GetMagicAttack() const;
	int GetMagicDefense() const;

};

