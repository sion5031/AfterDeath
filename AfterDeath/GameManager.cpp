#include "GameManager.h"
#include "ConsoleGotoxy.h"
#include <algorithm>
#include <random>

GameManager::GameManager()
{
	string name;
	Maps = new map<int, shared_ptr<Map>>;
	for (int i = 0;i < NumMap;i++)
	{
		Maps->insert({ i, make_shared<Map>(i) });
	}
	Gotoxy(23, 17);
	cout << "플레이어의 이름을 입력하세요 : ";
	cin >> name;
	Hero = make_shared<Player>(name);
	CurrentMap = (*Maps)[0];

	// 맵으로 옮기기!!
	Monsters = new vector<vector<shared_ptr<Creature>>*>;
	for (int i = 0;i < 3;i++)
	{
		Monsters->push_back(new vector<shared_ptr<Creature>>);
	}
	
	MakeMonsterMap1(Maps->at(0));
	MakeMonsterMap2(Maps->at(1));
	MakeMonsterMap3(Maps->at(2));

	Maps->at(0)->AddCreature(Maps->at(0)->GetStartLocation(), Hero);

}

GameManager::~GameManager()
{
}

void GameManager::PrintStartPage(string fileName, int x, int y)
{
	ifstream readFile;
	readFile.open("..\\" + fileName + ".txt");
	vector<string> strVector;
	int line = 0;

	if (readFile.is_open()) {
		while (!readFile.eof())
		{
			string s;
			getline(readFile, s);
			strVector.push_back(s);
			line++;
		}
	}
	else {
		cout << "파일을 찾을 수 없습니다!" << endl;
	}
	random_device rd;
	mt19937 g(rd());
	vector<int> randomVector;
	for (int i = 0;i < strVector.size();i++)
	{
		randomVector.push_back(i);
	}
	std::shuffle(randomVector.begin(), randomVector.end(), g);
	for (int i = 0;i < strVector.size();i++)
	{
		Gotoxy(x, y + randomVector[i]);
		cout << strVector[randomVector[i]] << '\n';
		Sleep(80);
	}

	readFile.close();
}

void GameManager::PrintDeathMessage()
{
	shared_ptr<IPlayable> playableCreature = dynamic_pointer_cast<IPlayable>(Hero);
	if (playableCreature->GetDeathCount() > 0)
	{
		system("cls");
		Gotoxy(38, 16);
		string dead = "DEAD!";

		for (int i = 0;i < dead.length();i++)
		{
			cout << dead[i] << "    ";
			Sleep(300);
		}
		Sleep(1000);
		GotoxyPrintXReturn("                                 ", 36);

		Gotoxy(40, 16);

		cout << "사망 횟수  ";
		Sleep(1000);
		cout << playableCreature->GetDeathCount();
		Sleep(2000);

		GotoxyPrintXReturn("                      ", 36);
	}
}

void GameManager::MoveMap(int nextMap)
{
	int playerLocation = CurrentMap->GetPlayerLocation();

	CurrentMap->DeletePlayer(); // Object 놓으려면 player가 없어져야함


	CurrentMap = Maps->at(nextMap); // 첫 맵으로 전환

	CurrentMap->AddCreature(CurrentMap->GetStartLocation(), Hero);
}

shared_ptr<Map> GameManager::GetMap(string name)
{
	for (int i = 0;i < Maps->size();i++)
	{
		if ((*Maps)[i]->GetName() == name)
		{
			return (*Maps)[i];
		}
	}
	
    return nullptr;
}

shared_ptr<Map> GameManager::GetCurrentMap()
{
	return CurrentMap;
}

