#pragma once
#include "Weapon.h"

class ShortSword : public Weapon
{
private:


public:
	ShortSword();
	ShortSword(int level);
	//virtual ~ShortSword(){ cout << "~ShortSword()" << endl; }
	~ShortSword();

};