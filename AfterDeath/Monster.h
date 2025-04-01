#pragma once

#include "Creature.h"
#include "Inventory.h"

class Monster : public Creature
{
private:

public:
	Monster();
	~Monster();

	void UseSkill() override;
	void Die() override;

};