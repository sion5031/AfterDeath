#include "PassiveSkill.h"

PassiveSkill::PassiveSkill()
{
}

PassiveSkill::~PassiveSkill()
{
}

vector<int> PassiveSkill::Effect()
{
	vector<int> effect;
	effect.push_back(10);
	effect.push_back(GetEffectValue());

	return effect;
}
