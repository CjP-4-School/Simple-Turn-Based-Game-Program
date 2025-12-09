// FinalProject02.cpp : This program is a simple turn-based game/Character stat analyzer.
//
using namespace std;
#include "CharacterBase.h"
#include "FinalFantasy7.h"
#include "FireEmblem.h"
#include "MegumiTensei.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <functional>

// FUNCTION PROTOTYPES
void RunFF7Menu(vector<FinalFantasy7>& players,
	vector<FinalFantasy7>& enemies);
FinalFantasy7 CreateFF7Character();
void PrintFF7Character(const FinalFantasy7& c);
void RunMegumiMenu(vector<MegumiTensei>& players,
	vector<MegumiTensei>& enemies);
MegumiTensei CreateMegumiCharacter();
void PrintMegumiCharacter(const MegumiTensei& c);
void RunFireEmblemMenu(vector<FireEmblem>& players,
	vector<FireEmblem>& enemies);
FireEmblem CreateFireEmblemCharacter();
void PrintFireEmblemCharacter(const FireEmblem& c);

// Main program
int main()
{
    srand(static_cast<unsigned int>(time(0)));



    vector<FinalFantasy7> ff7Players;
    vector<FinalFantasy7> ff7Enemies;

    vector<MegumiTensei> megumiPlayers;
    vector<MegumiTensei> megumiEnemies;

    vector<FireEmblem> fePlayers;
    vector<FireEmblem> feEnemies;

    int choice = -1;

    while (choice != 0)
    {
        cout << "\n====================================\n";
        cout << "            GAME SELECT\n";
        cout << "====================================\n";
        cout << "1. Final Fantasy VII\n";
        cout << "2. Megumi Tensei\n";
        cout << "3. Fire Emblem\n";
        cout << "0. Exit Program\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\n";

        switch (choice)
        {

        case 1:
            RunFF7Menu(ff7Players, ff7Enemies);
            break;

        case 2:
            RunMegumiMenu(megumiPlayers, megumiEnemies);
            break;

        case 3:
            RunFireEmblemMenu(fePlayers, feEnemies);
            break;

        case 0:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }


    return 0;
}

// GENERIC OPERATIONS (TEMPLATED) USED BY BATTLE & MENUS
// List characters via a provided print function
template<typename T>
void ListCharactersGeneric(const vector<T>& list, function<void(const T&)> printFunc)
{
    if (list.empty())
    {
        cout << "No characters in this category.\n\n";
        return;
    }


    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        cout << "Index: " << i << "\n";
        printFunc(list[i]);
        cout << "-------------------------------\n";
    }
}

// Re-create (edit) a character at index using creator function
template<typename T>
void EditCharacterGeneric(vector<T>& list, function<T()> creator)
{
    if (list.empty())
    {
        cout << "No characters to edit.\n\n";
        return;
    }


    int index = -1;

    cout << "Enter index to edit: ";
    cin >> index;


    if (index < 0 || index >= static_cast<int>(list.size()))
    {
        cout << "Invalid index.\n\n";
        return;
    }


    cout << "Re-entering attributes for this character.\n";

    T newChar = creator();

    list[index] = newChar;

    cout << "Character updated.\n\n";
}

// Delete character
template<typename T>
void DeleteCharacterGeneric(vector<T>& list)
{
    if (list.empty())
    {
        cout << "No characters to delete.\n\n";
        return;
    }


    int index = -1;

    cout << "Enter index to delete: ";

    cin >> index;


    if (index < 0 || index >= static_cast<int>(list.size()))
    {
        cout << "Invalid index.\n\n";
        return;
    }


    cout << "Deleting: " << list[index].GetCharacterName() << "\n";

    list.erase(list.begin() + index);

    cout << "Deleted successfully.\n\n";
}


// TURN-BASED BATTLE (templated so it works for all three classes)
template<typename T>
bool AllDeadFromHP(const vector<int>& hp)
{
    for (int h : hp)
        if (h > 0)
            return false;

    return true;
}

