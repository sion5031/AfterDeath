#include <conio.h>

#include "Map.h"
#include "HpPotion.h"
#include "MpPotion.h"
#include "ShortSword.h"
#include "FireBall.h"
#include "IncreaseAttack.h"
#include "AttackUp.h"
#include "ConsoleGotoxy.h"

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

void Map::FillMapLine(int rowNum, int startNum, int endNum)
{
	for (int i = startNum;i < endNum;i++)
	{
		Obstacles[i][rowNum] = true;
	}
}

Map::Map()
{
	Num = 0; // 만드는 곳에서!!! 되도록이면 GM에서
	Name = "Start Map";
	MaxMonster = 3;
	MaxTreasure = 2;
	StartLocation = 16;

	Obstacles = new bool*[MapSize];
	for (int i = 0; i < MapSize;i++)
	{
		Obstacles[i] = new bool[MapSize];
		std::fill(Obstacles[i], Obstacles[i] + MapSize, true);
	}
	FillMap();

	CreaturesLocation = new map<int, weak_ptr<Creature>>;
	ObjectsLocation = new map<int, MapObjects*>;

}

Map::Map(int num)
{
	Num = num; // 만드는 곳에서!!! 되도록이면 GM에서
	StartLocation = 16;//수정

	Obstacles = new bool* [MapSize];
	for (int i = 0; i < MapSize;i++)
	{
		Obstacles[i] = new bool[MapSize];
		std::fill(Obstacles[i], Obstacles[i] + MapSize, true);
	}
	FillMap();

	CreaturesLocation = new map<int, weak_ptr<Creature>>;
	ObjectsLocation = new map<int, MapObjects*>;

	if (num == 0)
	{
		
		Name = "버려진 성지";
		MaxMonster = 3;
		MaxTreasure = 2;
		StartLocation = 16;
		
		//맵 장애물 만들고
		std::fill(Obstacles[3] + 2, Obstacles[3] + 6, true);
		FillMapLine(9, 1, 8);
		FillMapLine(4, 6, 14);

		// 보물 넣고
		MapObjects* dropObject = new MapObjects;
		dropObject->Treasure = new Treasure();

		Item* newPotion = new HpPotion(1);
		dropObject->Treasure->AddItems(newPotion);

		ObjectsLocation->insert({ 41, dropObject });
		
		// 포털 넣고
	}
	if (num == 1)
	{

		Name = "관문";
		MaxMonster = 3;
		MaxTreasure = 2;
		StartLocation = 16;

		//맵 장애물 만들고
		FillMapLine(3, 6, 14);
		FillMapLine(5, 1, 11);
		FillMapLine(9, 6, 14);
		FillMapLine(11, 1, 8);

		// 보물 넣고 // 관리 어디서?
		MapObjects* dropObject1 = new MapObjects;
		MapObjects* dropObject2 = new MapObjects;
		dropObject1->Treasure = new Treasure();
		dropObject2->Treasure = new Treasure();

		Item* newPotion = new MpPotion(2);
		Item* newEquipment = new ShortSword(2);
		Skill* newSkill = new FireBall(2);
		dropObject1->Treasure->AddItems(newPotion);
		dropObject1->Treasure->AddItems(newEquipment);
		dropObject2->Treasure->SetNewSkill(newSkill);

		ObjectsLocation->insert({ 181, dropObject1 });
		ObjectsLocation->insert({ 28, dropObject2 });

		// 포털 넣고
	}
	if (num == 2)
	{

		Name = "드래곤 둥지";
		MaxMonster = 3;
		MaxTreasure = 2;
		StartLocation = 16;

		//맵 장애물 만들고
		// 보물 넣고 // 관리 어디서?
		// 포털 넣고
	}
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

	CreaturesLocation->insert({ 16, player });

}

Map::~Map()
{
}

int Map::MovePlayer()
{
	if (bRealTime == false)
	{
		char t;

		t = _getche();
		GotoxyCll(1);
		//GotoxyClsLong(1);

		return MoveCondition(t);
	}

	else
	{
		while (true)
		{
			if (_kbhit())
			{
				char t = _getch();
				GotoxyCll(1);
				//GotoxyClsLong(1);

				return MoveCondition(t);
			}
			else
			{
				Sleep(100);
				return -1;
			}
		}
	}
}

