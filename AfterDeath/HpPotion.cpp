#include "HpPotion.h"
#include "ConsoleGotoxy.h"

HpPotion::HpPotion(int num)
{
	Number = num;
	this->SetName("Hp 포션");
	this->SetSN(20);
	this->EffectPoint = 10;
}

HpPotion::~HpPotion()
{
}

void HpPotion::UseItem(shared_ptr<Creature> player)
{
	player->CalcHp(this->EffectPoint);
	Gotoxy(0, 17);
	cout << "Hp를 " << EffectPoint << " 만큼 회복했습니다.\n";
	Number--; // consumable에서 하고싶어...
	if (Number <= 0)
	{
		Number = 0;
	}
}
