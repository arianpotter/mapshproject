#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include "Design.h"
#define _WIN32_WINNT 0x0500
using namespace std;
/*
			 sign up	     pnl_driver
				?		      	 ?
Loading ---> welcome --------> sign in ---> pnl_user
				?		       	 ?
			  Guest		      pnl_admin

*/

COORD screen;
struct Person
{
	string username;
	string password;
	string name;
	string family;
	string phone;
	string inviter;
	string account;
	string accpass;
}person;

void pnl_user(int length, int width, int backcolor, int headercolor)
{
	background(backcolor, screen);
	system("cls");
	border(length, width, screen);
	//print(' ', headercolor, 0, 0, screen.X - 1);
	//print(person.name + '\t' + person.family, headercolor, 0, 0);

}

inline string int_to_str(int a)
{
	string str;
	for (; a > 0; a /= 10)
		str.insert(str.begin(), a % 10 + 48);
	return str;
}
string input(int min, int max, int x, int y, int xerr, int yerr, int color, int errorcolor, string mode, int maxerrlength = 30, bool ispass = false, bool isoptional = false) //mode: n:num | l:lower case | u:upper case |s | e
{
	string str;
	char ch;
	gotoxy(x, y);
	while (1)
	{
		ch = _getch();
		//enter
		if (ch == 13)
		{
			if (str.length() >= min || (isoptional && !str.length()))
			{
				print(' ', color, xerr, yerr, maxerrlength);
				break;
			}
			else
			{
				print(' ', color, xerr, yerr, maxerrlength);
				if (min == max) print("must be " + int_to_str(min) + " digits. ", errorcolor, xerr, yerr);
				else print("must be between " + int_to_str(min) + " and " + int_to_str(max) + ".", errorcolor, xerr, yerr);
				//remove input box
				print(' ', color, x, y, str.length());
				str = "";
			}
		}
		//check max length & limit char
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
		if ((str.length() == max || !m) && ch != 8) continue;
		//backspace
		if (ch == 8)
		{
			if (str.length() == 0) continue;
			cout << '\b' << " " << '\b';
			str.erase(str.end() - 1);
		}
		else
		{
			str += ch;
			ispass ? print('*', color) : print(ch, color);
		}
	}
	return str;
}

