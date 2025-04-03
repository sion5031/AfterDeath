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

	CreaturesLocation = new map<int, weak_ptr<Creature>>;
	ObjectsLocation = new map<int, MapObjects*>;

	//=======
	//shared_ptr<Creature> Monster1 = make_shared<Monster>();
	//this->AddCreature(36, Monster1);

	//=======



	cout << "맵을 생성했습니다." << endl;
}

Map::Map(shared_ptr<Creature> player)
{
	Name = "Start Map";
	MaxMonster = 3;
	MaxTreasure = 2;

	Obstacles = new bool* [MapSize];
	for (int i = 0; i < MapSize;i++)
	{
		Obstacles[i] = new bool[MapSize];
		std::fill(Obstacles[i], Obstacles[i] + MapSize, true);
	}
	FillMap();

	CreaturesLocation = new map<int, weak_ptr<Creature>>;
	ObjectsLocation = new map<int, MapObjects*>;

	//===================
	//Creature* monster1 = new Monster();

	CreaturesLocation->insert({ 16, player });
	//CreaturesLocation->insert({ 28, player });


	//===================

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
	vector<int> locations = GetMonsterLocation();

	for (auto i : locations)
	{
		vector<int> temCoordinate;

		vector<int> coordinate = LocationToCoordinate(i);

		int ran = rand() % 5;

		if (ran == 0)
		{
			temCoordinate.push_back(coordinate[0] - 1); // 예외처리 범위로...
			temCoordinate.push_back(coordinate[1]);
			MoveMonsterEvent(i, temCoordinate);

		}
		else if (ran == 1)
		{
			temCoordinate.push_back(coordinate[0]);
			temCoordinate.push_back(coordinate[1] - 1);
			MoveMonsterEvent(i, temCoordinate);
		}
		else if (ran == 2)
		{
			temCoordinate.push_back(coordinate[0] + 1);
			temCoordinate.push_back(coordinate[1]);
			MoveMonsterEvent(i, temCoordinate);
		}
		else if (ran == 3)
		{
			temCoordinate.push_back(coordinate[0]);
			temCoordinate.push_back(coordinate[1] + 1);
			MoveMonsterEvent(i, temCoordinate);
		}
		else if (ran == 4)
		{
			//temCoordinate.push_back(coordinate[0]);
			//temCoordinate.push_back(coordinate[1]);
			//MoveMonsterEvent(i, temCoordinate);
		}
	}

}

void Map::UsePortal(int location)
{
}

