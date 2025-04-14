#include "Creature.h"
#include "FireBall.h"

FireBall::FireBall()
{
	Name = "화염구";
	Type = 1;
	MpConsume = 15;
	EffectValue = 30;
	Level = 1;
	Explanation = "대상의 방어력을 50% 무시하는 " + to_string((int)(EffectValue + EffectValue * 0.5 * Level)) + " 의 데미지를 입힙니다.";
}

FireBall::FireBall(int level)
{
	Name = "화염구";
	Type = 1;
	MpConsume = 15;
	EffectValue = 20;
	Level = level;
	Explanation = "대상의 방어력을 50% 무시하는 " + to_string((int)(EffectValue + EffectValue * 0.5 * Level)) + " 의 데미지를 입힙니다.";
}

string FireBall::Effect(shared_ptr<Creature> player, int turn)
{
	int before = player->GetHp();
	// 방어력 50% 무시
	player->CalcHp(-(EffectValue + EffectValue * 0.5 * Level + player->GetTotalStatus()->TotalDef * 0.5));
	int after = player->GetHp();
	string str = player->GetName() + " 가 " + to_string(before - after) + " 만큼의 피해를 입었습니다.";
	return str;
}

string FireBall::GetExplanation()
{
	Explanation = "대상의 방어력을 50% 무시하는 " + to_string((int)(EffectValue + EffectValue * 0.5 * Level)) + " 의 데미지를 입힙니다.";
	return Explanation;
}
