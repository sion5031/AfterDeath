#pragma once

#include "Creature.h"

class Monster : public Creature
{
private:
	vector<Item*>* Items;

public:
	Monster();
	Monster(int level);
	~Monster();

	void SetItems(vector<Item*>* equipments);

	bool UseSkill(shared_ptr<Creature> creature, int num, int count) override;
	void Die() override;

	//int GetTotalAtk();
	//int GetTotalDef();
	//int GetTotalMaxHp();
	//int GetTotalMaxMp();

};
