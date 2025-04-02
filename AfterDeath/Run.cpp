#include <windows.h>

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"

unique_ptr<Map> CurrentMap;


int main()
{
	Creature* Hero = new Player();
	
	CurrentMap = make_unique<Map>();

	CurrentMap->_printMap();






















	return 0;
}










