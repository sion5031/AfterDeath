#include "ActiveSkill.h"

ActiveSkill::ActiveSkill()
{
}

ActiveSkill::~ActiveSkill()
{
}

vector<int> ActiveSkill::Effect()
{
	vector<int> effect;
	effect.push_back(0);
	effect.push_back(GetEffectValue());

	return effect;
}
