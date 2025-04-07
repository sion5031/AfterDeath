#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Creature;

class Skill
{
private:

protected:
	string Name;
	int Type; //0Àº Active / 1Àº Passive
	int Level;
	int MpConsume;
	int EffectValue;
	int Duration;
	int Turn;
	bool Using = false;

public:
	Skill();
	//virtual ~Skill(){ cout << "~Skill()" << endl; }
	virtual ~Skill() {}

	virtual string Effect(shared_ptr<Creature> player, int turn) = 0;

	void SetName(string name);
	void SetType(int type);
	void SetLevel(int level);
	void SetEffectValue(int value);

	string GetName();
	int GetType();
	int GetLevel();
	int GetEffectValue();
	int GetMpConsume();

};