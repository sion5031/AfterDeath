#pragma once
#include <iostream>
#include <vector>

#include "Skill.h"

using namespace std;

class Item;


class Creature
{
	int TotalAtk = 0;
	int TotalDef = 0;
	int TotalMaxHp = 0;
	int TotalMaxMp = 0;

	void InitStatus()
	{
		TotalAtk = 0;
		TotalDef = 0;
		TotalMaxHp = 0;
		TotalMaxMp = 0;
	}
};


class Creature : enable_shared_from_this<Creature>
{
protected:
	string Name;
	int Type;
	int MaxHp;
	int Hp;
	int MaxMp;
	int Mp;
	int Attack;
	int Defense;
	struct Status* BuffedStatus;
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
	void SetBuffedStatus(int atk, int def, int hp, int mp);
	//void SetMyInven(shared_ptr<Inventory>);

	string GetCName();
	int GetCType();
	int GetMaxHp();
	int GetHp();
	int GetMaxMp();
	int GetMp();
	int GetAttack();
	int GetDefense();
	struct Status* GetBuffedStatus();
	vector<Skill*>* GetSkills();

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