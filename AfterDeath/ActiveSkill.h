#pragma once
#include "Skill.h"

class ActiveSkill : public Skill
{
private:

public:
	ActiveSkill();
	//virtual ~ActiveSkill(){ cout << "~ActiveSkill()" << endl; }
	~ActiveSkill();

	vector<int> Effect() override;
};