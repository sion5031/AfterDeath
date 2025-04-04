#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <string>
#include <conio.h>
//#include <codecvt>
//#include <locale>

#include "Item.h"
#include "Skill.h"
#include "IPlayable.h"

using namespace std;

//class Item;
//class Skill;

//struct EquipedE
//{
//	shared_ptr<Item> myWeapon;
//	shared_ptr<Item> myUpper;
//	shared_ptr<Item> myLower;
//	shared_ptr<Item> myGlove;
//	shared_ptr<Item> myShoes;
//	shared_ptr<Item> myShield;
//};

struct EquipedE
{
	Item* myWeapon = nullptr;
	Item* myUpper = nullptr;
	Item* myLower = nullptr;
	Item* myGlove = nullptr;
	Item* myShoes = nullptr;
	Item* myShield = nullptr;

	Item* GetItem(int num)
	{
		if (myWeapon != nullptr && num == 0) return myWeapon;
		else if (myUpper != nullptr && num == 1) return myUpper;
		else if (myLower != nullptr && num == 2) return myLower;
		else if (myGlove != nullptr && num == 3) return myGlove;
		else if (myShoes != nullptr && num == 4) return myShoes;
		else if (myShield != nullptr && num == 5) return myShield;
		else return nullptr;
	}
	void InitEquipedE()
	{
		myWeapon = nullptr;
		myUpper = nullptr;
		myLower = nullptr;
		myGlove = nullptr;
		myShoes = nullptr;
		myShield = nullptr;
	}
};

struct Status
{
	int TotalAtk = 0;
	int TotalDef = 0;
	int TotalMaxHp = 0;
	int TotalMaxMp = 0;
};

class Creature : enable_shared_from_this<Creature>
{
protected:
	string Name;
	int Type; // 0은 Player, 이외는 Monster
	int MaxHp;
	int Hp;
	int MaxMp;
	int Mp;
	int Attack;
	int Defense;
	struct EquipedE* Equipments;
	vector<Skill*>* Skills;

	const int ScreenSize = 30; //space 기준 2칸이 1size

public:
	shared_ptr<Creature> GetShared() {
		return shared_from_this();
	}
	Creature();
	//virtual ~Creature(){ cout << "~Creature()" << endl; }
	virtual ~Creature(){}

	void InitCreature();
	//void Move(Map* currentMap, int* location);
	void Fight(shared_ptr<Creature> player, shared_ptr<Creature> monster, int turn);
	void NormalAttack(shared_ptr<Creature> attacker, shared_ptr<Creature> defender);
	virtual void UseSkill(shared_ptr<Creature> creature) = 0;
	virtual void Die() = 0;
	void CalcHp(int hp);
	void CalcMp(int mp);

	void PrintBattle(shared_ptr<Creature> player, shared_ptr<Creature> monster);

	void ReadFile(string fileName);

	struct Status* GetTotalStatus();

	void SetName(string name);
	void SetType(int type);
	void SetMaxHp(int maxHp);
	void SetHp(int hp);
	void SetMaxMp(int maxMp);
	void SetMp(int mp);
	void SetAtk(int attack);
	void SetDef(int defense);
	//void SetMyInven(shared_ptr<Inventory>);

	string GetName();
	int GetType();
	//int GetMaxHp();
	int GetHp();
	//int GetMaxMp();
	int GetMp();
	int GetAttack();
	int GetDefense();

	EquipedE* GetEquipments();
};

