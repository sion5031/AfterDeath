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
	system("mode con:cols=90 lines=35");
	
	//커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(NULL));
	//=============위는 건들지 말기

	//locale::global(locale(".UTF-8"));
	//SetConsoleOutputCP(949);
	//SetConsoleOutputCP(CP_UTF8);


	GameManager* GM = new GameManager();
	system("cls");

	//오프닝
	SetConsoleOutputCP(CP_UTF8);
	GM->PrintStartPage("Main_After", 11, 4);
	//GM->PrintStartPage("Main_After_BOM", 10, 4);
	Sleep(500);
	GM->PrintStartPage("Main_Death", 10, 18);
	//GM->PrintStartPage("Main_Death_BOM", 9, 18);
	SetConsoleOutputCP(949);
	Gotoxy(34, 31);
	cout << "PRESS ANY KEY";
	_getche();
	GotoxyCll(1);
	system("cls");



	










	while (true)
	{
		



		while (true)
		{
			Gotoxy(0, 0);
			GM->GetCurrentMap()->PrintMap();

			int nextMap = GM->GetCurrentMap()->MovePlayer();
			if (nextMap != -1)
			{
				GM->MoveMap(nextMap);
				continue;
			}
			if (GM->DeathPlayerChecker())
			{
				break;
			}
			GM->DeathMonsterChecker();

			GM->GetCurrentMap()->MoveMonster();
			if (GM->DeathPlayerChecker())
			{
				break;
			}
			GM->DeathMonsterChecker();
		}
	}





















	return 0;
}










