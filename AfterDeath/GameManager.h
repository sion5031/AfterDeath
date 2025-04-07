#pragma once
//#include <iostream>
//#include <vector>

#include "Map.h"
#include "Creature.h"

//class Map;
//class Creature;

class GameManager
{
private:
	const int NumMap = 3;
	shared_ptr<Map> CurrentMap;
	shared_ptr<Creature> Hero;
	map<int, shared_ptr<Map>>* Maps;
	vector<vector<shared_ptr<Creature>>*>* Monsters;


public:
	GameManager();
	~GameManager();

	void MoveMap(int nextMap);

	shared_ptr<Map> GetMap(string name);
	shared_ptr<Map> GetCurrentMap();

	bool DeathPlayerChecker();
	void DeathMonsterChecker();
	void InitMonster(int mapNum);

	void MakeMonsterMap1(shared_ptr<Map> map);
	void MakeMonsterMap2(shared_ptr<Map> map);
};