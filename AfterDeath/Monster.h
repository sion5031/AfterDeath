#pragma once

#include "Creature.h"

class Monster : public Creature
{
private:
	vector<Item*>* Equipments;

public:
	Monster();
	~Monster();

	void SetEquipments(vector<Item*>* equipments);

	void UseSkill(shared_ptr<Creature> creature) override;
	void Die() override;

	int GetTotalAtk();
	int GetTotalDef();
	int GetTotalMaxHp();
	int GetTotalMaxMp();

};
