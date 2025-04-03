#pragma once

#include "Creature.h"

class Monster : public Creature
{
private:

public:
	Monster();
	~Monster();

	void UseSkill(shared_ptr<Creature> creature) override;
	void Die() override;

};