int Map::MoveCondition(char t)
{
	int location = GetPlayerLocation();
	vector<int> coordinate = LocationToCoordinate(location);
	vector<int> temCoordinate;

	if (t == 'a' || t == 'A')
	{
		temCoordinate.push_back(coordinate[0] - 1); // 예외처리 범위로...
		temCoordinate.push_back(coordinate[1]);
		return MoveEvent(location, temCoordinate);

	}
	else if (t == 'w' || t == 'W')
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] - 1);
		return MoveEvent(location, temCoordinate);
	}
	else if (t == 'd' || t == 'D')
	{
		temCoordinate.push_back(coordinate[0] + 1);
		temCoordinate.push_back(coordinate[1]);
		return MoveEvent(location, temCoordinate);
	}
	else if (t == 's' || t == 'S')
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] + 1);
		return MoveEvent(location, temCoordinate);
	}
	else if (t == 'i' || t == 'I')
	{
		Item* getItem;
		shared_ptr<Creature> player = GetCreature(location);

		shared_ptr<Player> playableCreature = dynamic_pointer_cast<Player>(player);
		if (playableCreature)
		{
			char itemChar;
			int itemNum;

			system("cls");
			//playableCreature->DisplayInventory();
			playableCreature->DisplayInventoryDetail();

			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			itemChar = _getche();
			GotoxyCll(1);
			system("cls");

			itemNum = itemChar - '1';

			getItem = playableCreature->SelectInventoryItem(itemNum);
			if (getItem != nullptr)
			{
				IConsumable* consumable = dynamic_cast<IConsumable*>(getItem);
				playableCreature->AddNotification(consumable->UseItem(player));
				if (consumable->GetNumber() <= 0)
				{
					playableCreature->CheckZeroInventory();
				}
			}
		}
	}
	else if (t == 'j' || t == 'J')
	{
		shared_ptr<Creature> player = GetCreature(location);
		shared_ptr<IPlayable> displayableCreature = dynamic_pointer_cast<IPlayable>(player);
		displayableCreature->DisplaySkillsDetail();
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		_getche();
		//GotoxyCll(1);
		system("cls");
	}
	else
	{
		//??
	}
	return -1;
}

int Map::MoveMonster(int location)
{
	vector<int> temCoordinate;

	vector<int> coordinate = LocationToCoordinate(location);

	int ran;

	if (bRealTime == true)
	{
		ran = rand() % 20;
	}
	else
	{
		ran = rand() % 5;
	}

	if (ran == 0)
	{
		temCoordinate.push_back(coordinate[0] - 1); // 예외처리 범위로...
		temCoordinate.push_back(coordinate[1]);
		return MoveMonsterEvent(location, temCoordinate);

	}
	else if (ran == 1)
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] - 1);
		return MoveMonsterEvent(location, temCoordinate);
	}
	else if (ran == 2)
	{
		temCoordinate.push_back(coordinate[0] + 1);
		temCoordinate.push_back(coordinate[1]);
		return MoveMonsterEvent(location, temCoordinate);
	}
	else if (ran == 3)
	{
		temCoordinate.push_back(coordinate[0]);
		temCoordinate.push_back(coordinate[1] + 1);
		return MoveMonsterEvent(location, temCoordinate);
	}
	else if (ran == 4)
	{
		return -1;
	}
	return -1;
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

void Map::AddObject(int location, MapObjects* mapObjects)
{
	vector<int> coordinate = LocationToCoordinate(location);
	if (!bIsObstacle(coordinate[0], coordinate[1]) && !bIsObject(location) && !bIsEnemy(location) && !bIsPlayer(location))
	{
		ObjectsLocation->insert({ location, mapObjects });
	}
	else
	{
		cout << "자리 있음!!!" << endl;
	}
}

