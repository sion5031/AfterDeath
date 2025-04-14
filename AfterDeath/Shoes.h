#pragma once
#include "Armor.h"

class Shoes : public Armor
{
private:


public:
	Shoes();
	Shoes(int level);
	//virtual ~Shoes(){ cout << "~Shoes()" << endl; }
	~Shoes();

};