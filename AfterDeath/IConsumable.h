#pragma once

class IConsumable
{
public:
	virtual ~IConsumable() = default;

	virtual void UseItem() = 0;
};