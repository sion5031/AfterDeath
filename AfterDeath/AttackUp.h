#pragma once
#include "PassiveSkill.h"

class AttackUp : public PassiveSkill
{
private:

public:
	AttackUp();
	AttackUp(int level);
	//virtual ~PassiveSkill(){ cout << "~PassiveSkill()" << endl; }
	~AttackUp() {};

	string Effect(shared_ptr<Creature> player, int turn) override;
	string GetExplanation();
};