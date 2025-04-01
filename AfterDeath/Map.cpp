#include "Map.h"

//string Name;
//int MaxMonster;
//int MaxTreasure;
//bool** Obstacles;
//map<int, Creature*> CreaturesLocation;
//map<int, struct MapObjects*> ObjectsLocation;

void Map::FillMap(bool** map)
{
	for (int i = 0;i < MapSize;i++)
	{
		if (i == 0 || i == MapSize - 1)
		{
			for (int j = 0;j < MapSize;j++)
			{
				map[i][j] = true;
			}
			continue;
		}
	}
}

Map::Map()
{
	Name = "Start Map";
	MaxMonster = 3;
	MaxTreasure = 2;
	Obstacles = new bool*[MapSize];
	for (int i = 0; i < MapSize;i++)
	{
		Obstacles[i] = new bool[MapSize];
		//std::fill(Obstacles[i], Obstacles + MapSize, true);
	}
}

Map::~Map()
{
}

void Map::MoveCreature()
{
}

