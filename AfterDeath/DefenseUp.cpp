#include <string>
#include "DefenseUp.h"

DefenseUp::DefenseUp()
{
	Name = "방어 상승(패시브)";
	Type = 0;
	MpConsume = 0;
	EffectValue = 3;
	Level = 1;
	Explanation = "자신의 방어력을 영구히 " + to_string(EffectValue * Level) + " 만큼 상승시킵니다.";
}

DefenseUp::DefenseUp(int level)
{
	Name = "방어 상승(패시브)";
	Type = 0;
	EffectValue = 3;
	Level = level;
	Explanation = "자신의 방어력을 영구히 " + to_string(EffectValue * Level) + " 만큼 상승시킵니다.";
}

string DefenseUp::Effect(shared_ptr<Creature> player, int turn)
{
	return nullptr;
}