void Map::PrintMap()
{
	GotoxyClsLong(1);
	Gotoxy(SCREEN_START_X*2, SCREEN_START_Y - 1);
	GotoxyClsLong(1);
	cout << "<" << GetName() << ">";
	for (int i = 0;i < MapSize;i++)
	{
		for (int j = 0;j < MapSize;j++) {
			Gotoxy((i + SCREEN_START_X) * 2, j + SCREEN_START_Y + 1);
			if (bIsObstacle(i, j)) cout << "■";
			else if (bIsObject(IntCoordinateToLocation(i, j)))
			{
				vector<int> temCoor = { i,j };
				int temLoc = CoordinateToLocation(temCoor);
				if(ObjectsLocation->at(temLoc)->Portal != nullptr)cout << "♨";
				else cout << "! ";
			}
			else if (bIsObject(IntCoordinateToLocation(i, j)))cout << "! ";
			else if (bIsEnemy(IntCoordinateToLocation(i, j)))cout << "Ｘ";
			else if (bIsPlayer(IntCoordinateToLocation(i, j)))cout << "○";
			else cout << "  ";
		}
		cout << endl;
	}	
	GotoxyPrintReturn(" ○ - 플레이어", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 1);
	GotoxyPrintReturn(" Ｘ - 몬스터", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 2);
	GotoxyPrintReturn(" ! - 오브젝트", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 3);
	GotoxyPrintReturn(" ♨ - 포털", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 4);
	GotoxyPrintReturn(" ■ - 장애물", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 5);
	GotoxyPrintReturn(" i 버튼 - 인벤토리", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 7);
	GotoxyPrintReturn(" j 버튼 - 스킬상세", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 8);
	GotoxyPrintReturn(" Enter - 확인 및 스킵", (MapSize + SCREEN_START_X) * 2, SCREEN_START_Y + 9);

	shared_ptr<Creature> player = GetCreature(GetPlayerLocation());
	Gotoxy(SCREEN_START_X * 2, SCREEN_START_Y + MapSize + 1);
	GotoxyClsShort(1);
	cout.width(17);
	cout << left << "HP: " + to_string(player->GetHp()) + "/" + to_string(player->GetTotalStatus()->TotalMaxHp);
	cout << "Atk: " << player->GetTotalStatus()->TotalAtk;
	Gotoxy(SCREEN_START_X * 2, SCREEN_START_Y + MapSize + 2);
	GotoxyClsShort(1);
	cout.width(17);
	cout << left << "MP: " + to_string(player->GetMp()) + "/" + to_string(player->GetTotalStatus()->TotalMaxMp);
	cout << "Def: " << player->GetTotalStatus()->TotalDef << "\n";

	Gotoxy(0, 18);
	//GotoxyClsLong(6);
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

int Map::MoveEvent(int playerLocation, vector<int> nextCoordinate)
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
			if (ObjectsLocation->at(nextLocation)->Treasure != nullptr)
			{
				for (auto i : *(ObjectsLocation->at(nextLocation)->Treasure->GetItems()))
				{
					addableCreature->AddInventory(i);
				}
				if (ObjectsLocation->at(nextLocation)->Treasure->GetNewSkill() != nullptr)
				{
					addableCreature->AddSkill(ObjectsLocation->at(nextLocation)->Treasure->GetNewSkill());
					ObjectsLocation->at(nextLocation)->Treasure->SetNewSkill(nullptr);
				}
			}
			if (ObjectsLocation->at(nextLocation)->Item != nullptr)
			{
				addableCreature->AddInventory(ObjectsLocation->at(nextLocation)->Item);
			}
			if (ObjectsLocation->at(nextLocation)->Portal != nullptr)
			{
				return ObjectsLocation->at(nextLocation)->Portal->GetPortalInfo();
			}
			else
			{
				delete ObjectsLocation->at(nextLocation);
				ObjectsLocation->erase(nextLocation);
			}
		}
	}
	else if (bIsEnemy(nextLocation))
	{
		shared_ptr<Creature> tem = GetCreature(nextLocation);
		player->Fight(player, GetCreature(nextLocation), 0);
		if (player->GetHp() <= 0)
		{
			// 그냥 흐르게?
		}
		if (GetCreature(nextLocation)->GetHp() <= 0)
		{
			EquipedE* dropItem = new EquipedE;
			dropItem = GetCreature(nextLocation)->GetEquipments();

			MapObjects* dropObject = new MapObjects;
			dropObject->Treasure = new Treasure();

			// 장비 드랍
			for (int i = 0;i < 6;i++)
			{
				if (dropItem->GetItem(i) != nullptr && dropItem->GetItem(i)->GetSN() == 30)
				{
					return -100;
				}
			}
			int ran = rand() % 6;

			if (dropItem->GetItem(ran) != nullptr)
			{
				dropObject->Item = dropItem->GetItem(ran);
			}
			

			//소모품 드랍(랜덤 생성)
			ran = rand() % 6;

			if (ran % 3 == 1)
			{
				ran = rand() % 6;
				HpPotion* hpPotion = new HpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(hpPotion);
			}
			else if (ran % 3 == 2)
			{
				ran = rand() % 6;
				MpPotion* mpPotion = new MpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(mpPotion);
			}
			else
			{
				ran = rand() % 5;
				HpPotion* hpPotion = new HpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(hpPotion);
				ran = rand() % 5;
				MpPotion* mpPotion = new MpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(mpPotion);
			}

			// 스킬 드랍
			ran = rand() % (GetCreature(nextLocation)->GetSkills()->size() * 2); // 확률 50%

			if (ran < GetCreature(nextLocation)->GetSkills()->size())
			{
				dropObject->Treasure->SetNewSkill(GetCreature(nextLocation)->GetSkills()->at(ran));
			}

			ObjectsLocation->insert({ nextLocation, dropObject });
		}


	}
	else
	{
		//CreaturesLocation[nextLocation] = move(CreaturesLocation[playerLocation]);//되려나
		CreaturesLocation->insert({ nextLocation, CreaturesLocation->at(playerLocation) });//되려나
		CreaturesLocation->erase(playerLocation);
	}
	return -1;
}

