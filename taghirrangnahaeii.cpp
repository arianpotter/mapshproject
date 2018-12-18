#include <Windows.h>
#include <iostream>

using namespace std;
int main() 
{
	char ch = 219;
	for (int j = 0; j < 10; j++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		cout << endl;
	}
	for (int j = 0; j < 10; j++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		for (int i = 0; i < 20; i++)
		{
			cout << ch;
		}
		cout << endl;
	}
}