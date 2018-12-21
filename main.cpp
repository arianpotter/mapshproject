#include <iostream>
#include <conio.h>
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include <string>
#include "Design.h"
#include <fstream>
using namespace std;
struct user{
    string username;
    string password;
    string name;
    string family;
    string number;
    string refrence;
    string bacc;
    string bpass;
}u;

/*
bool recaptcha(string u, string p)
{
	char temp1[100],temp2[100];
	int a;
	FILE *fp_userpass = fopen("../userpass.txt","r");
	while (fscanf(fp_userpass, "%s\t%s", temp1, temp2)+1)
	{
		if (temp1 == u && temp2 == p)
			return 1;
	}
	return 0;
}
*/
void login(int length, int with)
{
	system("cls");
	background(31);
	border(length, with);
	string u, p;
	//================================== Username ==================================
	gotoxy((columns - length) / 2 + 1, rows / 2 + 2);
	cout << " Password: ";
	gotoxy((columns - length) / 2 + 1, rows / 2);
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
	gotoxy((columns - length) / 2 + 12, rows / 2 + 2);
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
void sign_up(){
    fullscreen();
    screensize();
    system("cls");
	background(31);
	border(50, 39);
	string temp,tempp;
	char ch;


	//showing sign_up fields :


	gotoxy((columns - 50) / 2+2,(rows -39) / 2+1);
	cout<<"Username:(between 5 to 15 characters)";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+5);
	cout<<"Password: (between 4 to 10 characters)";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+9);
	cout<<"Retype Password: ";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+13);
	cout<<"Name: ";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+17);
	cout<<"Family: ";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+21);
	cout<<"Telephone Number: ";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+25);
	cout<<"if someone invited you to this system";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+26);
	cout<<"please write his/her username: (optional)";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+31);
	cout<<"Bank Account Number: ";
	gotoxy((columns - 50) / 2+2,(rows -39) / 2+35);
	cout<<"Bank Account Password: ";

//connecting users file :

    fstream user;
    user.open("r.txt",ios::in |ios::out|ios::app);
    user<<"\n";

//getting info:
//=========================username============================
    gotoxy((columns - 50) / 2+2,(rows -39) / 2+3);
    while (1)
	{
		ch = _getch();
		if (ch == 13){
            if(temp.length()<5){
                gotoxy(0,0);
                cout<<"Error: not enough character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+3);
                 continue;
            }
            break;
		}
		if (temp.length() == 15 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='_'||ch=='@'||ch=='.')
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+3);
                }
                continue;
	}
	}
    u.username=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                                              ";
//=========================password========================================
    gotoxy((columns - 50) / 2+2,(rows -39) / 2+7);
    while (1)
	{
		ch = _getch();
		if (ch == 13){
                if(temp.length()<4){
                    gotoxy(0,0);
                cout<<"Error: not enough character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+7);
                 continue;
                }
                break;
        }

		if (temp.length() == 10 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='_'||ch=='@'||ch=='.')
		{
			cout << '*';
			temp += ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+7);
                }
                continue;
	}
	}
    tempp=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                                            ";
l:    gotoxy((columns - 50) / 2+2,(rows -39) / 2+11);
    while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		if (temp.length() == 10 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='_'||ch=='@'||ch=='.')
		{
			cout << '*';
			temp += ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+11);
                }
                continue;
	}
	}
	gotoxy(0,0);
    cout<<"                                   ";
	if(temp!=tempp){
            int i=0;
            gotoxy((columns - 50) / 2+2,(rows -39) / 2+11);
        while(i<temp.length()){
            cout<<" ";
            i++;
        }
    gotoxy(0,0);
   cout<<"Error: retype your password correct";
    temp="";
    goto l;
	}
	u.password=tempp;
	temp="";
	tempp="";
//==============================name================================
	 gotoxy((columns - 50) / 2+2,(rows -39) / 2+15);
	 while (1)
	{
		ch = _getch();
		if (ch == 13){
            if(temp.length()==0){
                gotoxy(0,0);
                cout<<"Error: please enter a username";
                gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+15);
                continue;
            }
            break;
		}
		if (temp.length() == 38 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		{
			temp += ch;
			cout << ch;
		}
		else{
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+15);
                }
                continue;
	}
	}
    u.name=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                                                    ";
//==================================family=========================================
	 gotoxy((columns - 50) / 2+2,(rows -39) / 2+19);
	 while (1)
	{
		ch = _getch();
		if (ch == 13){
            if(temp.length()==0){
                gotoxy(0,0);
                cout<<"Error: please enter a family";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+19);
                 continue;
            }
            break;
		}
		if (temp.length() == 15 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+19);
                }
                continue;
	}
	}
    u.family=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                                                  ";
