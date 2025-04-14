#include <windows.h>

#include "GameManager.h"
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"
#include "ConsoleGotoxy.h"

unique_ptr<Map> CurrentMap;


int main()
{
	//콘솔 창 크기 변경
	system("mode con:cols=130 lines=35");
	
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));
	//=============위는 건들지 말기



	GameManager* GM = new GameManager();
	system("cls");

	if (true)
	{
		//오프닝
		SetConsoleOutputCP(CP_UTF8);
		GM->PrintOpeningMessage("오프닝 문구");
		SetConsoleOutputCP(CP_UTF8);
		GM->PrintOpeningPage("Main_After", 13, 4);
		Sleep(500);
		GM->PrintOpeningPage("Main_Death", 12, 18);
		SetConsoleOutputCP(949);
		Gotoxy(36, 31);
		cout << "PRESS ANY KEY";
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getche();
		GotoxyCll(1);
		system("cls");

		SetConsoleOutputCP(CP_UTF8);
		GM->PrintStory("오프닝 스토리");
		SetConsoleOutputCP(949);

		system("cls");
	}
	
	int end = true;

	while (end)
	{
		GM->PrintDeathMessage();


		while (true)
		{
			//Gotoxy(0, 0);
			GM->GetCurrentMap()->PrintMap();

			int mapOrHead = GM->GetCurrentMap()->MovePlayer();
			if (mapOrHead == -100)
			{
				end = false;
				break;
			}
			else if (mapOrHead != -1)
			{
				GM->MoveMap(mapOrHead);
				continue;
			}
			if (GM->DeathPlayerChecker())
			{
				break;
			}
			GM->DeathMonsterChecker();

			vector<int> monsterLocations = GM->GetCurrentMap()->GetMonsterLocation();
			for (auto i : monsterLocations)
			{
				mapOrHead = GM->GetCurrentMap()->MoveMonster(i);
				if (mapOrHead == -100)
				{
					end = false;
					break;
				}
			}
			if (GM->DeathPlayerChecker())
			{
				break;
			}
			GM->DeathMonsterChecker();
		}
	}

	GM->PrintStory("엔딩 스토리");


	return 0;
}









