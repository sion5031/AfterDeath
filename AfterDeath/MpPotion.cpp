#include "MpPotion.h"
#include "ConsoleGotoxy.h"

MpPotion::MpPotion(int num)
{
	Number = num;
	this->SetName("Mp 포션");
	this->SetSN(21);
	this->EffectPoint = 10;
}

MpPotion::~MpPotion()
{
}

void MpPotion::UseItem(shared_ptr<Creature> player)
{
	player->CalcMp(this->EffectPoint);
	Gotoxy(0, 17);
	cout << "Hp를 " << EffectPoint << " 만큼 회복했습니다.\n";
	Number--;
	if (Number <= 0)
	{
		Number = 0;
	}
}