//=============================telephone========================================
	 gotoxy((columns - 50) / 2+2,(rows -39) / 2+23);
	 while (1)
	{
		ch = _getch();
		if (ch == 13){
            if(temp.length()==0){
                gotoxy(0,0);
                cout<<"Error: please enter a telephone number";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+23);
                 continue;
            }
            break;
		}
		if (temp.length() == 15 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if(ch>='0'&&ch<='9')
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+23);
                }
                continue;
	}
	}
    u.number=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                                                    ";
//=================================refrence======================================
	 gotoxy((columns - 50) / 2+2,(rows -39) / 2+28);
	 while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		if (temp.length() == 15 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch=='_'||ch=='@'||ch=='.')
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+28);
                }
                continue;
	}
	}
    u.refrence=temp;
    temp="";
    gotoxy(0,0);
    cout<<"                      ";


//banck account getting and checking



l2:gotoxy((columns - 50) / 2+2,(rows -39) / 2+33);
	 while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		if (temp.length() == 6 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if(ch>='0'&&ch<='9')
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+33);
                }
                continue;
	}
	}
    gotoxy(0,0);
    cout<<"                      ";
    fstream acc;
    string line;
    acc.open("accounts.txt",ios::in);
   size_t pos;
while(!acc.eof())
  {
      getline(acc,line); // get line from file
      pos=line.find(temp); // search
      if(pos!=string::npos) // string::npos is returned if string is not found
        {
            break;
        }
  }
  if(pos==string::npos||temp.length()!=6){
    gotoxy(0,0);
    cout<<"Error: wrong bank account number!";
    gotoxy((columns - 50) / 2+2,(rows -39) / 2+33);
    cout<<"       ";
    temp="";
    goto l2;
  }
  u.bacc=temp;
  gotoxy(0,0);
  cout<<"                                   ";
  temp="";
  l3:gotoxy((columns - 50) / 2+2,(rows -39) / 2+37);
	 while (1)
	{
		ch = _getch();
		if (ch == 13){
            if(temp.length()<4){
                gotoxy(0,0);
                cout<<"Error: not enough character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+37);
                 continue;
            }
            break;
		}
		if (temp.length() == 4 && ch != 8) continue;
		if (ch == 8)
		{
			if (temp.length() == 0) continue;
			cout << '\b' << " " << '\b';
			temp.erase(temp.end() - 1);
		}
		if(ch>='0'&&ch<='9')
		{
			temp += ch;
			cout << ch;
		}
		else {
                if(ch!=8&&ch!=127){
                gotoxy(0,0);
                cout<<"Error: wrong character";
                 gotoxy((columns - 50) / 2+2+temp.length(),(rows -39) / 2+37);
                }
                continue;
	}
	}

    gotoxy(0,0);
    cout<<"                                          ";
    pos=line.find(temp); // search
      if(pos!=string::npos) // string::npos is returned if string is not found
        {
            u.bpass=temp;
            gotoxy(0,0);
            cout<<"bank account connected!";
            user<<'1'<<u.bacc<<'\t'<<u.username<<'\t'<<u.password<<'\t'<<u.name<<'\t'<<u.family<<'\t'<<u.number<<'\t'<<u.refrence<<'\t'<<u.bacc<<'\t'<<u.bpass;
        }
        else{
            gotoxy(0,0);
            cout<<"your bank account password is incorrect!";
            gotoxy((columns - 50) / 2+2,(rows -39) / 2+37);
            cout<<"    ";
            temp="";
            goto l3;
        }
//closing files
    acc.close();
    user.close();
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
	else if (c == 'u' || c == 'U')sign_up();
	else if (c == 'g' || c == 'G');
	else;
}

inline void process(int time, int color, int n, int i)
{
	Sleep(time);
	gotoxy((columns - n) / 2 + i, rows / 2+1);
	print(char(219), color);
	Sleep(time);
	//gotoxy(columns / 2 - 5, rows / 2 - 2);
}
void loading(int time, int processcolor, int backcolor, int n)
{
	background(backcolor);
	gotoxy(columns / 2 - 4, rows / 2-2);
	border(n + 2, 1);
	gotoxy(0,0);
	for (int i = 0; i < n;)
	{
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
		process(time, processcolor, n, i);
		i++;
		if (i > n) break;
	}
	gotoxy(0, 0);
	Sleep(200);
}



int main()
{
	fullscreen();
	screensize();
	//loading(50, 255, 31, 50);
	//welcome();
	sign_up();
	gotoxy(0, rows);
}
