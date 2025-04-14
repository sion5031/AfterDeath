#pragma once
#include "PassiveSkill.h"

class DefenseUp : public PassiveSkill
{
private:

public:
	DefenseUp();
	DefenseUp(int level);
	//virtual ~PassiveSkill(){ cout << "~PassiveSkill()" << endl; }
	~DefenseUp() {};

	string Effect(shared_ptr<Creature> player, int turn) override;
	string GetExplanation() override;
};