#pragma once
#include "Skill.h"

class ActiveSkill : public Skill
{
private:

public:
	ActiveSkill();
	//virtual ~ActiveSkill(){ cout << "~ActiveSkill()" << endl; }
	~ActiveSkill();

	virtual string Effect(shared_ptr<Creature> player, int turn) = 0;
	virtual string GetExplanation() = 0;
};