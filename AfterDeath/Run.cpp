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

	srand(time(NULL));
	
	//==
	Creature* Monster1 = new Monster();
	Creature* Monster2 = new Monster();

	CurrentMap = make_unique<Map>();
	CurrentMap->AddCreature(26, Hero);
	CurrentMap->AddCreature(36, Monster1);
	CurrentMap->AddCreature(190, Monster2);
	
	//CurrentMap = make_unique<Map>(Hero);
	//==

	CurrentMap->PrintMap();

	//Hero->ReadFile("player.txt");

	while (true)
	{
		CurrentMap->MovePlayer();
		CurrentMap->MoveMonster();
		system("cls");
		CurrentMap->PrintMap();
	}





















	return 0;
}










