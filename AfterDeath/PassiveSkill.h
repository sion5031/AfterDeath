#pragma once
#include "Skill.h"

class PassiveSkill : public Skill
{
private:

public:
	PassiveSkill();
	//virtual ~PassiveSkill(){ cout << "~PassiveSkill()" << endl; }
	~PassiveSkill();

	virtual string Effect(shared_ptr<Creature> player, int turn) = 0;
};