inline void signupshow(int length, int width, int color, int titrcolor)
{
	system("cls");
	background(color, screen);
	cursor(true);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print(" Please Fill the blank to sign up in MAPSH ticket. ", titrcolor, x + 25, y - 1);
	print("Username: ", color, x + 2, y + 1);
	print("Password: ", color, x + 2, y + 3);
	print("Confirm Password: ", color, x + 2, y + 5);
	print("Name: ", color, x + 2, y + 7);
	print("Family: ", color, x + 2, y + 9);
	print("Phone Number: ", color, x + 2, y + 11);
	print("Inviter: ", color, x + 2, y + 13);
	print("Bank Account Number: ", color, x + 2, y + 15);
	print("Bank Account Password: ", color, x + 2, y + 17);
}
void signup(int length, int width, int color, int captioncolor, int errorcolor, int acceptcolor, int warningcolor, int titrcolor)
{	
	string pass;
	fstream user, userinfo;

	signupshow(length, width, captioncolor, titrcolor);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	{
		//================================== Username ==================================
		print("between 5 and 15", warningcolor, x + 12, y + 1);
		while (1)
		{
			person.username = input(5, 15, x + 4, y + 2, x + 12, y + 1, color, errorcolor, "nle");
			int id = 0;
			string u, p;
			userinfo.open("Users Information.txt", ios::in);
			while (userinfo >> id >> u >> p)
			{
				if (u == person.username)
				{
					print("This username alredy exist!", errorcolor, x + 12, y + 1);
					print(' ', color, x + 4, y + 2, person.username.length());
					print('X', errorcolor, x + 1, y + 1);
					id = -1;
					break;
				}
			}
			userinfo.close();
			if (id != -1) break;
		}
		print(char(-5), acceptcolor, x + 1, y + 1);
		//================================== Password ==================================
		print("between 4 and 15", warningcolor, x + 12, y + 3);
		person.password = input(4, 15, x + 4, y + 4, x + 12, y + 3, color, errorcolor, "nlus", true);
		print(char(-5), acceptcolor, x + 1, y + 3);

		print("Confirm your password", warningcolor, x + 20, y + 5);
		while (1)
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, color, errorcolor, "nlus", true);

			if (pass == person.password)
			{
				print(char(-5), acceptcolor, x + 1, y + 5);
				break;
			}
			else
			{
				print("X", errorcolor, x + 1, y + 5);
				print("Passwords not matched.", errorcolor, x + 20, y + 5);
				print(' ', color, x + 4, y + 6, pass.length());
			}
		}
		//===================================== Name ===================================
		print("between 3 and 10", warningcolor, x + 8, y + 7);
		person.name = input(3, 10, x + 4, y + 8, x + 8, y + 7, color, errorcolor, "lu");
		print(char(-5), acceptcolor, x + 1, y + 7);
		//==================================== Family ==================================
		print("betwen 5 and 20", warningcolor, x + 10, y + 9);
		person.family = input(5, 20, x + 4, y + 10, x + 10, y + 9, color, errorcolor, "lu");
		print(char(-5), acceptcolor, x + 1, y + 9);
		//===================================== Phone ==================================
		print("11 digits", warningcolor, x + 16, y + 11);
		person.phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, color, errorcolor, "n");
		print(char(-5), acceptcolor, x + 1, y + 11);
		//==================================== inviter =================================
		print("Inviter's Username is Optional and between 5 and 15.", warningcolor, x + 11, y + 13);
		person.inviter = input(5, 15, x + 4, y + 14, x + 11, y + 13, color, errorcolor, "nle", 60, false, true);
		print(char(-5), acceptcolor, x + 1, y + 13);
		//================================== Bank account ==============================
		ifstream acc;
		string line;
		size_t pos;
		print("6 digits", warningcolor, x + 23, y + 15);
		while (1)
		{
			person.account = input(6, 6, x + 4, y + 16, x + 23, y + 15, color, errorcolor, "n");

			acc.open("accounts.txt", ios::in);
			while (!acc.eof())
			{
				getline(acc, line); // get line from file
				pos = line.find(person.account); // search
				if (pos != string::npos) break; // string::npos is returned if string is not found
			}
			if (pos == string::npos)
			{
				print("wrong bank account number!", errorcolor, x + 23, y + 15);
				print("X", errorcolor, x + 1, y + 15);
				print(' ', color, x + 4, y + 16, 7);
				acc.close();
			}
			else break;
		}
		print(char(-5), acceptcolor, x + 1, y + 15);
		//================================ Bank password ===============================
		print("6 digits", warningcolor, x + 25, y + 17);
		while (1)
		{
			person.accpass = input(4, 4, x + 4, y + 18, x + 25, y + 17, color, errorcolor, "n", 50);

			pos = line.find(person.account + "\t" + person.accpass); // search
			if (pos != string::npos) // string::npos is returned if string is not found
			{
				gotoxy(x + 25, y + 17);
				print("bank account connected!", acceptcolor);
				Sleep(500);
				break;
			}
			else
			{
				print("your bank account password is incorrect!", errorcolor, x + 25, y + 17);
				print("X", errorcolor, x + 1, y + 17);
				print(' ', color, x + 4, y + 18, 4);
			}
		}
		print(char(-5), acceptcolor, x + 1, y + 17);
	}
	//================================ write in file ===============================
	user.open("User.txt", ios::app);
	userinfo.open("Users Information.txt", ios::app);
	userinfo << '\n' << "1" + person.account << "\t" << person.username << "\t" << person.password;
	user << '\n' << "1" + person.account << "\t" << person.name << "\t" << person.family << "\t" << person.phone << "\t" << person.accpass;

	background(160, screen);
	gotoxy(screen.X / 2 - 11, screen.Y / 2);
	cout << "Welcome to your panel";
	Sleep(1000);
}

