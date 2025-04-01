#pragma once

class IEquipable
{
public:
	virtual ~IEquipable() = default;

	virtual void EquipItem() = 0;
};