void Map::AddCreature(int location, shared_ptr<Creature> creature)
{
	vector<int> coordinate = LocationToCoordinate(location);
	if (!bIsObstacle(coordinate[0], coordinate[1]) && !bIsObject(location) && !bIsEnemy(location) && !bIsPlayer(location))
	{
		CreaturesLocation->insert({ location, creature });
	}
	else
	{
		cout << "자리 있음!!!" << endl;
	}
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

void Map::PrintMap()
{
	for (int i = 0;i < MapSize;i++)
	{
		for (int j = 0;j < MapSize;j++) {
			if (bIsObstacle(i, j)) cout << "* ";
			else if (bIsObject(IntCoordinateToLocation(i, j)))cout << "! ";
			else if (bIsEnemy(IntCoordinateToLocation(i, j)))cout << "X ";
			else if (bIsPlayer(IntCoordinateToLocation(i, j)))cout << "O ";
			else cout << "  ";
		}
		cout << endl;
	}
}

shared_ptr<Creature> Map::GetCreature(int location)
{
	auto it = CreaturesLocation->find(location);
	if (it != CreaturesLocation->end()) {
		shared_ptr<Creature> creature = it->second.lock();  // weak_ptr → shared_ptr 변환
		return creature; //살아 있으면 shared_ptr 반환 (nullptr이 아님)
	}
	return nullptr;
}

int Map::GetPlayerLocation()
{
	for (int i = 0;i < MapSize * MapSize;i++)
	{
		if (bIsPlayer(i))
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
		if (bIsEnemy(i))
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

int Map::IntCoordinateToLocation(int x, int y)
{
	int location = x * MapSize + y;
	return location;
}

void Map::MoveEvent(int playerLocation, vector<int> nextCoordinate)
{
	int x = nextCoordinate[0];
	int y = nextCoordinate[1];
	int nextLocation = CoordinateToLocation(nextCoordinate);
	shared_ptr<Creature> player = GetCreature(playerLocation);

	if (bIsObstacle(x, y)) // 하위 항목들을 맵에서 겹칠 수 있게 하려면 if문으로 바꾸고 순서 조정
	{
		// Do nothing
	}
	else if (bIsObject(nextLocation))
	{
		
		shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(player);
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
		shared_ptr<Creature> tem = GetCreature(nextLocation);
		player->Fight(player, GetCreature(nextLocation), 0);
		//DeathChecker(player, tem);
		//DeleteChecker();
		//아마도 출력

	}
	else
	{
		//CreaturesLocation[nextLocation] = move(CreaturesLocation[playerLocation]);//되려나
		CreaturesLocation->insert({ nextLocation, CreaturesLocation->at(playerLocation) });//되려나
		CreaturesLocation->erase(playerLocation);
	}
}

void Map::MoveMonsterEvent(int monsterLocation, vector<int> nextCoordinate) // MoveEvent와 합칠 수?
{
	int x = nextCoordinate[0];
	int y = nextCoordinate[1];
	int nextLocation = CoordinateToLocation(nextCoordinate);
	shared_ptr<Creature> monster = GetCreature(monsterLocation);

	if (bIsObstacle(x, y)) // 하위 항목들을 맵에서 겹칠 수 있게 하려면 if문으로 바꾸고 순서 조정
	{
		// Do nothing
	}
	else if (bIsObject(nextLocation))
	{
		// Do nothing
	}
	else if (bIsPlayer(nextLocation))
	{
		cout << "습격받음!" << endl;
		monster->Fight(GetCreature(nextLocation), monster, 1);
	}
	else
	{
		//CreaturesLocation[nextLocation] = move(CreaturesLocation[monsterLocation]);//되려나
		CreaturesLocation->insert({ nextLocation, CreaturesLocation->at(monsterLocation) });
		CreaturesLocation->erase(monsterLocation);
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
	if (CreaturesLocation->find(location) != CreaturesLocation->end()&& GetCreature(location)->GetType()!=0)
	{
		return true;
	}
	return false;
}

bool Map::bIsPlayer(int location)
{
	if (CreaturesLocation->find(location) != CreaturesLocation->end() && GetCreature(location)->GetType() == 0)
	{
		return true;
	}
	return false;
}

//void Map::DeathChecker(shared_ptr<Creature> player, shared_ptr<Creature> monster)
//{
//	if (monster->GetHp() <= 0)
//	{
//		monster.reset();
//	}
//	else if (player->GetHp() <= 0)
//	{
//		//=======================
//		
//	}
//}

void Map::DeathChecker()
{
	for (int i = 0;i < MapSize * MapSize;i++)
	{
		if (CreaturesLocation->find(i) != CreaturesLocation->end())
		{
			if (GetCreature(i)->GetHp() <= 0 && GetCreature(i)->GetType() == 0)
			{
				if (GetCreature(i)->GetType() == 0)
				{
					//GetCreature(i).reset();
					break;
				}
				else if (GetCreature(i)->GetType() > 0)
				{
					GetCreature(i).reset();
					break;
				}
				else
				{
					cout << "Creature Type Error" << endl;
				}
			}
		}
	}
}

void Map::DeleteChecker()
{
	//for (auto it = CreaturesLocation->begin(); it != CreaturesLocation->end(); ) {
	//	if (it->second.expired()) {  // Creature가 소멸되었는지 확인
	//		std::cout << "Removing creature ID: " << it->first << std::endl;
	//		it = CreaturesLocation->erase(it);  // 소멸된 객체 제거
	//	}
	//	else {
	//		++it;
	//	}
	//}
	for (auto it = CreaturesLocation->begin(); it != CreaturesLocation->end(); ) {
		if (it->second.expired()) {  // Creature가 소멸되었는지 확인
			std::cout << "Removing creature ID: " << it->first << std::endl;
			it = CreaturesLocation->erase(it);  // 소멸된 객체 제거
		}
		else {
			++it;
		}
	}
}

void Map::SetName(string name)
{
	Name = name;
}

string Map::GetName()
{
	return Name;
}
