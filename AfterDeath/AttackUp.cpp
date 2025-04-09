#include <string>
#include "AttackUp.h"

AttackUp::AttackUp()
{
	Name = "공격 상승(패시브)";
	Type = 0;
	MpConsume = 0;
	EffectValue = 3;
	Level = 1;
	Explanation = "자신의 공격력을 영구히 " + to_string(EffectValue * Level) + " 만큼 상승시킵니다.";
}

AttackUp::AttackUp(int level)
{
	Name = "공격 상승(패시브)";
	Type = 0;
	EffectValue = 3;
	Level = level;
	Explanation = "자신의 공격력을 영구히 " + to_string(EffectValue * Level) + " 만큼 상승시킵니다.";
}

string AttackUp::Effect(shared_ptr<Creature> player, int turn)
{
	return nullptr;
}
