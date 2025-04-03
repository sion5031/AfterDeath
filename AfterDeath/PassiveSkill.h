#pragma once
#include "Skill.h"

class PassiveSkill : public Skill
{
private:

public:
	PassiveSkill();
	//virtual ~PassiveSkill(){ cout << "~PassiveSkill()" << endl; }
	~PassiveSkill();

	vector<int> Effect() override;
};