int Map::MoveMonsterEvent(int monsterLocation, vector<int> nextCoordinate) // MoveEvent와 합칠 수?
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

		shared_ptr<Creature> player = GetCreature(nextLocation);

		if (player->GetHp() <= 0)
		{
			// 그냥 흐르게?
		}
		if (monster->GetHp() <= 0)
		{
			EquipedE* dropItem = new EquipedE;
			dropItem = monster->GetEquipments();

			MapObjects* dropObject = new MapObjects;
			dropObject->Treasure = new Treasure();

			// 장비 드랍
			for (int i = 0;i < 6;i++)
			{
				if (dropItem->GetItem(i) != nullptr && dropItem->GetItem(i)->GetSN() == 30)
				{
					return -100;
				}
			}
			int ran = rand() % 6;

			if (dropItem->GetItem(ran) != nullptr)
			{
				dropObject->Item = dropItem->GetItem(ran);
			}


			//소모품 드랍(랜덤 생성)
			ran = rand() % 6;

			if (ran % 3 == 1)
			{
				ran = rand() % 6;
				HpPotion* hpPotion = new HpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(hpPotion);
			}
			else if (ran % 3 == 2)
			{
				ran = rand() % 6;
				MpPotion* mpPotion = new MpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(mpPotion);
			}
			else
			{
				ran = rand() % 5;
				HpPotion* hpPotion = new HpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(hpPotion);
				ran = rand() % 5;
				MpPotion* mpPotion = new MpPotion(ran % 3 + 1);
				dropObject->Treasure->AddItems(mpPotion);
			}

			// 스킬 드랍
			ran = rand() % (monster->GetSkills()->size() * 2); // 확률 50%

			if (ran < monster->GetSkills()->size())
			{
				dropObject->Treasure->SetNewSkill(monster->GetSkills()->at(ran));
			}

			ObjectsLocation->insert({ monsterLocation, dropObject });
		}
	}
	else if (bIsEnemy(nextLocation))
	{
		// 몬스터끼리 만날 경우
	}
	else
	{
		//CreaturesLocation[nextLocation] = move(CreaturesLocation[monsterLocation]);//되려나
		CreaturesLocation->insert({ nextLocation, CreaturesLocation->at(monsterLocation) });
		CreaturesLocation->erase(monsterLocation);
	}
	return -1;
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

const int Map::GetMapSize()
{
	return MapSize;
}

void Map::DeleteChecker()
{
	for (auto it = CreaturesLocation->begin(); it != CreaturesLocation->end(); ) //플레이어 소멸 가능성
	{
		if (it->second.expired())
		{  // Creature가 소멸되었는지 확인
			std::cout << "Removing creature ID: " << it->first << std::endl;
			it = CreaturesLocation->erase(it);  // 소멸된 객체 제거
		}
		else {
			++it;
		}
	}
}

void Map::DeletePlayer()
{
	CreaturesLocation->erase(GetPlayerLocation());
}

void Map::SetNum(int num)
{
	Num = num;
}

int Map::GetNum()
{
	return Num;
}

void Map::SetName(string name)
{
	Name = name;
}

string Map::GetName()
{
	return Name;
}

void Map::SetStartLocation(int location)
{
	StartLocation = location;
}

int Map::GetStartLocation()
{
	return StartLocation;
}
