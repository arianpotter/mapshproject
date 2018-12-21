#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <string>
#include "Design.h"
using namespace std;

bool recaptcha(string u, string p)
{
	char temp1[100],temp2[100];
	int a;
	FILE *fp_userpass = fopen("../userpass.txt","w");
	while (fscanf(fp_userpass, "%s\t%s", temp1, temp2)+1)
	{
		if (temp1 == u && temp2 == p)
			return 1;
	}
	return 0;
}
void login(int length, int with)
{
	system("cls");
	background(31);
	border(length, with);
	string u, p;
	//================================== Username ==================================
	gotoxy((columns - length) / 2 + 1, rows / 2 + 1);
	cout << " Password: ";
	gotoxy((columns - length) / 2 + 1, rows / 2 - 1);
	cout << " Username: ";
	char ch;
	while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		if (u.length() == length - 13 && ch != 8) continue;
		if (ch == 8)
		{
			if (u.length() == 0) continue;
			cout << '\b' << " " << '\b';
			u.erase(u.end() - 1);
		}
		else
		{
			u += ch;
			cout << ch;
		}
	}
	//================================== Password ==================================
	gotoxy((columns - length) / 2 + 12, rows / 2 + 1);
	while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		if (p.length() == length - 13 && ch != 8) continue;
		if (ch == 8)
		{
			if (p.length() == 0) continue;
			cout << '\b' << " " << '\b';
			p.erase(p.end() - 1);
		}
		else
		{
			cout << '*';
			p += ch;
		}
	}
	//==================================== Check =====================================
	int check = 0;//recaptcha(u, p);
	gotoxy(0, 0);
	if (check == 1) 
	{
		background(160);
		gotoxy(columns / 2 - 11, rows / 2);
		cout << "Welcome to your panel";
		Sleep(1000);
		login(32, 5);
	}
	else
	{
		background(79);
		gotoxy(columns / 2 - 7, rows / 2);
		cout << "Access Denied";
		Sleep(1000);
		login(32,5);
	}
}
void welcome()
{
	background(31);
	system("cls");
	gotoxy(columns / 2 - 12, rows / 2 - 1);
	char s[25] = "Welcome to MAPSH ticket.";
	for (int i = 0; i < 24; i++)
	{
		cout << s[i];
		Sleep(50);
	}
	gotoxy(columns / 2 - 39, rows / 2);
	char str[78] = "to sign in press \"S\", to sign up press \"U\" and for using as guest press \"G\".\n";
	for (int i = 0; i < 78; i++)
	{
		cout << str[i];
		Sleep(50);
	}
	char c;
	c = _getche();
	if (c == 's' || c == 'S') login(32, 5);
	else if (c == 'u' || c == 'U');
	else if (c == 'g' || c == 'G');
	else;
}
inline void process(int time, int color, int n, int i)
{
	Sleep(time);
	gotoxy((columns - n) / 2 + i, rows / 2);
	print(char(219), color);
	Sleep(time);
	gotoxy(columns / 2 - 5, rows / 2 - 2);
}
void loading(int time, int processcolor, int backcolor, int n)
{
	background(backcolor);
	gotoxy(columns / 2 - 4, rows / 2 - 2);
	cout << " Loading\n";
	border(n + 2, 1);
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
		print("-", backcolor);

		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		print("\\", backcolor);
	}
	gotoxy(0, 0);
	Sleep(200);
}
void pnl_drivers(string user)
{
	background(31);
	long int ID2;
	char name[50], family[50], usern[50], username[50], passw[50], phonenum[50], vehicle[50];
	int n, t, t2;
	char temp[5000];
	for (int i = 0; i < user.length(); i++)
	{
		username[i] = user[i];
	}
	username[user.length()] = 0;
	FILE *AAIP = fopen("../All account information.txt", "r");
	while (1 + fscanf(AAIP, "%d\t%s\t%s\n", &ID2, usern, passw))
	{
		if (!strcmp(usern, username))
			break;
	}
	FILE *DTP = fopen("../Drivers travels.txt", "r");
	while (1)
	{
		fscanf(DTP, "%d\t%d\n", &t, &n);
		if (t == ID2) break;
		for (int i = 0; i < n; i++)
		{
			fgets(temp, 4999, DTP);
			fgets(temp, 4999, DTP);
		}
	}
	long int ID;
	fclose(AAIP);
	AAIP = fopen("../All account information.txt","r");
	FILE *DIP = fopen("../Drivers information.txt", "r");
	while (1 + fscanf(AAIP, "%d\t%s\t%s\n", &ID, usern, passw))
	{
		if (!strcmp(usern, username))
			break;
	}
	while (1 + fscanf(DIP, "%d\t%s\t%s\t%s\t%s", &t, name, family,phonenum,vehicle))
	{
		if (t==ID)
			break;
	}
	gotoxy((columns - 60) / 2 + 1, (rows - 2 * n - 1) / 2 - 2);
	cout << "Hi " << name << " " << family;
	border(60, 2 * n + 1);
	gotoxy((columns - 60) / 2 + 1, (rows - 2 * n - 1) / 2 + 1);
	cout << "Your travels:\n";
	char s[5000];
	fclose(DTP);
	DTP=fopen("../Drivers travels.txt", "r");
	while (1 + fscanf(DTP, "%d\t%d\n", &t,&t2))
	{
		if (t == ID)
		{
			for (int i = 0; i < n; i++)
			{
				gotoxy((columns - 60) / 2 + 1, (rows - 2 * n - 1) / 2 + 3 + 2 * i);
				fgets(s, 50, DTP);
				cout << s << endl;
				fgets(s, 50, DTP);
			}
		}
		for (int i = 0; i < t2; i++)
		{
			fgets(s, 4999, DTP);
			fgets(s, 4999, DTP);
		}
	}
	gotoxy((columns - 60) / 2 + 1, (rows + 2 * n + 1) / 2 + 3);
	cout << "To show your history press \"S\"\tTo show your info press \"I\"";
	gotoxy((columns - 60) / 2 + 1, (rows + 2 * n + 1) / 2 + 4);
	cout << "To change your info press \"T\"\tTo define your new travel, press \"N\"";
	gotoxy((columns - 60) / 2 + 1, (rows + 2 * n + 1) / 2 + 5);
	cout << "To change your travel press \"M\"\tTo cncel your travel, press \"L\"";
	gotoxy((columns - 60) / 2 + 1, (rows + 2 * n + 1) / 2 + 6);
	cout << "To go back press Ctrl+B\t\tTo go home press Ctrl+H";
	gotoxy((columns - 60) / 2 + 1, (rows + 2 * n + 1) / 2 + 7);
	cout << "To show details of travels press \"D\"";
	cin >> n;
}

int main()
{
	fullscreen();
	screensize();
	pnl_drivers("mp64");
	/*loading(50, 250, 31, 50);
	welcome();
	gotoxy(0, rows);*/
}