#include "Map.h"

//string Name;
//int MaxMonster;
//int MaxTreasure;
//bool** Obstacles;
//map<int, Creature*> CreaturesLocation;
//map<int, struct MapObjects*> ObjectsLocation;

void Map::FillMap()
{
	for (int i = 0;i < MapSize;i++)
	{
		if (i != 0 && i != MapSize - 1)
		{
			for (int j = 0;j < MapSize;j++)
			{
				if (j != 0 && j != MapSize - 1)
				{
					Obstacles[i][j] = false;
				}
			}
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
		std::fill(Obstacles[i], Obstacles[i] + MapSize, true);
	}
	FillMap();

	CreaturesLocation = new map<int, Creature*>;
	ObjectsLocation = new map<int, MapObjects*>;

	cout << "맵을 생성했습니다." << endl;
}

Map::~Map()
{
}

void Map::MovePlayer()
{
	char t;
	int location = GetPlayerLocation();
	vector<int> coordinate = LocationToCoordinate(location);	

	vector<int> temCoordinate;

	t = _getche();
	if (t == 'w')
	{
		temCoordinate.push_back(coordinate[0] - 1); // 예외처리 범위로...
		temCoordinate.push_back(coordinate[1]);
		MoveEvent(location, temCoordinate);

	}
	else if (t == 'a')
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] - 1);
		MoveEvent(location, temCoordinate);
	}
	else if (t == 's')
	{
		temCoordinate.push_back(coordinate[0] + 1);
		temCoordinate.push_back(coordinate[1]);
		MoveEvent(location, temCoordinate);
	}
	else if (t == 'd')
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] + 1);
		MoveEvent(location, temCoordinate);
	}
}

void Map::MoveMonster()
{
}

void Map::UsePortal(int location)
{
}

void Map::_printMap()
{
	for (int i = 0;i < MapSize;i++)
	{
		for (int j = 0;j < MapSize;j++) {
			if (Obstacles[i][j] == true) cout << "**";
			else cout << "  ";
		}
		cout << endl;
	}
}

int Map::GetPlayerLocation()
{
	for (int i = 0;i < MapSize * MapSize;i++)
	{
		if (CreaturesLocation->find(i) != CreaturesLocation->end() && CreaturesLocation->at(i)->GetType()==0)
		{
			return i;
		}
	}
}

vector<int> Map::GetMonsterLocation()
{
	vector<int> monsterLocation;
	for (int i = 0;i < MapSize * MapSize;i++)
	{
		if (CreaturesLocation->find(i) != CreaturesLocation->end() && CreaturesLocation->at(i)->GetType() != 0)
		{
			monsterLocation.push_back(i);
		}
	}
	return monsterLocation;
}

int Map::GetObjectLocation()
{
	return 0;
}

vector<int> Map::LocationToCoordinate(int location)
{
	vector<int> coordinate;

	coordinate.push_back(location / MapSize);
	coordinate.push_back(location % MapSize);

	return coordinate;
}

int Map::CoordinateToLocation(vector<int> coordinate)
{
	int location = coordinate.at(0) * MapSize + coordinate.at(1);
	return location;
}

void Map::MoveEvent(int playerLocation, vector<int> nextCoordinate)
{
	int x = nextCoordinate[0];
	int y = nextCoordinate[1];
	int nextLocation = CoordinateToLocation(nextCoordinate);
	Creature* player = CreaturesLocation->at(playerLocation);

	if (bIsObstacle(x, y)) // 하위 항목들을 맵에서 겹칠 수 있게 하려면 if문으로 바꾸고 순서 조정
	{
		// Do nothing
	}
	else if (bIsObject(nextLocation))
	{		
		IPlayable* addableCreature = dynamic_cast<IPlayable*>(player);
		if (addableCreature)
		{
			for (auto i : ObjectsLocation->at(nextLocation)->Treasure->GetItems())
			{
				addableCreature->AddInventory(i);
			}
			addableCreature->AddSkill(ObjectsLocation->at(nextLocation)->Treasure->GetNewSkill()); //없을 때 예외처리. 일단은 무조건 있게
		}
	}
	else if (bIsEnemy(nextLocation))
	{
		player->Fight(player, CreaturesLocation->at(nextLocation));
	}
	else
	{
		CreaturesLocation[nextLocation] = move(CreaturesLocation[playerLocation]);//되려나
		CreaturesLocation->erase(playerLocation);
	}
}

bool Map::bIsObstacle(int x, int y)
{
	if (Obstacles[x][y] == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::bIsObject(int location)
{
	if (ObjectsLocation->find(location) != ObjectsLocation->end())
	{
		return true;
	}
	return false;
}

bool Map::bIsEnemy(int location)
{
	if (CreaturesLocation->find(location) != CreaturesLocation->end())
	{
		return true;
	}
	return false;
}
