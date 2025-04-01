#pragma once
#include <iostream>
#include <vector>

#include "Skill.h"

using namespace std;

class Item;


class Creature
{
private:
	string Name;
	int Type;
	int MaxHp;
	int Hp;
	int MaxMp;
	int Mp;
	int Attack;
	int Defense;
	struct EquipedE* Equipments;
	vector<Skill*> Skills;

public:
	Creature() {}
	//virtual ~Creature(){ cout << "~Creature()" << endl; }
	virtual ~Creature(){}

	//void Move(Map* currentMap, int* location);
	void Fight(Creature* player, Creature* monster);
	void NormalAttack(Creature*);
	void HitBy(int damage);
	virtual void UseSkill() = 0;
	virtual void Die() = 0;
	void CalcHp(int hp);
	void CalcMp(int mp);




	void SetName(string name);
	void SetType(int type);
	void SetMaxHp(int maxHp);
	void SetHp(int hp);
	void SetMaxMp(int maxMp);
	void SetMp(int mp);
	void SetAtk(int attack);
	void SetDef(int defense);
	//void SetMyInven(shared_ptr<Inventory>);

	string GetCName();
	int GetCType();
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