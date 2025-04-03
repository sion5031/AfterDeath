#include <windows.h>

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"

unique_ptr<Map> CurrentMap;

int main()
{
	//===============//함수 추출

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);


	//===============

	shared_ptr<Creature> Hero = make_shared<Player>();

	srand(time(NULL));
	
	//==
	shared_ptr<Creature> Monster1 = make_shared<Monster>();
	shared_ptr<Creature> Monster2 = make_shared<Monster>();

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