template<typename T>
void StartBattleGeneric(const vector<T>& players, const vector<T>& enemies, function<void(const T&)> printFunc)
{
    if (players.empty() || enemies.empty())
    {
        cout << "Both sides must have at least one character.\n\n";
        return;
    }


    cout << "Starting battle...\n\n";


    // start timer
    auto startTime = chrono::high_resolution_clock::now();


    // mutable HP arrays
    vector<int> pHP, eHP;

    for (const auto& p : players)
        pHP.push_back(p.GetHealthPoints());

    for (const auto& e : enemies)
        eHP.push_back(e.GetHealthPoints());


    int roundNumber = 1;


    while (true)
    {

        cout << "===================================\n";
        cout << "           ROUND " << roundNumber << "\n";
        cout << "===================================\n\n";



        // Players attack
        for (int i = 0; i < static_cast<int>(players.size()); ++i)
        {

            if (pHP[i] <= 0) // dead, skip
                continue;



            // pick random living enemy
            vector<int> living;

            for (int j = 0; j < static_cast<int>(eHP.size()); ++j)
            {
                if (eHP[j] > 0)
                {
                    living.push_back(j);
                }
            }

            if (living.empty())
            {
                break;
            }

            int randIndex = living[rand() % living.size()];

            int damage = players[i].GetAttack() + players[i].GetWeaponPower() - enemies[randIndex].GetDefense();

            if (damage < 1)
            {
                damage = 0; 
            }


            eHP[randIndex] -= damage;

            cout << players[i].GetCharacterName() << " hits " << enemies[randIndex].GetCharacterName() << " for " << damage << " damage.\n";

            if (eHP[randIndex] <= 0)
            {
                cout << enemies[randIndex].GetCharacterName() << " HAS DIED!\n\n";
            }

        }



        if (AllDeadFromHP<T>(eHP))
        {
            cout << "All enemy units have died! PLAYERS WIN!\n\n";
            break;
        }



        // Enemies attack
        for (int i = 0; i < static_cast<int>(enemies.size()); ++i)
        {

            if (eHP[i] <= 0)
                continue;



            vector<int> living;

            for (int j = 0; j < static_cast<int>(pHP.size()); ++j)
                if (pHP[j] > 0)
                    living.push_back(j);



            if (living.empty())
                break;



            int randIndex = living[rand() % living.size()];



            int damage = enemies[i].GetAttack() + enemies[i].GetWeaponPower() - players[randIndex].GetStrength();

            if (damage < 1)
                damage = 1;



            pHP[randIndex] -= damage;



            cout << enemies[i].GetCharacterName()
                << " hits "
                << players[randIndex].GetCharacterName()
                << " for " << damage << " damage.\n";



            if (pHP[randIndex] <= 0)
            {
                cout << players[randIndex].GetCharacterName() << " HAS DIED!\n\n";
            }

        }


        if (AllDeadFromHP<T>(pHP))
        {
            cout << "All player units have died! ENEMIES WIN!\n\n";
            break;
        }


        ++roundNumber;

        cout << "\n";
    } // battle loop
    auto endTime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);

    cout << "Battle ended in " << duration.count() << " seconds.\n\n";
}


