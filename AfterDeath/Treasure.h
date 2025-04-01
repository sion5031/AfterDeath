#pragma once
#include <vector>

using namespace std;

class Item;
class Skill;

class Treasure
{
private:
	vector<Item*> Items;
	Skill* NewSkill;

public:
	Treasure();
	~Treasure();

	void SetItems(vector<Item*> treasure);
	void SetNewSkill(Skill* skill);

	vector<Item*> GetItems();
	Skill* GetNewSkill();
};