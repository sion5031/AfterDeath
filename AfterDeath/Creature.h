#pragma once
#include <iostream>

//#include "Inventory.h"

using namespace std;

class Inventory;
class Item;


class Creature
{
private:
	string CName;
	int CType;
	int MaxHp;
	int Hp;
	int MaxMp;
	int Mp;
	int Atk;
	int Def;
	unique_ptr<Inventory> myInven;
	Equiped* equiped;

public:
	Creature();
	~Creature();

	void Attack(Creature);
	virtual void UseSkill();
	virtual void Die();




	void SetCName(string CName);
	void SetCType(int CType);
	void SetMaxHp(int MaxHp);
	void SetHp(int Hp);
	void SetMaxMp(int MaxMp);
	void SetMp(int Mp);
	void SetAtk(int Atk);
	void SetDef(int Def);
	//void SetMyInven(shared_ptr<Inventory>);

	string GetCName();
	int GetCType();
	int GetMaxHp();
	int GetHp();
	int GetMaxMp();
	int GetMp();
	int GetAtk();
	int GetDef();

};


struct Equiped
{
	shared_ptr<Item> myWeapon;
	shared_ptr<Item> myUpper;
	shared_ptr<Item> myLower;
	shared_ptr<Item> myGlove;
	shared_ptr<Item> myShoes;
	shared_ptr<Item> myShield;
};