#include "CharacterBase.h"

string CharacterBase::GetCharacterName() const
{
	return string();characterName;
}

int CharacterBase::GetLevel() const
{
	return level;
}

int CharacterBase::GetHealthPoints() const
{
	return healthPoints;
}

int CharacterBase::GetAttack() const
{
	int attack;

	attack = weaponPower + strength;

	return attack;
}

int CharacterBase::GetStrength() const
{
	return strength;
}

int CharacterBase::GetVitality() const
{
	return vitality;
}

int CharacterBase::GetDexterity() const
{
	return dexterity;
}

int CharacterBase::GetAgility() const
{
	return agility;
}

int CharacterBase::GetLuck() const
{
	return luck;
}

int CharacterBase::GetDefense() const
{
	return defense;
}

string CharacterBase::GetWeaponName() const
{
	return weaponName;
}

int CharacterBase::GetWeaponPower() const
{
	return weaponPower;
}
