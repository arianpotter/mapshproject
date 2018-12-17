#include <Windows.h>
#include <iostream>

using namespace std;
void main() 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
	cout<<"Hello world"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14); 
	cout<<"Hello world"<<endl;
} 