bool GameManager::DeathPlayerChecker()
{
	if (Hero->GetHp() <= 0)
	{
		// 모든 맵 초기화???? //Player 초기화!!!!
		MakeMonsterMap1(Maps->at(0)); // 초기화 시 자리있음!
		MakeMonsterMap2(Maps->at(1));

		Hero->InitCreature();		//hp, mp, Equipments


		shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(Hero);
		if (addableCreature)
		{

			//deathcount 증가
			addableCreature->PlusDeathCount();
			

			//떨구기1
			vector<Item*>* dropItems = new vector<Item*>;
			dropItems = addableCreature->GetAllInventoryItems();

			//inven 초기화
			addableCreature->InitInventory();

			//떨구기2
			if (dropItems != nullptr)
			{
				int playerLocation = CurrentMap->GetPlayerLocation();

				MapObjects* dropObject = new MapObjects;
				dropObject->Treasure = new Treasure();
				dropObject->Treasure->SetItems(dropItems);

				CurrentMap->DeletePlayer(); // Object 놓으려면 player가 없어져야함

				CurrentMap->AddObject(playerLocation, dropObject);
			}
			else
			{
				CurrentMap->DeletePlayer();
			}
		}
		
		//CurrentMap->DeletePlayer();

		CurrentMap = Maps->at(0); // 첫 맵으로 전환
		
		CurrentMap->AddCreature(CurrentMap->GetStartLocation(), Hero);

		return true;
	}
	return false;
}

void GameManager::DeathMonsterChecker()
{
	for (int i = 0;i < Monsters->size();i++)
	{
		for (int j = 0;j < Monsters->at(i)->size();j++)
		{
			if (Monsters->at(i)->at(j)->GetHp() <= 0)
			{
				Monsters->at(i)->at(j).reset();
				Monsters->at(i)->erase(Monsters->at(i)->begin() + j);//위와 같은말?
				
				//CurrentMap->DeathChecker();
				CurrentMap->DeleteChecker();
			}
		}
	}
}

void GameManager::InitMonster(int mapNum)
{
	for (int j = 0;j < Monsters->at(mapNum)->size();j++)
	{
		if (Monsters->at(mapNum)->at(j)->GetHp() <= 0)
		{/*
			Maps->at(mapNum)->

			Monsters->at(mapNum)->at(j).reset();*/
			Monsters->at(mapNum)->erase(Monsters->at(mapNum)->begin() + j);//위와 같은말?

			//CurrentMap->DeathChecker();
			CurrentMap->DeleteChecker();
		}
	}
}

void GameManager::MakeMonsterMap1(shared_ptr<Map> map)
{
	//creature 넣기
	int num = map->GetNum();
	Monsters->at(num)->clear();
	Maps->at(num)->DeleteChecker();

	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>());

	Maps->at(num)->AddCreature(36, Monsters->at(num)->at(0));
	Maps->at(num)->AddCreature(190, Monsters->at(num)->at(1));

	MapObjects* newMapObject = new MapObjects;
	newMapObject->Portal = make_shared<Portal>(1);
	Maps->at(0)->AddObject(191, newMapObject);
}

void GameManager::MakeMonsterMap2(shared_ptr<Map> map)
{
	int num = map->GetNum();
	//creature 넣기
	Monsters->at(num)->clear();
	Maps->at(num)->DeleteChecker();

	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>(1));

	Maps->at(num)->AddCreature(36, Monsters->at(num)->at(0));
	Maps->at(num)->AddCreature(190, Monsters->at(num)->at(1));
	Maps->at(num)->AddCreature(160, Monsters->at(num)->at(2));

	MapObjects* newMapObject = new MapObjects;
	newMapObject->Portal = make_shared<Portal>(2);
	Maps->at(num)->AddObject(92, newMapObject);
}

void GameManager::MakeMonsterMap3(shared_ptr<Map> map)
{
	int num = map->GetNum();
	//creature 넣기
	Monsters->at(num)->clear();
	Maps->at(num)->DeleteChecker();

	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>(1));
	Monsters->at(num)->push_back(make_shared<Monster>(2));

	Maps->at(num)->AddCreature(36, Monsters->at(num)->at(0));
	Maps->at(num)->AddCreature(190, Monsters->at(num)->at(1));
	Maps->at(num)->AddCreature(160, Monsters->at(num)->at(2));

	//마지막 맵이라
	//MapObjects* newMapObject = new MapObjects;
	//newMapObject->Portal = make_shared<Portal>(0);
	//Maps->at(num)->AddObject(92, newMapObject);
}
