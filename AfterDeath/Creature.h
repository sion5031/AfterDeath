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

using namespace std;

//class Item;


class Creature
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
	Creature() {}
	//virtual ~Creature(){ cout << "~Creature()" << endl; }
	virtual ~Creature(){}

	//void Move(Map* currentMap, int* location);
	void Fight(Creature* attaker, Creature* defender, int turn);
	void NormalAttack(Creature* creature);
	virtual void UseSkill(Creature* creature) = 0;
	virtual void Die() = 0;
	void CalcHp(int hp);
	void CalcMp(int mp);

	void PrintBattle(Creature* player, Creature* monster);

	void ReadFile(string fileName);

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
	int GetMaxHp();
	int GetHp();
	int GetMaxMp();
	int GetMp();
	int GetAttack();
	int GetDefense();

};


struct EquipedE
{
	shared_ptr<Item> myWeapon;
	shared_ptr<Item> myUpper;
	shared_ptr<Item> myLower;
	shared_ptr<Item> myGlove;
	shared_ptr<Item> myShoes;
	shared_ptr<Item> myShield;
};