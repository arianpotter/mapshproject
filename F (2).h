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
#include "Design.h"

using namespace std;

//*********************************
//____________ loading ____________
#define LD_backcolor	31
#define LD_processcolor	250
//____________ welcome ____________
#define WL_backcolor	31
//_____________ login _____________
#define LN_backcolor	31
#define LN_errorcolor	20
//____________ sign up ____________
#define SU_backcolor	31
#define SU_captioncolor	30
#define SU_errorcolor	28
#define SU_acceptcolor	26
#define SU_warningcolor	24
#define SU_titrcolor	117
//___________ pnl-driver __________
#define DRV_backcolor	240
#define DRV_captioncolor 245
#define DRV_latercolor	242
#define DRV_todaycolor	241
#define DRV_faildcolor	248
#define DRV_cancelcolor	245
#define DRV_delaycolor	246
#define DRV_acceptcolor	242
#define DRV_warningcolor 248
#define DRV_errorcolor	244
#define DRV_arrowcolor	240
#define DRV_demoneycolor 241
#define DRV_inmoneycolor 244
//____________ pnl-user ___________
#define USR_backcolor	128
#define USR_captioncolor 132
#define USR_latercolor	143
#define USR_todaycolor	129
#define USR_faildcolor	134
#define USR_cancelcolor	141
#define USR_delaycolor	139
#define USR_acceptcolor	138
#define USR_warningcolor 135
#define USR_errorcolor	134
#define USR_arrowcolor	128
#define USR_demoneycolor 143
#define USR_inmoneycolor 132
#define USR_fullchaircolor 132
#define USR_emptychaircolor	135
//*********************************
#define Master_key "├£F▐"

COORD screen;

int nalltransaction, nalltravel, nsearchtravel;


struct User
{
	long int id;
	string username;
	string password;
	string name;
	string family;
	string phone;
	string account;
	string accpass;
	long long int money;
	string vehicle;
}user;
struct travelinfo
{
	travelinfo* previous = nullptr;
	long int id;
	int num = 0;
	int i;
	int f;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	string vehicle;
	long int id_driver;
	int delay = 0;
	travelinfo* next = nullptr;
}t0, t1;
struct passengerinfo
{
	passengerinfo* next;
	long int id;
	int num = 0;
	int chair = 0;
	string name;
	string family;
	string phone;
	passengerinfo* previous;
}p0;
struct transactioninfo
{
	transactioninfo* next;
	int num = 0;
	string acc;
	long int money;
	string date;
	transactioninfo* previous;
}r0;
struct vehicleinfo
{
	int velocity;
	int capacity;
	int price;//tooman per km
}bus, train, airplane;

int USR_CHAIR_row, USR_CHAIR_column;
int TR_i;
//------------------------------------------------------------------ Linked list -------------------------------------------------------------------
void LN_addtransaction(string account, string date, long int money)
{
	transactioninfo* r = &r0;
	if (r0.num)
	{
		while (r->next != NULL)
			r = r->next;
		r->next = new transactioninfo;
		r->next->previous = r;
		r = r->next;
		r->num = r->previous->num + 1;
	}
	else r->num = 1;

	r->acc = account;
	r->date = date;
	r->money = money;
	r->next = NULL;
}
int readtransaction(string acc)
{
	string l, hour, minute, day, month, year;
	ifstream transaction("Transactions.txt");
	transactioninfo* r = &r0;

	int i = 0;
	for (; getline(transaction, l);)
	{
		stringstream s;
		s << l;
		s >> r->acc;
		if (r->acc == acc)
		{
			s >> r->money >> day >> month >> year >> hour >> minute;
			r->date = day + "/" + month + "/" + year + "\t" + hour + ":" + minute;
			r->num = ++i;
			r->next = new transactioninfo;
			r->next->previous = r;
			r = r->next;
		}
	}
	if (r->previous != NULL)
	{
		r->previous->next = NULL;
		delete r;
	}
	return i;
}

