#include "Creature.h"

void Creature::Fight(Creature* player, Creature* monster, int turn)
{
	system("cls");

	int countTurn = turn;
	char t;

	//==========

	// 출력 부(캐릭터, 상태, 

	//==========

	while (true)
	{
		if (countTurn % 2 == 0)
		{
			cout << "1. 공격\n\n2. 스킬\n\n3. 가방\n\n4. 포기\n" << endl;
			t = _getche();
			if (t == 1)
			{
				player->NormalAttack(monster);
			}
			else if (t == 2)
			{

			}
			else if (t == 3)
			{

			}
			else if (t == 4)
			{

			}
		}
		else
		{

		}
		countTurn++;
	}


}

void Creature::NormalAttack(Creature* creature)
{
	//creature->CalcHp()
	//Equipments->myGlove->
}

void Creature::CalcHp(int hp)
{
	if (Hp <= hp)
	{
		Hp = 0;
		Die();
	}
	Hp += hp;
	
}

void Creature::CalcMp(int mp)
{
	Mp += mp;
}

void Creature::PrintBattle(Creature* player, Creature* monster)
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

int Creature::GetMaxHp()
{
	return MaxHp;
}

int Creature::GetHp()
{
	return Hp;
}

int Creature::GetMaxMp()
{
	return MaxMp;
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
