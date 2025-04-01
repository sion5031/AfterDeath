#pragma once
#include "Skill.h"

class ActiveSkill : public Skill
{
private:

public:
	ActiveSkill() {}
	//virtual ~ActiveSkill(){ cout << "~ActiveSkill()" << endl; }
	virtual ~ActiveSkill() {}

	void Effect() override;
};