#pragma once
#include <iostream>
#include <map>
#include <Windows.h>
#include <conio.h>

#include "Creature.h"
#include "Treasure.h"
#include "Portal.h"
#include "IPlayable.h"

using namespace std;

struct MapObjects
{
	bool Presence = false;
	Treasure* Treasure = nullptr;
	Item* Item = nullptr;
	Portal* Portal = nullptr;
};

class Map
{

private:
	string Name;
	int MaxMonster; //¾²³ª??
	int MaxTreasure;
	bool** Obstacles;
	map<int, Creature*>* CreaturesLocation;
	map<int, MapObjects*>* ObjectsLocation;
	const int MapSize = 15;

	void FillMap();

public:
	Map();
	Map(Creature* player);
	~Map();

	void MovePlayer();
	void MoveMonster();
	void UsePortal(int location);

	void AddCreature(int location, Creature* creature);

	//void MoveMap(?);
	//void Pause(?);
	
	void _printMap();
	void PrintMap();
	int GetPlayerLocation();
	vector<int> GetMonsterLocation();
	int GetObjectLocation();
	vector<int> LocationToCoordinate(int location);
	int CoordinateToLocation(vector<int> coordinate);
	int IntCoordinateToLocation(int x, int y);
	void MoveEvent(int playerLocation, vector<int> nextCoordinate);
	void MoveMonsterEvent(int playerLocation, vector<int> nextCoordinate);
	bool bIsObstacle(int x, int y);
	bool bIsObject(int location);
	bool bIsEnemy(int location);
	bool bIsPlayer(int location);
};
