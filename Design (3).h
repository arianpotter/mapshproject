#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <math.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>

using namespace std;


void fullscreen()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	/*SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwSize);

	HWND h = GetConsoleWindow();
	ShowScrollBar(h, SB_BOTH, FALSE);*/
}
COORD screensize()
{
	COORD c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	c.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	c.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return c;
}

void cursor(bool mode)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = mode;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void cursor(bool mode, int size)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = size;
	info.bVisible = mode;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

template <typename T>
void print(T s, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << s;
}
template <typename T>
void print(T s, int color, int x, int y)
{
	gotoxy(x, y);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << s;
}
void print(char s, int color, int xi, int y, int dx)
{
	gotoxy(xi, y);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	for (int i = 0; i <= dx; i++)
		cout << s;
	gotoxy(xi, y);
}

void background(int color, COORD screen)
{
	gotoxy(0, 0);
	for (int i = 0; i < screen.Y; i++)
		for (int j = 0; j < screen.X; j++)
			print(' ', color);
	system("cls");
	gotoxy(0, 0);
}

void border(int length, int width, COORD screen)
{
	gotoxy((screen.X - length) / 2, (screen.Y - width) / 2);
	cout << char(201);
	for (int i = 1; i < length; i++)
		cout << char(205);

	for (int i = 1; i <= width; i++)
	{
		gotoxy((screen.X - length) / 2, i + (screen.Y - width) / 2);
		cout << char(186) << endl;
	}
	gotoxy((screen.X - length) / 2, (screen.Y + width) / 2 + 1);
	cout << char(200);
	for (int i = 1; i <= length; i++)
		cout << char(205);

	gotoxy((screen.X + length) / 2, (screen.Y + width) / 2 + 1);
	cout << char(188);
	for (int i = 1; i <= width; i++)
	{
		gotoxy((screen.X + length) / 2, i + (screen.Y - width) / 2);
		cout << char(186) << endl;
	}
	gotoxy((screen.X + length) / 2, (screen.Y - width) / 2);
	cout << char(187);
}
