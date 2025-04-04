#include "GameManager.h"

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

	Monsters = new vector<vector<shared_ptr<Creature>>*>;

	Monsters->push_back(new vector<shared_ptr<Creature>>);
	//====
	Monsters->at(0)->push_back(make_shared<Monster>());
	Monsters->at(0)->push_back(make_shared<Monster>());

	CurrentMap->AddCreature(26, Hero);
	CurrentMap->AddCreature(36, Monsters->at(0)->at(0));
	CurrentMap->AddCreature(190, Monsters->at(0)->at(1));
}

GameManager::~GameManager()
{
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

void GameManager::MakeMap1(shared_ptr<Map>)
{
	//맵 장애물 만들고
	// 보물 넣고
	// 포털 넣고
	//creature 넣기
}

void GameManager::MakeMap2(shared_ptr<Map>)
{
	
}
