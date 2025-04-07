#include "Creature.h"
#include "FireBall.h"

FireBall::FireBall()
{
	Name = "화염구";
	Type = 0;
	MpConsume = 15;
	EffectValue = 10;
	Level = 1;
}

string FireBall::Effect(shared_ptr<Creature> player, int turn)
{
	player->CalcHp(-(EffectValue + EffectValue*0.5*Level));
	string str = player->GetName() + " 가 " + to_string((int)(EffectValue + EffectValue * 0.5 * Level)) + " 만큼의 피해를 입었습니다.";
	//cout << player->GetName() << " 가 " << EffectValue + EffectValue * 0.5 * Level << " 만큼의 피해를 입었습니다." << endl;
	return str;
}