/*void LN_addpassenger(long int id, int chair, string name, string family, string phone)
{
	passengerinfo* p = &p0;
	if (p0.num)
	{
		while (p->next != NULL)
			p = p->next;
		p->next = new passengerinfo;
		p->next->previous = p;
		p = p->next;
		p->num = p->previous->num + 1;
	}
	else p->num = 1;
	p->id = id;
	p->chair = chair;
	p->name = name;
	p->family = family;
	p->phone = phone;
	p->next = NULL;
}*/
int passenger(string chairs)
{
	passengerinfo* p = &p0;
	long int id;
	int n = 0;
	string l;
	stringstream s;

	s << chairs;
	s >> id >> id;

	for (int i = 1; s >> id; i++)
	{
		if (!id) continue;
		if (id / 1000000 == 1)
		{
			ifstream userinformation("Users Information.txt");
			while (getline(userinformation, l))
			{
				long int idtemp;
				stringstream ss;
				ss << l;
				ss >> idtemp;
				if (id == idtemp)
				{
					p->id = idtemp;
					ss >> p->name >> p->family >> p->phone;
					p->num = ++n;
					p->chair = i;
					break;
				}
			}
			userinformation.close();
		}
		else
		{
			ifstream guest("Guests.txt");
			while (getline(guest, l))
			{
				long int idtemp;
				stringstream ss;
				ss << l;
				ss >> idtemp;
				if (id == idtemp)
				{
					p->id = idtemp;
					ss >> p->name >> p->family >> p->phone;
					p->num = n + 1, n++;
					p->chair = i;
					break;
				}
			}
			guest.close();
		}
		p->next = new passengerinfo;
		p->next->previous = p;
		p = p->next;
	}
	if (p->previous != NULL)
	{
		p->previous->next = NULL;
		delete p;
	}
	return n;
}

void LN_addtravel(travelinfo* first, long int id, long int id_driver, int i, int f, int day, int month, int year, int hour, int minute, int delay, string vehicle)
{
	travelinfo* t = first;
	if (first->num)
	{
		while (t->next != NULL)
			t = t->next;
		t->next = new travelinfo;
		t->next->previous = t;
		t = t->next;
		t->num = t->previous->num + 1;
	}
	else t->num = 1;

	t->id = id;
	t->id_driver = id_driver;
	t->i = i;
	t->f = f;
	t->day = day;
	t->month = month;
	t->year = year;
	t->hour = hour;
	t->minute = minute;
	t->delay = delay;
	t->vehicle = vehicle;

	nalltravel++;

	t->next = NULL;
}
int readTravel(long int id)
{
	ifstream travels("Travels.txt");
	travelinfo* t = &t0;
	string l;
	int n = 0;
	getline(travels, l);
	while (getline(travels, l))
	{
		stringstream line;
		line << l;
		line >> t->id >> t->i >> t->f >> t->day >> t->month >> t->year >> t->hour >> t->minute >> t->vehicle >> t->id_driver >> t->delay;
		if (t->id_driver != id) continue;
		t->num = ++n;
		t->next = new travelinfo;
		t->next->previous = t;
		t = t->next;
	}
	if (t->previous != NULL)
	{
		t->previous->next = nullptr;
		delete t;
	}

	return n;
}
//*********************************
tm* time()
{
	tm* timeinfo = new tm;
	time_t rawtime;
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	return timeinfo;
}


