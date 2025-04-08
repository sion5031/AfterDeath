#include <functional>

#include "Creature.h"
//#include "Player.h"
//#include "Monster.h"
#include "IConsumable.h"
#include "ConsoleGotoxy.h"

vector<string>* Creature::Notifications = new vector<string>;
string Creature::PlayerName;

COORD POS;

void notificationErase(int x, int y, int line)
{
	Gotoxy(x, y);
	GotoxyClsLong(line);
}

Creature::Creature()
{
	Equipments = new EquipedE;
}

void Creature::InitCreature()
{
	Hp = MaxHp;
	Mp = MaxMp;
	Equipments->InitEquipedE();
}

void Creature::Fight(shared_ptr<Creature> player, shared_ptr<Creature> monster, int turn)
{
	//system("cls");

	int countTurn = turn;
	char t;

	vector<function<void(int)>> PlayerDurationSkills;
	//vector<UseSkillFuncPtr> MonsterDurationSkills;


	//==========

	// 출력 부(캐릭터, 상태, 
	system("cls");

	//==========

	while (true)
	{
		//상태 갱신
		string strTurn;
		GotoxyPrintReturn(to_string(countTurn) + " 턴", 0, 0 );
		monster->PrintMonsterStatus(42, 0);
		//cout << countTurn << " 턴" << endl << endl; // 위에서 출력하고 지우지 않게 하기

		ReadFile(monster->GetName(), 40, 4);

		POS = GetCurrentXY();
		//====
		POS.X += 2;
		//====

		Gotoxy(0, 13);
		GotoxyClsShort(2);
		cout << "Hp: " << player->GetHp() << "/" << player->GetTotalStatus()->TotalMaxHp
			<< "\tAtk: " << player->GetTotalStatus()->TotalAtk << '\n'
			<< "Mp: " << player->GetMp() << "/" << player->GetTotalStatus()->TotalMaxMp
			<< "\tDef: " << player->GetTotalStatus()->TotalDef << "\n"
			<< "====================\n";

		if (countTurn % 2 == 0)
		{
			GotoxyPreparePrintMenu();
			cout << "1. 공격\t|\n2. 스킬\t|\n3. 가방\t|\n4. 포기\t|\n" << endl;
			t = _getche();
			GotoxyCll(1);

			Gotoxy(0, POS.Y);

			if (t == '1')
			{
				player->NormalAttack(player, monster, countTurn); // 의미 없는 주체...
			}
			else if (t == '2')
			{
				shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(player);
				if (addableCreature)
				{
					GotoxyPreparePrintMenu();
					addableCreature->DisplaySkills();
					//cout << "스킬을 선택하거나 나갑니다." << endl;
					char skillChar = _getche();
					GotoxyCll(1);
					int skillNum = skillChar - '1';

					Gotoxy(POS.X, POS.Y);
					player->UseSkill(monster, skillNum, countTurn);
					MonsterHitMotion(countTurn, monster->GetName(), player->GetName(), "color 4f");
					PlayerDurationSkills.push_back([&](int count) {player->UseSkill(monster, skillNum, count);});
				}
				
			}
			else if (t == '3')
			{
				shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(player);
				if (addableCreature)
				{
					GotoxyPreparePrintMenu();
					addableCreature->DisplayInventory();
					//cout << "아이템을 선택하거나 나갑니다.\n";
					char itemChar = _getche();
					GotoxyCll(1);
					int itemNum = itemChar - '1';

					Item* getItem = addableCreature->SelectInventoryItem(itemNum);
					if (getItem != nullptr)
					{
						IConsumable* consumable = dynamic_cast<IConsumable*>(getItem);
						consumable->UseItem(player);
						if (consumable->GetNumber() <= 0)
						{
							addableCreature->CheckZeroInventory();
						}
					}
				}
				
			}
			else if (t == '4')
			{

			}
		}
		else // 몬스터 턴 ================
		{
			Sleep(200);

			int num = rand() % 2; // 공격, 스킬 사용 빈도 몬스터에서 받아오기?

			if (num < 2)
			{
				notificationErase(0, POS.Y, 6);
				monster->NormalAttack(monster, player, countTurn);
			}
			else if (num == 2)
			{
				notificationErase(0, POS.Y, 6);
				int num = 0;// 수정!!!
				monster->UseSkill(player, num, countTurn);
			}
			else
			{
				//예외?
			}

		}

		if (player->GetHp() <= 0 || monster->GetHp() <= 0)
		{
			break;
		}
		countTurn++;
			

		// 지속 스킬 구현부
		//for (int i = 0;i < PlayerDurationSkills.size();i++)
		//{
		//	PlayerDurationSkills[i](countTurn);
		//}

	}

	//초기화(상태 및 delete)
	//system("cls");
	Gotoxy(0, 0);
	GotoxyClsLong(17);
	//Notifications->clear();

}

