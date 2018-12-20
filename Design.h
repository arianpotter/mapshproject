#include <iostream>
#include <conio.h>
#include <cwchar>
#include <string>
#include <windows.h>
#define _WIN32_WINNT 0x0500
#include <fstream>
using namespace std;

int columns, rows;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template <typename T>
void print(T s,int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
	cout << s;
}
void background(int k)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			print(' ', k);
}
void fullscreen()
{
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}
void screensize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void border(int length, int width)
{
	gotoxy((columns - length) / 2, (rows - width) / 2);
	cout << char(201);
	for (int i = 1; i < length; i++)
		cout << char(205);

	for (int i = 1; i <= width; i++)
	{
		gotoxy((columns - length) / 2, i + (rows - width) / 2);
		cout << char(186) << endl;
	}
	gotoxy((columns - length) / 2, (rows + width) / 2 + 1);
	cout << char(200);
	for (int i = 1; i <= length; i++)
		cout << char(205);

	gotoxy((columns + length) / 2, (rows + width) / 2 + 1);
	cout << char(188);
	for (int i = 1; i <= width; i++)
	{
		gotoxy((columns + length) / 2, i + (rows - width) / 2);
		cout << char(186) << endl;
	}
	gotoxy((columns + length) / 2, (rows - width) / 2);
	cout << char(187);
}
