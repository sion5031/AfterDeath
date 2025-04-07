#pragma once
#include "ActiveSkill.h"

class IncreaseAttack : public ActiveSkill
{
private:

public:
	IncreaseAttack();
	~IncreaseAttack() {}

	string Effect(shared_ptr<Creature> player, int turn) override;
};