#pragma once
#include "Armor.h"

class Shield : public Armor
{
private:


public:
	Shield();
	Shield(int level);
	//virtual ~Shield(){ cout << "~Shield()" << endl; }
	~Shield();

};