#pragma once
#include <iostream>

using namespace std;

class Item
{
private:
	string name;
	int SN;

protected:
	int AtkPoint;
	int DefPoint;
	int EffectPoint;
	bool Equiped;

public:
	Item(){}
	//virtual ~Item() = 0; // 반드시 자식이 override 해야함
	//virtual ~Item(){ cout << "~Item()" << endl; }
	virtual ~Item(){}

	void SetEquipedTrue();
	void SetEquipedFalse();

	void SetName(string name);
	void SetSN(int SN);
	void SetAtkPoint(int atkPoint);
	void SetDefPoint(int defPoint);
	void SetEffectPoint(int effectPoint);
	void SetEquiped(bool equiped);

	string GetName();
	int GetSN();
	int GetAtkPoint();
	int GetDefPoint();
	int GetEffectPoint();
	bool GetEquiped();
};