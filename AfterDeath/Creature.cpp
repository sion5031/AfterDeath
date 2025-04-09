#include <functional>

#include "Creature.h"
//#include "Player.h"
//#include "Monster.h"
#include "IConsumable.h"
#include "ConsoleGotoxy.h"
#include "Config.h"

vector<string>* Creature::Notifications = new vector<string>;
string Creature::PlayerName;

COORD POS;

void notificationErase(int x, int y, int line)
{
	//Gotoxy(SCREEN_START_X + x, SCREEN_START_Y + y);
	Gotoxy( x, y + 3);
	GotoxyClsLong(line);
}

Creature::Creature()
{
	Equipments = new EquipedE;
}

void Creature::InitCreature()
{
	Hp = GetTotalStatus()->TotalMaxHp;
	Mp = GetTotalStatus()->TotalMaxMp;
	Equipments->InitEquipedE();
}

void Creature::Fight(shared_ptr<Creature> player, shared_ptr<Creature> monster, int turn)
{
	system("cls");
	Gotoxy(46, 16);
	if (turn == 0)
	{
		cout << "적과 마주쳤다!";
	}
	else if (turn == 1)
	{
		cout << "적의 습격이다!";
	}
	Sleep(1500);
	GotoxyPrintXReturn("                    ", 44);

	int countTurn = turn;
	char t;

	vector<function<bool(int)>> PlayerDurationSkills;
	//vector<UseSkillFuncPtr> MonsterDurationSkills;



	while (true)
	{
		//상태 갱신
		string strTurn;
		GotoxyPrintReturn(to_string(countTurn) + " 턴", SCREEN_START_X * 2 + 0, SCREEN_START_Y + 0 );
		monster->PrintMonsterStatus(SCREEN_START_X * 2 + 42, SCREEN_START_Y + 0);
		//cout << countTurn << " 턴" << endl << endl; // 위에서 출력하고 지우지 않게 하기

		ReadFile(monster->GetName(), 40, 4);

		POS = GetCurrentXY();
		POS.X += 2;


		for (int i = 0;i < PlayerDurationSkills.size();i++)
		{
			//PlayerDurationSkills[i](countTurn);
			if (!PlayerDurationSkills[i](countTurn))//스킬이 종료(false) 되었다면
			{
				PlayerDurationSkills.erase(PlayerDurationSkills.begin() + i);
			}
		}


		Gotoxy(SCREEN_START_X * 2, SCREEN_START_Y + MAP_SIZE + 1);
		GotoxyClsShort(1);
		cout << "HP: " << player->GetHp() << "/" << player->GetTotalStatus()->TotalMaxHp
			<< "    Atk: " << player->GetTotalStatus()->TotalAtk;
		Gotoxy(SCREEN_START_X * 2, SCREEN_START_Y + MAP_SIZE + 2);
		GotoxyClsShort(1);
		cout << "MP: " << player->GetMp() << "/" << player->GetTotalStatus()->TotalMaxMp
			<< "    Def: " << player->GetTotalStatus()->TotalDef;
		Gotoxy(SCREEN_START_X * 2, SCREEN_START_Y + MAP_SIZE + 3);
		GotoxyClsShort(1);
		cout << "====================";

		if (countTurn % 2 == 0)
		{
			GotoxyPreparePrintMenu(0);
			cout << "1. 공 격";
			GotoxyPreparePrintMenu(1);
			cout << "2. 스 킬";
			GotoxyPreparePrintMenu(2);
			cout << "3. 가 방";
			GotoxyPreparePrintMenu(3);
			cout << "4. 포 기";
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
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
					addableCreature->DisplaySkills();

					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					char skillChar = _getche();
					GotoxyCll(1);

					int skillNum = skillChar - '1';

					Gotoxy(POS.X, POS.Y);
					if (player->GetSkillType(skillNum) == 1) // 타인에게 발동
					{
						if (GetMp() < player->Skills->at(skillNum)->GetMpConsume())
						{
							AddNotification("\"" + player->Skills->at(skillNum)->GetName() + "\"" + " 사용을 위한 Mp가 부족합니다.");
						}
						else
						{
							CalcMp(-player->Skills->at(skillNum)->GetMpConsume());
							player->UseSkill(monster, skillNum, countTurn);
							MonsterHitMotion(countTurn, monster->GetName(), player->GetName(), "color 4f");
							
							//타인에게 사용하는 턴제 스킬이 아니면 X
							//PlayerDurationSkills.push_back([&](int count) -> bool {return player->UseSkill(monster, skillNum, count);});
						}
					}
					else if (player->GetSkillType(skillNum) == 2) // 스스로에게 발동
					{
						if (GetMp() < player->Skills->at(skillNum)->GetMpConsume())
						{
							AddNotification("\"" + player->Skills->at(skillNum)->GetName() + "\"" + " 사용을 위한 Mp가 부족합니다.");
						}
						else
						{
							CalcMp(-player->Skills->at(skillNum)->GetMpConsume());
							player->UseSkill(player, skillNum, countTurn);							
							PlayerDurationSkills.push_back([&](int count) -> bool {return player->UseSkill(player, skillNum, count);});
						}
						
					}
				}
				
			}
			else if (t == '3')
			{
				shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(player);
				if (addableCreature)
				{
					addableCreature->DisplayInventory();

					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
					char itemChar = _getche();
					GotoxyCll(1);

					int itemNum = itemChar - '1';

					Item* getItem = addableCreature->SelectInventoryItem(itemNum);
					if (getItem != nullptr)
					{
						IConsumable* consumable = dynamic_cast<IConsumable*>(getItem);
						player->AddNotification(consumable->UseItem(player));
						if (consumable->GetNumber() <= 0)
						{
							addableCreature->CheckZeroInventory();
						}
					}
				}
				
			}
			else if (t == '4') // 포기
			{
				AddNotification("*플레이어가 사망합니다.*");
				player->SetHp(0);
				Sleep(2000);
				break;
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

		if (player->GetHp() <= 0)
		{
			AddNotification("플레이어 사망!");
			Notifications->clear();
			break;
		}
		else if (player->GetHp() <= 0 || monster->GetHp() <= 0)
		{
			AddNotification(monster->GetName() + " 을 처치하여 전투가 종료됩니다.");
				break;
		}
		countTurn++;
	}

	//초기화(상태 및 delete)
	system("cls");
	//Gotoxy(0, 0);
	//GotoxyClsLong(17);
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
	notificationErase(SCREEN_START_X, POS.Y, 6);
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
		//ReadFile(attacker, 40, 2);
		Sleep(200);
		ReadFile(attacker, 30, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//Sleep(100);
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
		ReadFile(attacker, 40, 14);
	}
	Sleep(700);
}

