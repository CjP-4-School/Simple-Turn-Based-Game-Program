#pragma once
using namespace std;
#include <string>
#include <iostream>
class CharacterBase
{
private:
	string characterName;
	int level;
	int healthPoints;
	int attack;
	int strength;
	int vitality;
	int dexterity;
	int agility;
	int luck;
	int defense;
	string weaponName;
	int weaponPower;
public:
	CharacterBase(const string& cn, int lvl, int hp, int atk, int stg, int vit, int dex, int ag, int lck, int def, string& wn, int wp)
		: characterName(cn), level(lvl), healthPoints(hp), attack(atk), strength(stg), vitality(vit), dexterity(dex), agility(ag), luck(lck), defense(def), weaponName(wn), weaponPower(wp)
	{
	}
	 ~CharacterBase() = default;
	 string GetCharacterName() const;
	 int GetLevel() const;
	 int GetHealthPoints() const;
	 int GetAttack() const;
	 int GetStrength() const;
	 int GetVitality() const;
	 int GetDexterity() const;
	 int GetAgility() const;
	 int GetLuck() const;
	 int GetDefense() const;
	 string GetWeaponName() const;
	 int GetWeaponPower() const;

};

