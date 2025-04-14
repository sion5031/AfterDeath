#include "HpPotion.h"
#include "ConsoleGotoxy.h"

HpPotion::HpPotion(int num)
{
	Number = num;
	this->SetName("HP 포션");
	this->SetSN(20);
	this->EffectPoint = 30;
}

HpPotion::~HpPotion()
{
}

string HpPotion::UseItem(shared_ptr<Creature> player)
{
	int before = player->GetHp();
	player->CalcHp(this->EffectPoint);
	int after = player->GetHp();
	string message = "Hp를 " + to_string(after - before) + " 만큼 회복했습니다.";
	Number--; // consumable에서 하고싶어...
	if (Number <= 0)
	{
		Number = 0;
	}
	return message;
}