bool recaptcha(string u, string p)
{
	string user, pass;
	int id;
	ifstream userinfo;
	userinfo.open("Users Information.txt", ios::in);

	while (userinfo >> id >> user >> pass)
	{
		if (user == u && pass == p)
			return true;
	}
	userinfo.close();
	return false;
}
void login(int length, int width, int color, int errorcolor)
{
	system("cls");
	background(color, screen);
	cursor(true);
	border(length, width, screen);
	//================================== User pass ==================================
	string u, p;
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;

	print("Username: ", color, x + 2, y + 2);
	print("Password: ", color, x + 2, y + 4);

	u = input(5, 15, x + 12, y + 2, x + 6, y + 3, color, errorcolor, "nle", 25);
	p = input(4, 15, x + 12, y + 4, x + 6, y + 5, color, errorcolor, "nlus", 25, true);
	//==================================== Check =====================================
	int check = recaptcha(u, p);
	if (check == 1) 
	{
		background(160, screen);
		print("Welcome to your panel", 160, screen.X / 2 - 11, screen.Y / 2);
		Sleep(1000);
		pnl_user(screen.X - 16, screen.Y - 16, 115, 78);
	}
	else
	{
		background(79, screen);
		print("Access Denied", 79, screen.X / 2 - 7, screen.Y / 2);
		Sleep(1000);
		login(37, 5, 31, 20);
	}
}

void welcome(int backcolor, int sleeptime)
{
	system("cls");
	background(backcolor, screen);
	//================================== Print first line ==========================
	gotoxy(screen.X / 2 - 12, screen.Y / 2 - 1);
	char s[25] = "Welcome to MAPSH ticket.";
	for (int i = 0; i < 24; i++)
	{
		cout << s[i];
		Sleep(sleeptime);
	}
	Sleep(3 * sleeptime);
	//================================== Print second line =========================
	gotoxy(screen.X / 2 - 39, screen.Y / 2);
	char str[78] = "to sign in press \"S\", to sign up press \"U\" and for using as guest press \"G\".\n";
	for (int i = 0; i < 78; i++)
	{
		cout << str[i];
		Sleep(sleeptime);
	}
	//==================================== goto panels =============================
	char c;
	c = _getch();
	if (c == 's' || c == 'S') login(37, 5, 31, 20);
	else if (c == 'u' || c == 'U') signup(100, 18, 31, 30, 28, 26, 24, 117);
	else if (c == 'g' || c == 'G') signup(100, 18, 31, 30, 28, 26, 24, 117);
	else;
}

inline void process(int time, int color, int n, int i)
{
	Sleep(time);
	print(char(219), color, (screen.X - n) / 2 + i, screen.Y / 2);
	Sleep(time);
	gotoxy(screen.X / 2 - 5, screen.Y / 2 - 2);
}
void loading(int time, int processcolor, int backcolor, int n)
{
	background(backcolor, screen);
	cursor(false);
	gotoxy(screen.X / 2 - 4, screen.Y / 2 - 2);
	cout << " Loading\n";
	border(n + 2, 1, screen);
	for (int i = 0; i < n;)
	{
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		print("|", backcolor);

		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		print("/", backcolor);

		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		print(char(-60), backcolor);

		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		print("\\", backcolor);
	}
	Sleep(200);
}

int main()
{
	fullscreen();
	screen = screensize();
	//loading(50, 250, 31, 50);
	//welcome(31, 50);
	pnl_user(screen.X - 16, screen.Y - 16, 115, 78);
	
	/*for (int i = 0; i < 299; i++)
	{
		print(i, i);
		print("	fghfgfsghfhfhfa\n", i);
		//printf("%d : %c\n", i, i);
	}*/
	gotoxy(0, screen.Y);
}