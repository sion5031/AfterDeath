#include "GameManager.h"
#include "ConsoleGotoxy.h"

GameManager::GameManager()
{
	string name;
	Maps = new map<int, shared_ptr<Map>>;
	for (int i = 0;i < NumMap;i++)
	{
		Maps->insert({ i, make_shared<Map>(i) });
	}
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

	Maps->at(0)->AddCreature(Maps->at(0)->GetStartLocation(), Hero);

}

GameManager::~GameManager()
{
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
				//EquipedE* dropItem = new EquipedE;
				//dropItem = Monsters->at(i)->at(j)->GetEquipments();
				//MapObjects* dropObjects = new MapObjects;
				//dropObjects->Item = dropItem->myGlove;
				//CurrentMap->AddObject(, dropObjects); // Map에서 구현함

				Monsters->at(i)->at(j).reset();
				Monsters->at(i)->erase(Monsters->at(i)->begin() + j);//위와 같은말?
				
				//CurrentMap->DeathChecker();
				CurrentMap->DeleteChecker();
			}
		}
	}

	//int MapSize = CurrentMap->GetMapSize();
	//for (int i = 0;i < MapSize * MapSize;i++)
	//{
	//	if (CurrentMap->GetCreature(i)!=nullptr)
	//	{
	//		if (CurrentMap->GetCreature(i)->GetHp() <= 0 && CurrentMap->GetCreature(i)->GetType() == 0)
	//		{
	//			if (CurrentMap->GetCreature(i)->GetType() == 0)
	//			{
	//				//GetCreature(i).reset();
	//				break;
	//			}
	//			else if (CurrentMap->GetCreature(i)->GetType() > 0)
	//			{
	//				CurrentMap->GetCreature(i).reset();
	//				break;
	//			}
	//			else
	//			{
	//				cout << "Creature Type Error" << endl;
	//			}
	//		}
	//	}
	//}
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
	Monsters->at(0)->clear();
	Monsters->at(0)->push_back(make_shared<Monster>());
	Monsters->at(0)->push_back(make_shared<Monster>());

	Maps->at(0)->DeleteChecker();
	Maps->at(0)->AddCreature(36, Monsters->at(0)->at(0));
	Maps->at(0)->AddCreature(190, Monsters->at(0)->at(1));

	MapObjects* newMapObject = new MapObjects;
	newMapObject->Portal = make_shared<Portal>(1);
	Maps->at(0)->AddObject(191, newMapObject); // 초기화시 아마 자리있음?
}

void GameManager::MakeMonsterMap2(shared_ptr<Map> map)
{
	int num = 1;
	//creature 넣기
	Monsters->at(num)->clear();
	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>());
	Monsters->at(num)->push_back(make_shared<Monster>());

	Maps->at(num)->DeleteChecker();
	//Maps->at(num)->AddCreature(Maps->at(num)->GetStartLocation(), Hero);
	Maps->at(num)->AddCreature(36, Monsters->at(num)->at(0));
	Maps->at(num)->AddCreature(190, Monsters->at(num)->at(1));
	Maps->at(num)->AddCreature(160, Monsters->at(num)->at(2));

	MapObjects* newMapObject = new MapObjects;
	newMapObject->Portal = make_shared<Portal>(0);
	Maps->at(num)->AddObject(92, newMapObject);
}