//--------------------------- Final Fantasy VII menu ---------------------------
void RunFF7Menu(vector<FinalFantasy7>& players,
    vector<FinalFantasy7>& enemies)
{

    int choice = -1;


    while (choice != 0)
    {

        cout << "\n====================================\n";
        cout << "        FINAL FANTASY VII - MENU\n";
        cout << "====================================\n";
        cout << "1. Add Player Unit\n";
        cout << "2. Add Enemy Unit\n";
        cout << "3. List Player Units\n";
        cout << "4. List Enemy Units\n";
        cout << "5. Edit Player Unit\n";
        cout << "6. Edit Enemy Unit\n";
        cout << "7. Delete Player Unit\n";
        cout << "8. Delete Enemy Unit\n";
        cout << "9. Start Battle\n";
        cout << "0. Return to Game Select\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\n";


        switch (choice)
        {

        case 1:
            players.push_back(CreateFF7Character());
            break;

        case 2:
            enemies.push_back(CreateFF7Character());
            break;

        case 3:
            ListCharactersGeneric<FinalFantasy7>(players, PrintFF7Character);
            break;

        case 4:
            ListCharactersGeneric<FinalFantasy7>(enemies, PrintFF7Character);
            break;

        case 5:
            EditCharacterGeneric<FinalFantasy7>(players, CreateFF7Character);
            break;

        case 6:
            EditCharacterGeneric<FinalFantasy7>(enemies, CreateFF7Character);
            break;

        case 7:
            DeleteCharacterGeneric<FinalFantasy7>(players);
            break;

        case 8:
            DeleteCharacterGeneric<FinalFantasy7>(enemies);
            break;

        case 9:
            StartBattleGeneric<FinalFantasy7>(players, enemies, PrintFF7Character);
            break;

        case 0:
            cout << "Returning to game select...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

FinalFantasy7 CreateFF7Character()
{
    string name;

    cout << "Enter character name: ";
    cin >> ws;

    getline(cin, name);

    int lvl = 1;

    cout << "Enter level: ";
    cin >> lvl;

    int hp = 50;

    cout << "Enter health points (HP): ";
    cin >> hp;

    int atk = 5;

    cout << "Enter attack: ";
    cin >> atk;

    int stg = 5;

    cout << "Enter strength: ";
    cin >> stg;

    int vit = 5;

    cout << "Enter vitality: ";
    cin >> vit;

    int dex = 5;

    cout << "Enter dexterity: ";
    cin >> dex;

    int ag = 5;

    cout << "Enter agility: ";
    cin >> ag;



    int lck = 0;

    cout << "Enter luck: ";
    cin >> lck;

    int def = 0;

    cout << "Enter defense: ";
    cin >> def;

    string wname;

    cout << "Enter weapon name: ";
    cin >> ws;

    getline(cin, wname);

    int wp = 0;

    cout << "Enter weapon power: ";
    cin >> wp;

    int mgc = 0;

    cout << "Enter magic (stat): ";
    cin >> mgc;

    int mgcAtk = 0;

    cout << "Enter magic attack: ";
    cin >> mgcAtk;

    int mgcDef = 0;

    cout << "Enter magic defense: ";
    cin >> mgcDef;

    return FinalFantasy7(name, lvl, hp, atk, stg, vit, dex, ag, lck, def, wname, wp, mgc, mgcAtk, mgcDef);
}

void PrintFF7Character(const FinalFantasy7& c)
{
    cout << "Name:           " << c.GetCharacterName() << "\n";

    cout << "Level:          " << c.GetLevel() << "\n";

    cout << "HP:             " << c.GetHealthPoints() << "\n";

    cout << "Attack:         " << c.GetAttack() << "\n";

    cout << "Strength:       " << c.GetStrength() << "\n";

    cout << "Vitality:       " << c.GetVitality() << "\n";

    cout << "Dexterity:      " << c.GetDexterity() << "\n";

    cout << "Agility:        " << c.GetAgility() << "\n";

    cout << "Luck:           " << c.GetLuck() << "\n";

    cout << "Weapon Name:    " << c.GetWeaponName() << "\n";

    cout << "Weapon Power:   " << c.GetWeaponPower() << "\n";

    cout << "Magic:          " << c.GetMagic() << "\n";

    cout << "Magic Attack:   " << c.GetMagicAttack() << "\n";

    cout << "Magic Defense:  " << c.GetMagicDefense() << "\n";
}


// ------------------------- Megumi Tensei ---------------------------
void RunMegumiMenu(vector<MegumiTensei>& players,
    vector<MegumiTensei>& enemies)
{
    int choice = -1;


    while (choice != 0)
    {

        cout << "\n====================================\n";
        cout << "        MEGUMI TENSEI - MENU\n";
        cout << "====================================\n";
        cout << "1. Add Player Unit\n";
        cout << "2. Add Enemy Unit\n";
        cout << "3. List Player Units\n";
        cout << "4. List Enemy Units\n";
        cout << "5. Edit Player Unit\n";
        cout << "6. Edit Enemy Unit\n";
        cout << "7. Delete Player Unit\n";
        cout << "8. Delete Enemy Unit\n";
        cout << "9. Start Battle\n";
        cout << "0. Return to Game Select\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\n";


        switch (choice)
        {
        case 1:
            players.push_back(CreateMegumiCharacter());
            break;

        case 2:
            enemies.push_back(CreateMegumiCharacter());
            break;

        case 3:
            ListCharactersGeneric<MegumiTensei>(players, PrintMegumiCharacter);
            break;

        case 4:
            ListCharactersGeneric<MegumiTensei>(enemies, PrintMegumiCharacter);
            break;

        case 5:
            EditCharacterGeneric<MegumiTensei>(players, CreateMegumiCharacter);
            break;

        case 6:
            EditCharacterGeneric<MegumiTensei>(enemies, CreateMegumiCharacter);
            break;

        case 7:
            DeleteCharacterGeneric<MegumiTensei>(players);
            break;

        case 8:
            DeleteCharacterGeneric<MegumiTensei>(enemies);
            break;

        case 9:
            StartBattleGeneric<MegumiTensei>(players, enemies, PrintMegumiCharacter);
            break;

        case 0:
            cout << "Returning to game select...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

MegumiTensei CreateMegumiCharacter()
{
    string name;

    cout << "Enter character name: ";
    cin >> ws;

    getline(cin, name);

    int lvl = 1;

    cout << "Enter level: ";
    cin >> lvl;

    int hp = 50;

    cout << "Enter health points (HP): ";
    cin >> hp;

    int atk = 5;

    cout << "Enter attack: ";
    cin >> atk;

    int stg = 5;

    cout << "Enter strength: ";
    cin >> stg;

    int vit = 5;

    cout << "Enter vitality: ";
    cin >> vit;

    int dex = 5;

    cout << "Enter dexterity: ";
    cin >> dex;

    int ag = 5;

    cout << "Enter agility: ";
    cin >> ag;

    int lck = 0;

    cout << "Enter luck: ";
    cin >> lck;

    int def = 0;

    cout << "Enter defense: ";
    cin >> def;

    string wname;

    cout << "Enter weapon name: ";
    cin >> ws;

    getline(cin, wname);

    int wp = 0;

    cout << "Enter weapon power: ";
    cin >> wp;

    int mgcAtk = 0;

    cout << "Enter magic attack: ";
    cin >> mgcAtk;

    int mgcDef = 0;

    cout << "Enter magic defense: ";
    cin >> mgcDef;


    return MegumiTensei(name, lvl, hp, atk, stg, vit, dex, ag, lck, def, wname, wp, mgcAtk, mgcDef);
}

void PrintMegumiCharacter(const MegumiTensei& c)
{
    cout << "Name:            " << c.GetCharacterName() << "\n";

    cout << "Level:           " << c.GetLevel() << "\n";

    cout << "HP:              " << c.GetHealthPoints() << "\n";

    cout << "Attack:          " << c.GetAttack() << "\n";

    cout << "Strength:        " << c.GetStrength() << "\n";

    cout << "Vitality:        " << c.GetVitality() << "\n";

    cout << "Dexterity:       " << c.GetDexterity() << "\n";

    cout << "Agility:         " << c.GetAgility() << "\n";

    cout << "Luck:            " << c.GetLuck() << "\n";

    cout << "Weapon Name:     " << c.GetWeaponName() << "\n";

    cout << "Weapon Power:    " << c.GetWeaponPower() << "\n";

    cout << "Magic Attack:    " << c.GetMagicAttack() << "\n";

    cout << "Magic Defense:   " << c.GetMagicDefense() << "\n";
}


// ------------------------- Fire Emblem ----------------------------- 
void RunFireEmblemMenu(vector<FireEmblem>& players,
    vector<FireEmblem>& enemies)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n====================================\n";
        cout << "          FIRE EMBLEM - MENU\n";
        cout << "====================================\n";
        cout << "1. Add Player Unit\n";
        cout << "2. Add Enemy Unit\n";
        cout << "3. List Player Units\n";
        cout << "4. List Enemy Units\n";
        cout << "5. Edit Player Unit\n";
        cout << "6. Edit Enemy Unit\n";
        cout << "7. Delete Player Unit\n";
        cout << "8. Delete Enemy Unit\n";
        cout << "9. Start Battle\n";
        cout << "0. Return to Game Select\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        cout << "\n";

        switch (choice)
        {
        case 1:
            players.push_back(CreateFireEmblemCharacter());
            break;

        case 2:
            enemies.push_back(CreateFireEmblemCharacter());
            break;

        case 3:
            ListCharactersGeneric<FireEmblem>(players, PrintFireEmblemCharacter);
            break;

        case 4:
            ListCharactersGeneric<FireEmblem>(enemies, PrintFireEmblemCharacter);
            break;

        case 5:
            EditCharacterGeneric<FireEmblem>(players, CreateFireEmblemCharacter);
            break;

        case 6:
            EditCharacterGeneric<FireEmblem>(enemies, CreateFireEmblemCharacter);
            break;

        case 7:
            DeleteCharacterGeneric<FireEmblem>(players);
            break;

        case 8:
            DeleteCharacterGeneric<FireEmblem>(enemies);
            break;

        case 9:
            StartBattleGeneric<FireEmblem>(players, enemies, PrintFireEmblemCharacter);
            break;

        case 0:
            cout << "Returning to game select...\n";
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

FireEmblem CreateFireEmblemCharacter()
{
    string name;

    cout << "Enter character name: ";
    cin >> ws;

    getline(cin, name);

    int lvl = 1;

    cout << "Enter level: ";
    cin >> lvl;

    int hp = 50;

    cout << "Enter health points (HP): ";
    cin >> hp;

    int atk = 5;

    cout << "Enter attack: ";
    cin >> atk;

    int stg = 5;

    cout << "Enter strength: ";
    cin >> stg;

    int vit = 5;

    cout << "Enter vitality: ";
    cin >> vit;

    int dex = 5;

    cout << "Enter dexterity: ";
    cin >> dex;

    int ag = 5;

    cout << "Enter agility: ";
    cin >> ag;

    int lck = 0;

    cout << "Enter luck: ";
    cin >> lck;

    int def = 0;

    cout << "Enter defense: ";
    cin >> def;

    string wname;

    cout << "Enter weapon name: ";
    cin >> ws;

    getline(cin, wname);

    int wp = 0;

    cout << "Enter weapon power: ";
    cin >> wp;

    string wcc;

    cout << "Enter weapon class color (string): ";
    cin >> ws;

    getline(cin, wcc);

    int mgc = 0;

    cout << "Enter magic (stat): ";
    cin >> mgc;

    int spd = 0;

    cout << "Enter speed: ";
    cin >> spd;

    return FireEmblem(name, lvl, hp, atk, stg, vit, dex, ag, lck, def, wname, wp, wcc, mgc, spd);
}

void PrintFireEmblemCharacter(const FireEmblem& c)
{
    cout << "Name:               " << c.GetCharacterName() << "\n";

    cout << "Level:              " << c.GetLevel() << "\n";

    cout << "HP:                 " << c.GetHealthPoints() << "\n";

    cout << "Attack:             " << c.GetAttack() << "\n";

    cout << "Strength:           " << c.GetStrength() << "\n";

    cout << "Vitality:           " << c.GetVitality() << "\n";

    cout << "Dexterity:          " << c.GetDexterity() << "\n";

    cout << "Agility:            " << c.GetAgility() << "\n";

    cout << "Luck:               " << c.GetLuck() << "\n";

    cout << "Weapon Name:        " << c.GetWeaponName() << "\n";

    cout << "Weapon Power:       " << c.GetWeaponPower() << "\n";

    cout << "Weapon Class Color: " << c.GetWeaponClassColor() << "\n";

    cout << "Magic:              " << c.GetMagic() << "\n";

    cout << "Speed:              " << c.GetSpeed() << "\n";
}
