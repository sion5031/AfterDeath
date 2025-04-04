#include <windows.h>

#include "GameManager.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"

unique_ptr<Map> CurrentMap;

int main()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));
	//=============위는 건들지 말기




	GameManager* GM = new GameManager();
	/*
	//==
	shared_ptr<Creature> Hero = make_shared<Player>();		
	shared_ptr<Creature> Monster1 = make_shared<Monster>();
	shared_ptr<Creature> Monster2 = make_shared<Monster>();

	CurrentMap = make_unique<Map>();
	CurrentMap->AddCreature(26, Hero);
	CurrentMap->AddCreature(36, Monster1);
	CurrentMap->AddCreature(190, Monster2);
	
	

	CurrentMap->PrintMap();

	//Hero->ReadFile("player.txt");

	while (true)
	{
		CurrentMap->MovePlayer();
		CurrentMap->DeathChecker();
		//Monster1.reset();
		CurrentMap->DeleteChecker();
		CurrentMap->MoveMonster();
		CurrentMap->DeathChecker();
		CurrentMap->DeleteChecker();
		system("cls");
		CurrentMap->PrintMap();
	}
	*/
	GM->GetCurrentMap()->PrintMap();

	while (true)
	{
		GM->GetCurrentMap()->MovePlayer();
		if (GM->DeathPlayerChecker())
		{
			continue; // 원래라면 게임 처음으로...또는 죽었을 때 가는 곳
		}
		GM->DeathMonsterChecker();

		GM->GetCurrentMap()->MoveMonster();
		if (GM->DeathPlayerChecker())
		{
			continue; // 원래라면 게임 처음으로...또는 죽었을 때 가는 곳
		}
		GM->DeathMonsterChecker();
		//GM->GetCurrentMap()->DeathChecker();
		//GM->GetCurrentMap()->DeleteChecker();
		system("cls");
		GM->GetCurrentMap()->PrintMap();
	}





















	return 0;
}










