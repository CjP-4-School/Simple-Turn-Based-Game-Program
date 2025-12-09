#include "FinalFantasy7.h"

int FinalFantasy7::GetMagic() const
{
    return magic;
}

int FinalFantasy7::GetMagicAttack() const
{
	int magicAttack;

	magicAttack = magic + (GetDexterity() / 2);

    return magicAttack;
}

int FinalFantasy7::GetMagicDefense() const
{
    return magicDefense;
}
