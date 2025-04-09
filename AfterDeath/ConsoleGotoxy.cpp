#include "ConsoleGotoxy.h"
#include "Config.h"

void Gotoxy(int x, int y)
{
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyCll(int size)
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);  	//현재 커서의 위치 정보를 저장하는 함수
	COORD Pos = { presentCur.dwCursorPosition.X - 1 , presentCur.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cout << ' ';
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyCll(int size, int x, int y)
{
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	for (int i = 0;i < size;i++)
	{
		cout << ' ';
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyClsShort(int size)
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);  	//현재 커서의 위치 정보를 저장하는 함수
	COORD Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	for (int i = 0;i < size;i++)
	{		
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << "                                   \n";
		Pos.Y++;
	}
	Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyClsLong(int size)
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;// 콘솔 출력창의 정보를 담기 위해서 정의한 구조체
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);  	//현재 커서의 위치 정보를 저장하는 함수
	COORD Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	for (int i = 0;i < size;i++)
	{
		cout << "                                                                                            \n";
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyCls(int size, int x, int y)
{
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	for (int i = 0;i < size;i++)
	{
		cout << "                              \n";
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyPrintReturn(string str, int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cout << str;
	Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyPrintXReturn(string str, int x)
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	COORD Pos = { x , presentCur.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cout << str;
	//Pos = { presentCur.dwCursorPosition.X , (short)((int)presentCur.dwCursorPosition.Y + 1) };
	Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GotoxyPreparePrintMenu(int line)
{
	Gotoxy(SCREEN_START_X * 2 + 0, SCREEN_START_Y + 5 + line);
	GotoxyClsShort(8);
}

void GotoxyPreparePrintSituation(int line)
{	
	//Gotoxy(0, 19); //15+4
	Gotoxy(SCREEN_START_X * 2 + 0, SCREEN_START_Y + MAP_SIZE + 4 + line);
	GotoxyClsLong(1);
}

COORD GetCurrentXY()
{
	CONSOLE_SCREEN_BUFFER_INFO presentCur;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
	COORD Pos = { presentCur.dwCursorPosition.X , presentCur.dwCursorPosition.Y };
	return Pos;
}
