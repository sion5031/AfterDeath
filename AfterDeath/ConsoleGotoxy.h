#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

void Gotoxy(int x, int y);
void GotoxyCll(int size);
void GotoxyCll(int size, int x, int y);
void GotoxyClsShort(int size);
void GotoxyClsLong(int size);
void GotoxyCls(int size, int x, int y);
void GotoxyPrintReturn(string str, int x, int y);
void GotoxyPrintXReturn(string str, int x);

void GotoxyPreparePrintMenu();
void GotoxyPreparePrintSituation();

COORD GetCurrentXY();