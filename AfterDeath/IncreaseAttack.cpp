#include "Creature.h"
#include "IncreaseAttack.h"

IncreaseAttack::IncreaseAttack()
{
	Name = "공격 상승(엑티브)";
	Type = 2;
	MpConsume = 10;
	EffectValue = 20;
	Level = 1;
	Duration = 4;
	Explanation = "자신의 공격력을 " + to_string(Duration) + " 턴동안 " + to_string((int)(EffectValue * (0.5 + 0.5 * Level))) + " 만큼 상승시킵니다.";
}

IncreaseAttack::IncreaseAttack(int level)
{
	Name = "공격 상승(엑티브)";
	Type = 2;
	MpConsume = 10;
	EffectValue = 20;
	Level = level;
	Duration = 4;
	Explanation = "자신의 공격력을 " + to_string(Duration) + " 턴동안 " + to_string((int)(EffectValue * (0.5 + 0.5 * Level))) + " 만큼 상승시킵니다.";
}

string IncreaseAttack::Effect(shared_ptr<Creature> player, int turn)
{
	string str;
	if (Using == false)
	{
		Using = true;
		Turn = turn;
		//int currentAtk = player->GetAttack();
		int raise = EffectValue * (0.5 + 0.5 * Level);
		//player->SetAtk(currentAtk + raise);
		player->SetBuffedStatus(raise, 0, 0, 0);
		str = player->GetName() + " 의 공격력이 " + to_string(raise) + " 만큼 상승했습니다.";
		return str;
	}
	else
	{
		if (turn - Turn > Duration) // 지속 시간이 끝났다면
		{
			Using = false;
			Turn = 0;
			int currentAtk = player->GetAttack();
			int raise = EffectValue * (0.5 + 0.5 * Level);
			player->SetAtk(currentAtk - raise);
			return "-1";
		}
	}
	return str;
}

string IncreaseAttack::GetExplanation()
{
	Explanation = "자신의 공격력을 " + to_string(Duration) + " 턴동안 " + to_string((int)(EffectValue * (0.5 + 0.5 * Level))) + " 만큼 상승시킵니다.";
	return Explanation;
}
