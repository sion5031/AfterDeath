#include "GameManager.h"

GameManager::GameManager()
{
	string name;
	Maps = new vector<shared_ptr<Map>>;
	for (int i = 0;i < NumMap;i++)
	{
		Maps->push_back(make_shared<Map>());
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
