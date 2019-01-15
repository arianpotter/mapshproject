#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <string>
#include "Design.h"
using namespace std;
int t_i_n=0;

void ch_driver_info(long long int ID)
{
	int i = 0, j = 0;
	long int acc, accpass1, ID2 = 0;
	long int acc2, accpass12, ID22 = 0;
	background(31);
	border(32, 20);
	char name[50], family[50], phnum[50], vehicle[50], user[50], pass[50];
	char name2[50], family2[50], phnum2[50], vehicle2[50], user2[50], pass2[50];
	FILE *DIP = fopen("Drivers information.txt", "r");
	while (ID != ID2)
	{
		fscanf(DIP, "%d\t%s\t%s\t%s\t%s\t%d\t%d\n", &ID2, name, family, phnum, vehicle, &acc, &accpass1);
		i++;
	}
	accpass12 = accpass1;
	fclose(DIP);
	FILE *AAIP = fopen("All account information.txt", "r");
	ID2 = 0;
	while (ID != ID2)
	{
		fscanf(AAIP, "%d\t%s\t%s\t\n", &ID2, user, pass);
		j++;
	}
	fclose(AAIP);
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 9);
	cout << "Username: ";
	cin >> user2;
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 6);
	cout << "name: ";
	cin >> name2;
	gotoxy((columns - 32) / 2 + 1, rows / 2-3);
	cout << "family: ";
	cin >> family2;
	gotoxy((columns - 32) / 2 + 1, rows / 2);
	cout << "phonr number: ";
	cin >> phnum2;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 3);
	cout << "vehicle: ";
	cin >> vehicle2;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 6);
	cout << "Bank account: ";
	cin >> acc2;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 9);
	cout << "Bank account password: ";
	cin >> accpass12;
	DIP = fopen("Drivers information.txt", "r+");
	AAIP = fopen("All account information.txt", "r+");
	for (int k = 1; k < i; k++)
	{
		fscanf(DIP, "%d\t%s\t%s\t%s\t%s\t%d\t%d\n", &ID2, name, family, phnum, vehicle, &acc, &accpass1);
	}
	fprintf(DIP, "%d\t%s\t%s\t%s\t%s\t%d\t%d\n", ID, name2, family2, phnum2, vehicle2, acc2, accpass12);
	for (int k = 1; k < j; k++)
	{
		fscanf(AAIP, "%d\t%s\t%s\n", &ID2, user, pass);
	}
	fprintf(AAIP, "%d\t%s\t%s\t\n", ID22, user2, pass2);
}
void drivers_info(long long int ID)
{
	long int acc, accpass1,ID2=0;
	background(31);
	border(32, 20);
	char name[50], family[50], phnum[50],vehicle[50], user[50], pass[50];
	FILE *DIP = fopen("Drivers information.txt","r");
	while (ID!=ID2) fscanf(DIP, "%d\t%s\t%s\t%s\t%s\t%d\t%d\n",&ID2,name,family,phnum,vehicle,&acc,&accpass1);
	FILE *AAIP = fopen("All account information.txt", "r");
	ID2 = 0;
	while (ID != ID2) fscanf(AAIP, "%d\t%s\t%s\t\n", &ID2, user, pass);
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 9);
	cout << "ID: " << ID;
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 6);
	cout << "Username: " << user;
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 3);
	cout << "name: "<<name;
	gotoxy((columns - 32) / 2 + 1, rows / 2);
	cout << "family: "<<family;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 3);
	cout << "phonr number: "<<phnum;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 6);
	cout << "vehicle: "<<vehicle<<endl;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 9);
	cout << "Bank account: " << acc << endl;
}
void travel_def_driver(char vehicle[])
{
	background(31);
	char first[4], end[4];
	int  year, month, day, hour, minute;
	border(32, 21);
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 10);
	cout << "From: ";
	scanf("%s", &first);
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 7);
	cout << "To: ";
	scanf("%s", &end);
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 4);
	cout << "Year: ";
	cin >> year;
	gotoxy((columns - 32) / 2 + 1, rows / 2 - 1);
	cout << "Month: ";
	cin >> month;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 2);
	cout << "Day: ";
	cin >> day;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 5);
	cout << "Hour: ";
	cin >> hour;
	gotoxy((columns - 32) / 2 + 1, rows / 2 + 8);
	cout << "Minute: ";
	cin >> minute;
	int travel_ID;
	t_i_n++;
	travel_ID = t_i_n;
	FILE *ETP = fopen("Existed travels.txt", "a");
	fprintf(ETP, "%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\n", travel_ID, first, end, year, month, day, hour, minute);
	fclose(ETP);
}
bool recaptcha(string u, string p)
{
	char temp1[100],temp2[100];
	int a;
	FILE *fp_userpass = fopen("userpass.txt","w");
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
	/*
	background(143);
	long int ID2;
	char name[50], family[50], usern[50], username[50], passw[50], phonenum[50], vehicle[50];
	int n, t, t2;
	char temp[5000];
	for (int i = 0; i < user.length(); i++)
	{
		username[i] = user[i];
	}
	username[user.length()] = 0;
	FILE *AAIP = fopen("All account information.txt", "r");
	while (1 + fscanf(AAIP, "%d\t%s\t%s\n", &ID2, usern, passw))
	{
		if (!strcmp(usern, username))
			break;
	}
	FILE *DTP = fopen("Drivers travels.txt", "r");
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
	AAIP = fopen("All account information.txt","r");
	FILE *DIP = fopen("Drivers information.txt", "r");
	while (1 + fscanf(AAIP, "%d\t%s\t%s\n", &ID, usern, passw))
	{
		if (!strcmp(usern, username))
			break;
	}
	while (1 + fscanf(DIP, "%d\t%s\t%s\t%s\t%s", &t, name, family,phonenum,vehicle))
	{
		if (t==ID)
			break;
	}*/
	gotoxy(5, 4);
	cout << "Hi " << name << " " << family << "!" << "\t\tID: " << ID << "\t\tUsername: " << username << "\t\tVehicle: " << vehicle;
	border(200, 43);
	gotoxy(6, 6);
	cout << "Your travels:\n";
	char s[5000];
	fclose(DTP);
	DTP=fopen("Drivers travels.txt", "r");
	while (1 + fscanf(DTP, "%d\t%d\n", &t,&t2))
	{
		if (t == ID)
		{
			for (int i = 0; i < n; i++)
			{
				gotoxy(6, 8 + 2 * i);
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
	gotoxy((columns - 200) / 2, (rows + 2 * n + 1) / 2 + 20);
	cout << "To show your transaction press \"S\"\tTo show your info press \"I\"\t";
	cout << "To change your info press \"T\"\tTo define your new travel, press \"N\"\t";
	cout << "To change your travel press \"M\"\tTo cancel your travel, press \"L\"";
	gotoxy((columns - 200) / 2, (rows + 2 * n + 1) / 2 + 22);
	cout << "To go back press Ctrl+B\t\tTo go home press Ctrl+H\t\t";
	cout << "To show all travels press\"A\"\tTo show details of travels press \"D\"";
	char ch=getch();
	system("cls");
	if (ch == 'N' || ch == 'n')
		travel_def_driver("bus");
	else if (ch == 'I' || ch == 'i')
		drivers_info(ID);
	else if (ch == 'T' || ch == 't')
		ch_driver_info(ID);
}
int main()
{
	fullscreen();
	screensize();
	//travel_def_driver("bus");
	pnl_drivers("mp64");
	/*loading(50, 250, 31, 50);
	welcome();*/
	//gotoxy(0, rows);
}
