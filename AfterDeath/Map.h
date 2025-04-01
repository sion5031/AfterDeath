#pragma once
#include <iostream>
#include <map>

#include "Creature.h"
#include "Treasure.h"
#include "Portal.h"

using namespace std;

class Map
{
private:
	string Name;
	int MaxMonster;
	int MaxTreasure;
	bool** Obstacles;
	map<int, Creature*> CreaturesLocation;
	map<int, struct MapObjects*> ObjectsLocation;
	const int MapSize = 15;

	void FillMap(bool** map);

public:
	Map();
	~Map();

	void MoveCreature();

};

struct MapObjects
{
	bool Presence = false;
	Treasure* Treasure = nullptr;
	Item* Item = nullptr;
	Portal* Portal = nullptr;
};