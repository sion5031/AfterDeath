#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Creature;

class Skill
{
private:
	string Name;
	int Type; //0Àº Active / 1Àº Passive
	int Level;
	int EffectValue;

public:
	Skill();
	//virtual ~Skill(){ cout << "~Skill()" << endl; }
	virtual ~Skill() {}

	virtual vector<int> Effect() = 0;

	void SetName(string name);
	void SetType(int type);
	void SetLevel(int level);
	void SetEffectValue(int value);

	string GetName();
	int GetType();
	int GetLevel();
	int GetEffectValue();

};