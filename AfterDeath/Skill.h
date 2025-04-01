#pragma once
#include <iostream>

class Skill
{
private:
	string Name;
	int Type;
	int Level;
	int EffectValue;

public:
	Skill(){}
	//virtual ~Skill(){ cout << "~Skill()" << endl; }
	virtual ~Skill() {}

	virtual void Effect() = 0;
};