inline string int_to_str(long int a)
{
	if (a == 0) return "0";
	if (a < 0)
	{
		a = -a;
		string str;
		for (; a > 0; a /= 10)
			str.insert(str.begin(), a % 10 + 48);
		str.insert(str.begin(), '-');
		return str;
	}
	string str;
	for (; a > 0; a /= 10)
		str.insert(str.begin(), a % 10 + 48);
	return str;
}
inline string int_to_str(long int a, unsigned int size)
{
	string str;
	a %= (int)pow(10, size);
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

string c(string l, char key)
{
	string s;
	for (int i = 0; i < l.length(); i++)
		s += l[i] ^ key;
	return s;
}
string code(string l, string key)
{
	for (int i = 0; key[i] != '\0'; i++)
		l = c(l, key[i]);
	return l;
}

int edit(string search, string replace, string fileaddress)
{
	//search = code(search, Master_key);
	//replace = code(replace, Master_key);
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

void freeln(passengerinfo* p)
{
	if (p->next != NULL)
		freeln(p->next);
	delete p;
	/*if (p->next != NULL) freeln(p->next);
		p->next = p->previous = NULL;
	if (p->previous == NULL)
		p0.num = 0;
*/
	//delete(p);
}
void freeln(travelinfo* t)
{
	if (t->next != NULL) freeln(t->next);
		t->next = t->previous = NULL;
	if (t->previous == NULL) 
		t1.num = 0;

	//delete(t);
}

//------------------------------------------------------------------ ticketprice -------------------------------------------------------------------
double distance(int i, int f)
{
	//================================= Find in file ================================
	if (i > f) i += f, f = i - f, i -= f;
	ifstream city("cities.txt");
	string l;
	int xi, xf, yi, yf;
	for (int j = 1; j < i && getline(city, l); j++);
	city >> xi >> xi >> yi;
	for (int j = i; j < f && getline(city, l); j++);
	city >> xf >> xf >> yf;
	//================================= calculating =================================
	return sqrt((xi - xf)*(xi - xf) + (yi - yf)*(yi - yf));
}

//1000 toman
int ifmoney(int i, int f, string vehicle)
{

	int price, dist = distance(i, f);
	if (vehicle == "Bus") price = (dist*bus.price) / 1000;
	if (vehicle == "Train") price = (dist*train.price) / 1000;
	if (vehicle == "Plane")price = (dist*airplane.price) / 1000;
	return price;
}
//1000 toman
//RETURN	-1: less money | 0: dont find account | 1:OK
//CODE		 1:user | 2:driver | 3:admin | 4:guest || -:cancel
int do_transaction(string acc, double dmoney, int id_travel, int code)
{
	tm* timer = time();
	double money;
	string pass, l;

	ifstream account("accounts.txt");
	for (int i = 200000; i < stoi(acc) && getline(account, l); i++);
	account >> money >> pass >> money;
	account.close();
	if (money + dmoney * 1000 < 0) return -1;

	if (edit(acc + "\t" + pass + "\t" + int_to_str(money), acc + "\t" + pass + "\t" + int_to_str(money + dmoney * 1000), "accounts.txt") == 0)
		return 0;

	fstream transaction("Transactions.txt", ios::app);
	transaction << acc << "\t" << dmoney * 1000 << "\t" << int_to_str(timer->tm_mday, 2) << "\t" << int_to_str(timer->tm_mon + 1, 2) << "\t" << timer->tm_year + 1900 << "\t" << int_to_str(timer->tm_hour, 2) << "\t" << int_to_str(timer->tm_min, 2) << "\t" << int_to_str(id_travel) << "\t" << int_to_str(code) << "\n";
	transaction.close();
	return 1;
}

string find_chairs(long int id)
{
	string l;
	long int id_travel;
	ifstream chairs("Chairs.txt");

	while (getline(chairs, l))
	{
		stringstream s;
		s << l;
		s >> id_travel;
		if (id_travel == id) return l;
	}
}

long int* costed_money(int id_travel, long int id_user = -1)
{
	if (id_user == -1)
	{
		int accnum, idt, pri, code;
		long int price[351] = { 0 };
		long int sum = 0;
		long int id;
		string l = find_chairs(id_travel), ll;
		stringstream s;

		s << l;
		s >> id >> id;
		for (int i = 0; s >> id;)
		{
			if (!id)continue;

			ifstream transaction("Transactions.txt");
			while (getline(transaction, ll))
			{
				string date;
				stringstream ss;
				ss << ll;
				ss >> accnum >> pri >> date >> date >> date >> date >> date >> idt >> code;
				if (accnum == id % 1000000 && code == 1 && id_travel == idt)
				{
					price[i] = pri;
					sum += price[i];
					i++;
					break;
				}
			}
			transaction.close();
		}
		price[350] = sum;
		return price;
	}
	else
	{
		string ll;
		long int accnum, pri, idt, code, id;
		ifstream transaction("Transactions.txt");
		while (getline(transaction, ll))
		{
			string date;
			stringstream ss;
			ss << ll;
			ss >> accnum >> pri >> date >> date >> date >> date >> date >> idt >> code;
			if (accnum == id_user % 1000000 && code == 1 && id_travel == idt)
			{
				return &pri;
			}
		}
		transaction.close();
	}
}

bool isfull(int column, string chair)
{
	int chairnum = USR_CHAIR_row*column + USR_CHAIR_column, k;
	stringstream s;
	s << chair;
	for (int i = -2; i < chairnum && s >> k; i++);
	if (k) return true;
	return false;
}


void arrow(int x, int y, int linenum, int time, int n, int length)
{
	char ch;
	n == length ? ch = '>' : ch = '-';
	int arrowcolor = DRV_arrowcolor;
	if (user.id / 1000000 == 1)
		arrowcolor = USR_arrowcolor;
	for (int i = 0; i < linenum; i++)
	{
		n == 0 ? print(' ', arrowcolor, x + length, y + i) : print(' ', arrowcolor, x + n - 1, y + i);
		print(ch, arrowcolor, x + n, y + i);
	}
	Sleep(time);
}
//------------------------------------------------------------------ vehicleinfo -------------------------------------------------------------------
void vehicles()
{
	ifstream vehicleinformation("Vehicle information.txt");
	vehicleinformation >> bus.price >> bus.capacity >> bus.velocity >> train.price >> train.capacity >> train.velocity >> airplane.price >> airplane.capacity >> airplane.velocity;
	vehicleinformation.close();
}
