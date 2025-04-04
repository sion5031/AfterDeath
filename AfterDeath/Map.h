#pragma once
#include <iostream>
#include <map>
#include <Windows.h>
#include <conio.h>

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Treasure.h"
#include "Portal.h"
#include "IPlayable.h"

using namespace std;

struct MapObjects
{
	Treasure* Treasure = nullptr;
	Item* Item = nullptr;
	Portal* Portal = nullptr;
};

class Map
{

private:
	int Num;
	string Name;
	int MaxMonster; //쓰나??
	int MaxTreasure;
	int StartLocation;
	bool** Obstacles;
	map<int, weak_ptr<Creature>>* CreaturesLocation;
	map<int, MapObjects*>* ObjectsLocation;
	const int MapSize = 15;

	void FillMap();

public:
	Map();
	Map(int num);
	Map(shared_ptr<Creature> player); // 쓰나?
	~Map();

	void MovePlayer();
	void MoveMonster();
	void UsePortal(int location);

	void AddCreature(int location, shared_ptr<Creature> creature);
	void AddObject(int location, MapObjects* mapObjects);

	//void MoveMap(?);
	//void Pause(?);
	
	void _printMap();
	void PrintMap();
	shared_ptr<Creature> GetCreature(int location);
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

	const int GetMapSize();

	void DeathChecker();
	void DeleteChecker();
	void DeletePlayer();

	void SetNum(int num);
	int GetNum();
	void SetName(string name);
	string GetName();
	void SetStartLocation(int location);
	int GetStartLocation();
};
