#include "Creature.h"
#include "IncreaseAttack.h"

IncreaseAttack::IncreaseAttack()
{
	Name = "공격력 증가시키기";
	Type = 0;
	MpConsume = 10;
	EffectValue = 10;
	Level = 1;
	Duration = 4;
}

string IncreaseAttack::Effect(shared_ptr<Creature> player, int turn)
{
	if (Using == false)
	{
		Using = true;
		Turn = turn;
		int currentAtk = player->GetAttack();
		player->SetAtk(currentAtk + EffectValue);
		string str = player->GetName() + " 의 공격력이 " + to_string(EffectValue) + " 만큼 상승했습니다.";
		return str;
	}
	else
	{
		if (turn - Turn > Duration) // 지속 시간이 끝났다면
		{
			Using = false;
			Turn = 0;
			int currentAtk = player->GetAttack();
			player->SetAtk(currentAtk - EffectValue);
		}
	}
}
