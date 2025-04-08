#pragma once
#include "Weapon.h"

class LongSword : public Weapon
{
private:


public:
	LongSword();
	LongSword(int level);
	//virtual ~LongSword(){ cout << "~LongSword()" << endl; }
	~LongSword();

};