void Creature::PrintMonsterStatus(int x, int y)
{
	GotoxyPrintReturn("<"+Name+">", x, y);
	Gotoxy(x, y+1);
	int maxHp = GetTotalStatus()->TotalMaxHp/5;
	int currentHp = GetHp()/5;
	if (currentHp == 0 && GetHp() > 0)
	{
		currentHp = 1;
	}
	cout << "HP [";
	for (int i = 0;i < currentHp;i++)
	{
		cout << '=';
	}
	for (int i = 0;i < maxHp - currentHp;i++)
	{
		cout << ' ';
	}
	cout << "]";
}

void Creature::CalcHp(int hp)
{
	if (hp < 0)// 데미지 계산
	{
		//if (GetTotalStatus()->TotalDef >= -hp*1.1) // 방어력이 높아도 데미지의 10%는 보장
		//{
		//	hp /= 10;
		//}
		//else
		//{
		//	hp += GetTotalStatus()->TotalDef;
		//}
		hp = min(hp + GetTotalStatus()->TotalDef, hp / 10);
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
		if (Hp > GetTotalStatus()->TotalMaxHp)
		{
			Hp = GetTotalStatus()->TotalMaxHp;
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
	if (Mp > GetTotalStatus()->TotalMaxMp)
	{

		Mp += mp;
		Mp = GetTotalStatus()->TotalMaxMp;
	}
}

int Creature::GetSkillType(int num)
{
	if (num >= 0 && num < Skills->size())
	{
		return Skills->at(num)->GetType();
	}
	else
	{
		return -1;
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
			Gotoxy(SCREEN_START_X * 2 + start, SCREEN_START_Y + line);
			GotoxyPrintXReturn("                                                  ", SCREEN_START_X * 2 + start - erase);
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
	for (int i = 0;i < Skills->size();i++)
	{
		if (Skills->at(i)->GetType() == 0)
		{
			if (Skills->at(i)->GetName() == "공격 상승(패시브)")
			{
				atkSum += Skills->at(i)->GetEffectValue() * Skills->at(i)->GetLevel();
			}
		}
	}
	for (int i = 0;i < Skills->size();i++)
	{
		if (Skills->at(i)->GetType() == 0)
		{
			if (Skills->at(i)->GetName() == "방어 상승(패시브)")
			{
				defSum += Skills->at(i)->GetEffectValue() * Skills->at(i)->GetLevel();
			}
		}
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
	if (Notifications->size() > NOTIFICATION_LINE)
	{
		Notifications->erase(Notifications->begin());
	}
	
	int line = 0;
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
				GotoxyPreparePrintSituation(line);

				if (i == Notifications->size() - 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 | (8 << 4));
					cout << result;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (8 << 4));
					result = str.substr(len + 1, str.length() - len);
					cout << result << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << result;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					result = str.substr(len + 1, str.length() - len);
					cout << result << "\n";
				}

				bPrint = true;
				line++;
			}
			else if (result == "스켈레톤" || result == "드래곤")
			{
				GotoxyPreparePrintSituation(line);
				
				if (i == Notifications->size() - 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 | (8 << 4));
					cout << result;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (8 << 4));
					result = str.substr(len + 1, str.length() - len);
					cout << result << "\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << result;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					result = str.substr(len + 1, str.length() - len);
					cout << result << "\n";
				}

				bPrint = true;
				line++;
			}

			//index = position + 1;
			break; // 첫번째 단어만 체크 가능하게 됨
		}
		if (bPrint == false)
		{
			if (i == Notifications->size() - 1)
			{
				GotoxyPreparePrintSituation(line);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (8 << 4));
				cout << Notifications->at(i) << '\n';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				GotoxyPreparePrintSituation(line);
				cout << Notifications->at(i) << '\n';
			}
			line++;
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


int Creature::GetHp()
{
	return Hp;
}

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

vector<Skill*>* Creature::GetSkills()
{
	return Skills;
}

EquipedE* Creature::GetEquipments()
{
	return Equipments;
}
