#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include "Design.h"
using namespace std;

inline string int_to_str(int a)
{
	if (a == 0) return "0";
	string str;
	for (; a > 0; a /= 10)
		str.insert(str.begin(), a % 10 + 48);
	return str;
}
inline string int_to_str(int a, unsigned int size)
{
	string str;
	for (; a > 0; a /= 10)
		str.insert(str.begin(), a % 10 + 48);
	while (str.length() < size)
		str.insert(str.begin(), '0');
	return str;
}

inline int yday(int month, int day)
{
	switch (month)
	{
	case 1: return  day;
	case 2: return  31 + day;
	case 3: return  59 + day;
	case 4: return  90 + day;
	case 5: return  120 + day;
	case 6: return  151 + day;
	case 7: return  181 + day;
	case 8: return  212 + day;
	case 9: return  243 + day;
	case 10: return  273 + day;
	case 11: return  304 + day;
	case 12: return  334 + day;
	}
	return -1;
}

//mode: n:num | l:lower case | u:upper case |s | e
string input(unsigned int min, int max, int x, int y, int xerr, int yerr, int color, int errorcolor, string mode, int maxerrlength = 30, bool ispass = false, bool isoptional = false)
{
	string str;
	char ch;
	//ctrl key
	bool b = false, p = false, z = false, e = false;
	for (int i = 0; mode[i] != '\0'; i++)
	{
		switch (mode[i])
		{
		case 'b':
			b = true; break;
		case 'p':
			p = true; break;
		case 'z':
			z = true; break;
		case 'E':
			e = true;; break;
		}
	}

	print(' ', color, x, y, max - 1);
	gotoxy(x, y);
	while (1)
	{
		ch = _getch();
		//input Mode
		bool m = false;
		for (int i = 0; mode[i] != '\0'; i++)
		{
			switch (mode[i])
			{
			case 'n':
				m |= ch >= '0' && ch <= '9'; break;
			case 'l':
				m |= ch <= 'z' && ch >= 'a'; break;
			case 'u':
				m |= ch <= 'Z' && ch >= 'A'; break;
			case 'e':
				m |= ch == '_' || ch == '@'; break;
			case 's':
				m |= (ch <= 47 && ch > 32) || (ch <= 64 && ch >= 58) || (ch <= 96 && ch >= 91) || (ch <= 126 && ch >= 123); break;
			}
		}
	
		if (ch == 2 && b) { print(' ', color, x, y, max - 1); return "~b"; } // Ctrl + B
		else if (ch == 16 && p) { (' ', color, x, y, max - 1); return "~p"; } //Ctrl + P
		else if (ch == 26 && z) { print(' ', color, x, y, max - 1); return "~z"; } //ctrl + Z
		else if (ch == 27 && e) { print(' ', color, x, y, max - 1); return "~E"; } // Esc
		else if (ch == -32 || !ch) //limit arrow and fn
		{
			_getch();
			continue;
		}
		else if (ch == 13) //Enter
		{
			if (str.length() >= min || (isoptional && !str.length())) //enough char
			{
				print(' ', color, xerr, yerr, maxerrlength);
				return str;
			}
			else //less char
			{
				print(' ', color, xerr, yerr, maxerrlength); //erase Error
				if (min == max) print("must be " + int_to_str(min) + " digits. ", errorcolor, xerr, yerr);
				else print("must be between " + int_to_str(min) + " and " + int_to_str(max) + ".", errorcolor, xerr, yerr);
				print(' ', color, x, y, str.length()); //erase input box
				str = "";
			}
		}
		else if (ch == 8) //Backspace
		{
			if (str.length() == 0) continue;
			cout << "\b \b";
			str.erase(str.end() - 1);
		}
		else //true char
		{
			if ((str.length() == max || !m)) continue; //check max length & limit invalid char
			str += ch;
			ispass ? print('*', color) : print(ch, color);
		}
	}
	return str;
}

int edit(string search, string replace, string fileaddress)
{
	string str;
	stringstream l;
	ifstream f(fileaddress);

	l << f.rdbuf();
	str = l.str();
	size_t pos = str.find(search);
	if (pos == string::npos)
		return 0;

	str.replace(pos, search.length(), replace);
	f.close();

	ofstream fi(fileaddress);
	fi << str;
	fi.close();
	return 1;
}
