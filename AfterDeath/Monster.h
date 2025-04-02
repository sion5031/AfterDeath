#pragma once

#include "Creature.h"

class Monster : public Creature
{
private:

public:
	Monster();
	~Monster();

	void UseSkill(Creature* creature) override;
	void Die() override;

};