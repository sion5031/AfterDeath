#pragma once
#include "Skill.h"

class PassiveSkill : public Skill
{
private:

public:
	PassiveSkill() {}
	//virtual ~PassiveSkill(){ cout << "~PassiveSkill()" << endl; }
	virtual ~PassiveSkill() {}

	void Effect() override;
};