void Creature::NormalAttack(shared_ptr<Creature> attacker, shared_ptr<Creature> defender, int countTurn) //방어력 계산 필요
{
	//cout << "atk: " << attacker->GetTotalStatus()->TotalAtk << ", def: " << defender->GetTotalStatus()->TotalDef << endl;
	int before = defender->Hp;
	defender->CalcHp(-attacker->GetTotalStatus()->TotalAtk);
	int after = defender->Hp;
	//cout << defender->GetName() << "가 " << before - after << " 만큼의 피해를 입었습니다.     ";
	
	// 6줄 날리기 길게
	notificationErase(0, POS.Y, 6);
	string difference = to_string(before - after);
	AddNotification(defender->GetName() + " 가 " + difference + " 만큼의 피해를 입었습니다.     ");
	//GotoxyPrintXReturn("                                                  ", 0);
	
	MonsterHitMotion(countTurn, defender->GetName(), attacker->GetName(), "color 04");
}

void Creature::MonsterHitMotion(int countTurn, string defender, string attacker, string color)
{
	if (countTurn % 2 == 0)
	{
		//system(color.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		ReadFile(defender, 42, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	else
	{
		//system(color.c_str());
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		ReadFile(attacker, 40, 2);
		Sleep(200);
		ReadFile(attacker, 30, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Sleep(500);
	}
	Sleep(300);
	if (countTurn % 2 == 0)
	{
		//system("color 0f");
		ReadFile(defender, 40, 4);
	}
	else
	{
		//system("color 0f");
		ReadFile(attacker, 40, 12);
	}
	Sleep(700);
}

void Creature::PrintMonsterStatus(int x, int y)
{
	GotoxyPrintReturn("<"+Name+">", x, y);
	Gotoxy(x, y+1);
	int maxHp = GetTotalStatus()->TotalMaxHp/10;
	int currentHp = GetHp()/10;
	if (currentHp == 0 && GetHp() > 0)
	{
		currentHp = 1;
	}
	cout << "[";
	for (int i = 0;i < currentHp;i++)
	{
		cout << '=';
	}
	for (int i = 0;i < maxHp - currentHp;i++)
	{
		cout << '-';
	}
	cout << "]";
}

void Creature::CalcHp(int hp)
{
	if (hp < 0)// 데미지 계산
	{
		if (GetTotalStatus()->TotalDef >= -hp)
		{
			hp /= 10;
		}
		else
		{
			hp += GetTotalStatus()->TotalDef;//논리상 오류. 1/10보다 작은 경우 발생
		}
	}
	
	//데미지 적용
	if (Hp + hp <= 0)
	{
		Hp = 0;
		Die();
	}
	else
	{
		Hp += hp;
		if (Hp > MaxHp)
		{
			Hp = MaxHp;
		}
	}
	
}

void Creature::CalcMp(int mp)
{
	Mp += mp;

	if (Mp + mp <= 0)
	{
		Mp = 0;
	}
	if (Mp > MaxMp)
	{

		Mp += mp;
		Mp = MaxMp;
	}
}


void Creature::ReadFile(string fileName, int start, int erase)
{
	ifstream in("..\\"+fileName+".txt");
	string s;
	int line = 2;

	if (in.is_open()) {
		while (!in.eof())
		{
			getline(in, s);
			Gotoxy(start, line);
			GotoxyPrintXReturn("                                                  ", start - erase);
			//Gotoxy(start, line);
			cout<< s << std::endl;
			line++;
		}
	}
	else {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
	}
	in.close();
}

Status* Creature::GetTotalStatus()
{
	Status* totalStatus = new Status;

	int atkSum = Attack;
	int defSum = Defense;
	int maxHpSum = MaxHp;
	int maxMpSum = MaxMp;

	if (Equipments->myWeapon != nullptr)
	{
		atkSum += Equipments->myWeapon->GetAtkPoint();
		defSum += Equipments->myWeapon->GetDefPoint();
		maxHpSum += Equipments->myWeapon->GetHpPoint();
		maxMpSum += Equipments->myWeapon->GetMpPoint();
	}
	if (Equipments->myUpper != nullptr)
	{
		atkSum += Equipments->myUpper->GetAtkPoint();
		defSum += Equipments->myUpper->GetDefPoint();
		maxHpSum += Equipments->myUpper->GetHpPoint();
		maxMpSum += Equipments->myUpper->GetMpPoint();
	}
	if (Equipments->myLower != nullptr)
	{
		atkSum += Equipments->myLower->GetAtkPoint();
		defSum += Equipments->myLower->GetDefPoint();
		maxHpSum += Equipments->myLower->GetHpPoint();
		maxMpSum += Equipments->myLower->GetMpPoint();
	}
	if (Equipments->myGlove != nullptr)
	{
		atkSum += Equipments->myGlove->GetAtkPoint();
		defSum += Equipments->myGlove->GetDefPoint();
		maxHpSum += Equipments->myGlove->GetHpPoint();
		maxMpSum += Equipments->myGlove->GetMpPoint();
	}
	if (Equipments->myShoes != nullptr)
	{
		atkSum += Equipments->myShoes->GetAtkPoint();
		defSum += Equipments->myShoes->GetDefPoint();
		maxHpSum += Equipments->myShoes->GetHpPoint();
		maxMpSum += Equipments->myShoes->GetMpPoint();
	}
	if (Equipments->myShield != nullptr)
	{
		atkSum += Equipments->myShield->GetAtkPoint();
		defSum += Equipments->myShield->GetDefPoint();
		maxHpSum += Equipments->myShield->GetHpPoint();
		maxMpSum += Equipments->myShield->GetMpPoint();
	}
	
	totalStatus->TotalAtk = atkSum;
	totalStatus->TotalDef = defSum;
	totalStatus->TotalMaxHp = maxHpSum;
	totalStatus->TotalMaxMp = maxMpSum;

	return totalStatus;
}


void Creature::SetName(string Name)
{
	this->Name = Name;
}

void Creature::SetType(int Type)
{
	this->Type = Type;
}

void Creature::SetMaxHp(int MaxHp)
{
	this->MaxHp = MaxHp;
}

void Creature::SetHp(int Hp)
{
	this->Hp = Hp;
}

void Creature::SetMaxMp(int MaxMp)
{
	this->MaxMp = MaxMp;
}

void Creature::SetMp(int Mp)
{
	this->Mp = Mp;
}

void Creature::SetAtk(int Atk)
{
	this->Attack = Atk;
}

void Creature::SetDef(int Def)
{
	this->Defense = Def;
}

//void Creature::AddNotification(string notification)
//{
//	Notifications->push_back(notification);
//	if (Notifications->size() > 6)
//	{
//		Notifications->erase(Notifications->begin());
//	}
//	GotoxyPreparePrintSituation();
//	for (int i = 0;i < Notifications->size();i++)
//	{
//		cout << Notifications->at(i) << '\n';
//	}
//}

void Creature::AddNotification(string notification)
{
	int position;
	int index = 0;
	string str;

	Notifications->push_back(notification);
	if (Notifications->size() > 6)
	{
		Notifications->erase(Notifications->begin());
	}
	
	GotoxyPreparePrintSituation();
	for (int i = 0;i < Notifications->size();i++)
	{
		bool bPrint = false;
		str = Notifications->at(i);
		while ((position = str.find(' ', index)) != string::npos)
		{
			int len = position - index;
			string result = str.substr(index, len);
			if (result == PlayerName)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << result;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				result = str.substr(len + 1, str.length() - len);
				cout << result << "\n";
				bPrint = true;
			}
			else if (result == "스켈레톤" || result == "드래곤")
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << result;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				result = str.substr(len + 1, str.length() - len);
				cout << result << "\n";
				bPrint = true;
			}

			//index = position + 1;
			break; // 첫번째 단어만 체크 가능하게 됨
		}
		if (bPrint == false)
		{
			cout << Notifications->at(i) << '\n';
		}
	}
}

string Creature::GetName()
{
	return Name;
}

int Creature::GetType()
{
	return Type;
}

//int Creature::GetMaxHp()
//{
//	return MaxHp;
//}

int Creature::GetHp()
{
	return Hp;
}

//int Creature::GetMaxMp()
//{
//	return MaxMp;
//}

int Creature::GetMp()
{
	return Mp;
}

int Creature::GetAttack()
{
	return Attack;
}

int Creature::GetDefense()
{
	return Defense;
}

EquipedE* Creature::GetEquipments()
{
	return Equipments;
}
