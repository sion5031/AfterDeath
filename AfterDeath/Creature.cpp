#include "Creature.h"

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

	//==========

	// 출력 부(캐릭터, 상태, 
	system("cls");

	//==========

	while (true)
	{
		if (countTurn % 2 == 0)
		{// t값 예외처리!!
			system("cls");
			cout << countTurn << " 턴" << endl << endl; // 위에서 출력하고 지우지 않게 하기
			cout << "1. 공격\n\n2. 스킬\n\n3. 가방\n\n4. 포기\n" << endl;
			t = _getche();
			if (t == '1')
			{
				player->NormalAttack(player, monster); // 의미 없는 주체...
				if (monster->GetHp() <= 0)
				{
					break;
				}
			}
			else if (t == '2')
			{
				for (int i = 0;i < player->Skills->size();i++) // 동작?
				{
					if (player->Skills->at(i)->GetType() == 0)
					{
						cout << i + 1 << ".\t" << player->Skills->at(i) << endl << endl;
					}
				}
				cout << "스킬 선택" << endl;
				t = _getche();
				int skillNum = t - '0';
				int count = 1;
				for (int i = 0;i < player->Skills->size();i++)
				{
					if (player->Skills->at(i)->GetType() == 0)
					{
						if (skillNum == count)
						{
							if (player->Skills->at(i)->Effect().at(0) == 0)
							{
								player->UseSkill(monster);
							}
						}
					}
					else
					{

					}
				}
			}
			else if (t == '3')
			{
				shared_ptr<IPlayable> addableCreature = dynamic_pointer_cast<IPlayable>(player);
				if (addableCreature)
				{
					addableCreature->DisplayInventory();					
				}
				t = _getche();
				if (t == '1')
				{
					int selectItem;
					cout << endl << "아이템을 선택해주세요: ";
					t = _getche();
					selectItem = t - '0';

					addableCreature->SelectInventoryItem(selectItem);
				}
				
			}
			else if (t == '4')
			{

			}
		}
		else // 몬스터 턴 ================
		{
			system("cls");
			cout << countTurn << " 턴" << endl << endl; // 위에서 출력

			int num = rand() % 2; // 공격, 스킬 사용 빈도 몬스터에서 받아오기?

			if (num < 2)
			{
				monster->NormalAttack(monster, player);
				if (player->GetHp() <= 0)
				{
					break;
				}
			}
			else if (num == 2)
			{
				monster->UseSkill(player);
			}
			else
			{
				//예외?
			}

		}
		countTurn++;
	}


}

void Creature::NormalAttack(shared_ptr<Creature> attacker, shared_ptr<Creature> defender) //방어력 계산 필요
{
	cout << "atk: " << attacker->GetTotalStatus()->TotalAtk << ", def: " << defender->GetTotalStatus()->TotalDef << endl;
	int before = defender->Hp;
	defender->CalcHp(-attacker->GetTotalStatus()->TotalAtk);
	int after = defender->Hp;
	cout << defender->GetName() << "가 " << before - after << " 만큼의 피해를 입었습니다." << endl;
	Sleep(2000);
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
	}
	
}

void Creature::CalcMp(int mp)
{
	Mp += mp;
}

void Creature::PrintBattle(shared_ptr<Creature> player, shared_ptr<Creature> monster)
{
	for (int i = 0;i < ScreenSize;i++) cout << "= ";
	for (int i = 0;i < ScreenSize;i++) cout << "  ";

	int size = 4;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < ScreenSize-size;j++) cout << "  ";
		//for
	}






	for (int i = 0;i < ScreenSize;i++) cout << "  ";
	for (int i = 0;i < ScreenSize;i++) cout << "= ";
}

void Creature::ReadFile(string fileName)
{
	ifstream in("..\\"+fileName);
	string s;

	if (in.is_open()) {
		while (!in.eof())
		{
			getline(in, s);
			cout<< s << std::endl;
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

//void Creature::ReadFile(string fileName)
//{
//	wstring tem;
//	tem.assign(fileName.begin(), fileName.end());
//	wstring path = L"..\\" + tem;
//
//	wifstream in;
//	in.imbue(locale(locale::empty(), new codecvt_utf16<wchar_t, 0x10ffff, consume_header>));
//	in.open(path);
//	wstring s;
//
//	if (in.is_open()) {
//		while (!in.eof())
//		{
//			cout << "진입" << endl;
//			getline(in, s);
//			wcout << s << endl;
//		}
//	}
//	else {
//		cout << "파일을 찾을 수 없습니다!" << std::endl;
//	}
//	in.close();
//}

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
