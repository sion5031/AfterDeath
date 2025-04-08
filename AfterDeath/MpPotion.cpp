#include "MpPotion.h"
#include "ConsoleGotoxy.h"

MpPotion::MpPotion(int num)
{
	Number = num;
	this->SetName("Mp 포션");
	this->SetSN(21);
	this->EffectPoint = 20;
}

MpPotion::~MpPotion()
{
}

string MpPotion::UseItem(shared_ptr<Creature> player)
{
	int before = player->GetMp();
	player->CalcMp(this->EffectPoint);
	int after = player->GetMp();
	string message = "Mp를 " + to_string(after - before) + " 만큼 회복했습니다.";
	Number--; // consumable에서 하고싶어...
	if (Number <= 0)
	{
		Number = 0;
	}
	return message;
}
