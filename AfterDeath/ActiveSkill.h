#pragma once
#include "Skill.h"

class ActiveSkill : public Skill
{
private:

public:
	ActiveSkill();
	//virtual ~ActiveSkill(){ cout << "~ActiveSkill()" << endl; }
	~ActiveSkill();

	void Effect() override;
};