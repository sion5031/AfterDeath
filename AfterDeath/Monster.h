#pragma once

#include "Creature.h"

class Monster : public Creature
{
private:
	vector<Item*>* Items;

public:
	Monster();
	~Monster();

	void SetItems(vector<Item*>* equipments);

	void UseSkill(shared_ptr<Creature> creature) override;
	void Die() override;

	//int GetTotalAtk();
	//int GetTotalDef();
	//int GetTotalMaxHp();
	//int GetTotalMaxMp();

};
