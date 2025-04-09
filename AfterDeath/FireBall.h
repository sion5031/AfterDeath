#pragma once
#include "ActiveSkill.h"

class FireBall : public ActiveSkill
{
private:

public:
	FireBall();
	FireBall(int level);
	~FireBall(){}

	string Effect(shared_ptr<Creature> player, int turn) override;
};