#include "Consumable.h"

Consumable::Consumable(int num)
{
	Number = num;
}

void Consumable::SetNumber(int num)
{
	Number = num;
}

int Consumable::GetNumber()
{
	return Number;
}

void Consumable::PlusNumber(int num)
{
	Number += num; // 동작 안 함. 동적할당 아니라?
	if (Number < 0)
	{
		Number = 0;
	}
}
