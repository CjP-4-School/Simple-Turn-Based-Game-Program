#pragma once
#include "CharacterBase.h"
class FinalFantasy7 :
    public CharacterBase
{
private:
    int magic;
    int magicAttack;
	int magicDefense;
public:
	FinalFantasy7(const string& cn, int lvl, int hp, int atk, int stg, int vit, int dex, int ag, int lck, int def, string& wn, int wp, int mgc, int mgcAtk, int mgcDef)
		: CharacterBase(cn, lvl, hp, atk, stg, vit, dex, ag, lck, def, wn, wp), magic(mgc), magicAttack(mgcAtk), magicDefense(mgcDef)
	{
	}
	~FinalFantasy7() = default;
	int GetMagic() const;
	int GetMagicAttack() const;
	int GetMagicDefense() const;

};

