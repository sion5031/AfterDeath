#pragma once
#include "ActiveSkill.h"

class FireBall : public ActiveSkill
{
private:

public:
	FireBall();
	~FireBall(){}

	string Effect(shared_ptr<Creature> player, int turn) override;
};