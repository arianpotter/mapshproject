#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <math.h>
#include "F.h"
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
//*********************************



int nalltransaction, nalltravel;



COORD screen;
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
}t0;
struct passengerinfo
{
	passengerinfo* next;
	long int id;
	int num = 0;
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

//*********************************
void alltravelshow(bool showfiald, int n, travelinfo *first);
void welcome(int sleeptime);
void signup(int length, int width);
void pnl_drivers(int length, int width);
void pnl_user(int length, int width);
//*********************************

tm* time()
{
	time_t rawtime;
	tm * timeinfo;

	timeinfo = new tm;

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	return timeinfo;
}

//------------------------------------------------------------------ ticketprice -------------------------------------------------------------------
//1000 toman
int ifmoney(int i, int f, string vehicle)
{
	//================================= Find in file ================================
	if (i > f) i += f, f = i - f, i -= f;
	ifstream city("cities.txt");
	string l;
	int xi, xf, yi, yf;
	for (int j = 1; j < i && getline(city, l); j++);
	city >> xi >> xi >> yi;
	for (int j = i + 1; j < f && getline(city, l); j++);
	city >> xf >> xf >> yf;
	//================================= calculating =================================
	double dist = sqrt((xi - xf)*(xi - xf) + (yi - yf)*(yi - yf));
	int price;
	if (vehicle == "Bus") price = (dist*bus.price) / 1000;
	if (vehicle == "Train") price = (dist*train.price) / 1000;
	if (vehicle == "Plane")price = (dist*airplane.price) / 1000;
	return price;
}
//1000 toman
//-1: less money | 0: dont find account | 1:OK
int do_transaction(string acc, double dmoney)
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
	transaction << acc << "\t" << dmoney * 1000 << "\t" << int_to_str(timer->tm_mday, 2) << "\t" << int_to_str(timer->tm_mon + 1, 2) << "\t" << timer->tm_year + 1900 << "\t" << int_to_str(timer->tm_hour, 2) << "\t" << int_to_str(timer->tm_min, 2) << "\n";
	transaction.close();
	return 1;
}
//------------------------------------------------------------------ vehicleinfo -------------------------------------------------------------------
void vehicles()
{
	ifstream vehicleinformation("Vehicle information.txt");
	vehicleinformation >> bus.price >> bus.capacity >> bus.velocity >> train.price >> train.capacity >> train.velocity >> airplane.price >> airplane.capacity >> airplane.velocity;
	vehicleinformation.close();
}






//------------------------------------------------------------------- pnl_driver -------------------------------------------------------------------
inline void DRV_showtop(int length, int width)
{
	cursor(false);
	background(DRV_backcolor, screen);
	print(' ', DRV_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
	print(" Hi " + user.name + " " + user.family + "!" + "                Username: " + user.username + "                Vehicle: " + user.vehicle, DRV_captioncolor, 5, 2);
	print("", DRV_backcolor);
	border(length, width, screen);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ transaction +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
		delete(r);
	}
	return i;
}
inline transactioninfo* transactionshow(int n, transactioninfo *first = &r0)
{
	int backcolor = DRV_backcolor, inmoneycolor = DRV_inmoneycolor, demoneycolor = DRV_demoneycolor;
	if (user.id / 1000000 == 1)
		backcolor = USR_backcolor, inmoneycolor = USR_inmoneycolor, demoneycolor = USR_demoneycolor;

	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', backcolor, 6, i, screen.X - 13);

	if (!r0.num) return &r0;

	transactioninfo *currenttransaction = first, *last = first;

	for (int i = first->num; currenttransaction != nullptr && i <= n + first->num; currenttransaction = currenttransaction->next, i++)
	{
		if (currenttransaction->money<0)
			print("   " + int_to_str(currenttransaction->num) + "\t" + int_to_str(currenttransaction->money) + "\t\t" + currenttransaction->date, inmoneycolor, 7, 7 + i - first->num);
		else 
			print("   " + int_to_str(currenttransaction->num) + "\t " + int_to_str(currenttransaction->money) + "\t\t" + currenttransaction->date, demoneycolor, 7, 7 + i - first->num);
		if (currenttransaction->next == NULL || i == n + first->num) last = currenttransaction;
	}
	return last;
}
void alltransactions(int n, transactioninfo *first)
{
	int backcolor = DRV_backcolor, captioncolor = DRV_captioncolor;
	if (user.id / 1000000 == 1)
		backcolor = USR_backcolor, captioncolor = USR_captioncolor;

	print("Your transactions:           ", backcolor, 7, 6);
	while (1)
	{
		transactioninfo *k = transactionshow(n, first);

		print(' ', captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
		if (first->num > 1) print("                     <-: Previous page", captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalltransaction) print("->: Next page", captioncolor, 7, screen.Y - 2);

		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalltransaction)
				alltransactions(n, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				alltransactions(n, first);
			}
			break;

		case 2:
		case 16:
		case 26:
			if (user.id / 1000000 == 2)
				pnl_drivers(screen.X - 11, screen.Y - 10);
			else
				pnl_user(screen.X - 11, screen.Y - 10);
			break;
		case 27:
			exit(0);
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ show_detail +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline travelinfo* DRV_TD_id()
{
	string l;
	travelinfo *t = &t0;
	//===================================== Show ====================================
	print("Which travel do you want to watch detail?", DRV_captioncolor, 7, screen.Y - 3);

	cursor(true);
	do
	{
		l = input(0, 6, 49, screen.Y - 3, 54, screen.Y - 3, DRV_backcolor, DRV_errorcolor, "bpzEn");
		if (l == "~E") exit(0);
		else if (l == "~z" || l == "~b")
		{
			print(' ', DRV_backcolor, 7, screen.Y - 3, 50);
			cursor(false);
			return NULL;
		}
		else if (l == "~p")
			pnl_drivers(screen.X - 11, screen.Y - 10);

		else if (l == "") l = "0";
	} while (stoi(l) > nalltravel || stoi(l) < 1);

	for (int i = 1; i < stoi(l); i++, t = t->next);
	cursor(false);
	return t;
}
inline string find_chairs(long int id)
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

int passenger(string chairs)
{
	passengerinfo* p = &p0;
	long int id;
	int capacity, n = 0;
	string l;
	stringstream s;

	s << chairs;
	s >> id >> capacity;

	while (s >> id)
	{
		if (!id) continue;
		if (id >= 1200000)
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
					p->num = ++n;
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
		delete(p);
	}
	return n;
}
inline passengerinfo* passengershow(int n, passengerinfo* first = &p0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);

	if (!p0.num) return &p0;

	passengerinfo *currentpassenger = first, *last = first;

	for (int i = first->num; currentpassenger != nullptr && i <= n + first->num; currentpassenger = currentpassenger->next, i++)
	{
		print("   " + int_to_str(currentpassenger->num) + "\t" + currentpassenger->name + " " + currentpassenger->family, DRV_backcolor, 7, 7 + i - first->num);
		print(currentpassenger->phone, DRV_backcolor, 50, 7 + i - first->num);
		if (currentpassenger->next == NULL || i == n + first->num) last = currentpassenger;
	}
	return last;
}
void allpassengershow(int n, int nalldetail, passengerinfo* first)
{
	print("Passengers :                 ", DRV_backcolor, 7, 6);
	while (1)
	{
		passengerinfo *k = passengershow(screen.Y - 12, first);

		print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
		if (first->num > 1) print("                     <-: Previous page", DRV_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalldetail) print("->: Next page", DRV_captioncolor, 7, screen.Y - 2);

		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalldetail)
				allpassengershow(screen.Y - 12, nalldetail, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				allpassengershow(screen.Y - 12, nalldetail, first);
			}
			break;

		case 2:
		case 26:
			alltravelshow(true, screen.Y - 12, &t0);
			break;
		case 16:
			pnl_drivers(screen.X - 11, screen.Y - 10);
			break;
		case 27:
			exit(0);
		}
	}
}
void detail()
{
	//================================= Find in file ================================
	travelinfo* t = DRV_TD_id();
	if (t == NULL) return;
	string chair = find_chairs(t->id);
	//===================================== Show ====================================
	int nalldetail = passenger(chair);

	print(' ', DRV_captioncolor, 5, screen.Y - 3, screen.X - 2 * 5 - 1);
	allpassengershow(screen.Y - 12, nalldetail, &p0);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_travel +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline travelinfo* DRV_ET_id()
{
	//===================================== Show ===================================
	print("Which travel do you want to edit?", DRV_captioncolor, 7, screen.Y - 3);

	string l;
	travelinfo *t = &t0;
	tm *timer = time();
	bool islater;

	cursor(true);
	do
	{
		do
		{
			l = input(0, 6, 41, screen.Y - 3, 48, screen.Y - 3, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (l == "~E") exit(0);
			else if (l == "~z" || l == "~b")
			{
				print(' ', DRV_backcolor, 7, screen.Y - 3, 100);
				cursor(false);
				return NULL;
			}
			else if (l == "~p")
			{
				DRV_showtop(screen.X - 11, screen.Y - 10);
				pnl_drivers(screen.X - 11, screen.Y - 10);
			}
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);

		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);
		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't edit past travels!", DRV_errorcolor, 48, screen.Y - 3);
		else if (t->delay == -1) print("You can't edit canceled travels!", DRV_errorcolor, 48, screen.Y - 3);

	} while (!islater || t->delay == -1);
	return t;
}
travelinfo DRV_edittravel;
inline void DRV_ET_day(int x, int y)
{
	string day;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (day == "~p")
			{
				DRV_showtop(screen.X - 11, screen.Y - 10);
				pnl_drivers(screen.X - 11, screen.Y - 10);
			}
			else if (day == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, &t0);
			else if (day == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), DRV_backcolor, x + 8, y + 5);
				DRV_showtop(screen.X - 11, screen.Y - 10);
				alltravelshow(true, screen.Y - 12, &t0);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');
		DRV_edittravel.day = stoi(day);

		if (DRV_edittravel.day > 31 || DRV_edittravel.day < 1)
		{
			print("Must be between 1 and 31", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (DRV_edittravel.day > 31 || DRV_edittravel.day < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_ET_month(int x, int y)
{
	string month;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (month == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (month == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, &t0);
			else if (month == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mon + 1, 2), DRV_backcolor, x + 11, y + 5);
				DRV_ET_day(x, y);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');
		DRV_edittravel.month = stoi(month);

		if (DRV_edittravel.month > 12 || DRV_edittravel.month < 1)
		{
			print("Must be between 1 and 12", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (DRV_edittravel.month > 12 || DRV_edittravel.month < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_ET_year(int x, int y, travelinfo *t)
{
	string year;
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			year = input(4, 4, x + 14, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (year == "~b" || year == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (year == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, &t0);
			else if (year == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_year + 1900, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_month(x, y);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');
		DRV_edittravel.year = stoi(year);

		islater = (t->year < DRV_edittravel.year || (t->year == DRV_edittravel.year && yday(t->month, t->day) <= yday(DRV_edittravel.month, DRV_edittravel.day)));
		if (!islater)
		{
			print("You can't make travel earlier!", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (!islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_ET_hour(int x, int y, travelinfo *t)
{
	string hour;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (hour == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (hour == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, &t0);
			else if (hour == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_hour, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_year(x, y, t);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');
		DRV_edittravel.hour = stoi(hour);

		if (DRV_edittravel.hour > 23 || DRV_edittravel.hour < 0)
		{
			print("Must be between 0 and 23", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (DRV_edittravel.hour > 23 || DRV_edittravel.hour < 0);
	print(' ', DRV_acceptcolor, x + 1, y + 7);
}
inline void DRV_ET_minute(int x, int y, travelinfo *t)
{
	string minute;
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	do
	{
		do
		{
			minute = input(2, 2, x + 11, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (minute == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (minute == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, &t0);
			else if (minute == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_min, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_hour(x, y, t);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');
		DRV_edittravel.minute = stoi(minute);

		islater = (t->year < DRV_edittravel.year || (t->year == DRV_edittravel.year && (yday(t->month, t->day) < yday(DRV_edittravel.month, DRV_edittravel.day) || (yday(t->month, t->day) == yday(DRV_edittravel.month, DRV_edittravel.day) && (t->hour < DRV_edittravel.hour || (t->hour == DRV_edittravel.hour && t->minute <= DRV_edittravel.minute))))));
		if (DRV_edittravel.minute < 0 || DRV_edittravel.minute >= 60)
		{
			print("Must be between 0 and 59", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
		else if (!islater)
		{
			print("You can't make travel earlier!", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (DRV_edittravel.minute < 0 || DRV_edittravel.minute >= 60 || !islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}

void edit_travel(int length, int width)
{
	travelinfo *t = DRV_ET_id();
	if (t == NULL) return;
	
	system("cls");
	border(length, width, screen);
	cursor(false);
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", DRV_captioncolor, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("From: ", DRV_captioncolor, x + 2, y + 1);
	print(t->i, DRV_captioncolor, x + 8, y + 1);
	print("To: ", DRV_captioncolor, x + 2, y + 3);
	print(t->f, DRV_captioncolor, x + 6, y + 3);
	print("Date: ", DRV_captioncolor, x + 2, y + 5);
	print(int_to_str(t->day, 2) + "/" + int_to_str(t->month, 2) + "/" + int_to_str(t->year), DRV_backcolor, x + 8, y + 5);
	print("Time: ", DRV_captioncolor, x + 2, y + 7);
	print(int_to_str(t->hour, 2) + ":" + int_to_str(t->minute, 2), DRV_backcolor, x + 8, y + 7);

	//===================================== Input ===================================
	cursor(true);
	
	DRV_ET_day(x, y);
	DRV_ET_month(x, y);
	DRV_ET_year(x, y, t);
	DRV_ET_hour(x, y, t);
	DRV_ET_minute(x, y, t);

	cursor(false);
	//============================= Edit file & linked list =========================
	int delayhour, capacity = 0;
	long int k;

	delayhour = (DRV_edittravel.year - t->year) * 8760 + (DRV_edittravel.month - t->month) * 720 + (DRV_edittravel.day - t->day) * 24 + (DRV_edittravel.hour - t->hour);
	if (DRV_edittravel.minute < t->minute) delayhour--;
	double delayprice = (float) ifmoney(t->i, t->f, t->vehicle) * (float) delayhour * 5.0 / 100.0;
	//check if there is enough money in admin & driver acc

	string ll = find_chairs(t->id);
	stringstream passengers, ss;

	passengers << ll;
	ss << ll;

	passengers >> k >> k;
	ss >> k >> k;
	while (ss >> k)
		if (k)
			capacity++;

	if (do_transaction(user.account, (0.9)* delayprice * capacity * (-1)) + 1)
	{
		if (do_transaction("200000", (0.1)* delayprice * capacity * (-1)) + 1)
		{
			string search = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			t->delay += delayhour;
			//if (DRV_edit.minute < t->minute) t->delay--;
			t->day = DRV_edittravel.day;
			t->month = DRV_edittravel.month;
			t->year = DRV_edittravel.year;
			t->hour = DRV_edittravel.hour;
			t->minute = DRV_edittravel.minute;
			string replace = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			edit(search, replace, "Travels.txt");

			//return money to passengers accs
			long int id_passenger;
			while (passengers >> id_passenger)
			{
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), delayprice);
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, screen.X / 2 - 19, screen.Y / 2 + 4);
			Sleep(3000);
			do_transaction(user.account, (0.9) * delayprice * capacity);
		}
	}
	else
	{
		print("Your account balance is not enough!", DRV_errorcolor, screen.X / 2 - 18, screen.Y / 2 + 4);
		Sleep(3000);
	}
	DRV_showtop(screen.X - 11, screen.Y - 10);
	alltravelshow(screen.X - 11, screen.Y - 10, &t0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ cancel_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void cancel_travel()
{
	bool islater;
	string l;
	travelinfo *t = &t0;
	tm *timer = time();
	//===================================== Input ===================================
	print("Which travel do you want to cancel?", DRV_captioncolor, 7, screen.Y - 3);
	cursor(true);
	do
	{
		do
		{
			l = input(0, 6, 43, screen.Y - 3, 50, screen.Y - 3, DRV_backcolor, DRV_errorcolor, "bpzEn", 34);
			if (l == "~E") exit(0);
			else if (l == "~z" || l == "~b")
			{
				print(' ', DRV_backcolor, 7, screen.Y - 3, 100);
				cursor(false);
				return;
			}
			else if (l == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);

		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);

		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't cancel past travels!", DRV_errorcolor, 50, screen.Y - 3);
		else if (t->delay == -1) print("You can't cancel canceled travels!", DRV_errorcolor, 50, screen.Y - 3);

	} while (!islater || t->delay == -1);
	cursor(false);
	//==================================== Account ==================================
	int t_price, capacity = 0;
	long int k;

	string ll = find_chairs(t->id);
	stringstream passengers, ss;

	passengers << ll;
	ss << ll;

	passengers >> k >> k;
	ss >> k >> k;
	while (ss >> k)
		if (k)
			capacity++;

	t_price = ifmoney(t->i, t->f, t->vehicle);
	long int id_passenger;

	//check if there is enough money in admin & driver acc
	if (do_transaction(user.account, (0.9)* t_price * capacity * (-1)) + 1)
	{
		if (do_transaction("200000", (0.1)* t_price * capacity * (-1)) + 1)
		{
			string s = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t";
			edit(s + int_to_str(t->delay), s + "-1", "Travels.txt");
			t->delay = -1;
			print(' ', DRV_backcolor, 7, screen.Y - 3, 50);
			//return money to passengers accs
			while (passengers >> id_passenger)
			{
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), t_price);
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, 50, screen.Y - 3);
			Sleep(3000);
			do_transaction(user.account, (0.9) * t_price * capacity);
			print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
		}
	}
	else
	{
		print("Your account balance is not enough!", DRV_errorcolor, 50, screen.Y - 3);
		Sleep(3000);
		print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ new_travel +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
travelinfo DRV_newtravel;
inline void DRV_NT_i(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 1);
	print("between 1 and 300", DRV_warningcolor, x + 4, y + 2);
	string i;
	do
	{
		do
		{
			i = input(1, 3, x + 8, y + 1, x + 4, y + 2, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (i == "~E") exit(0);
		} while (i[0] == '~');
		DRV_newtravel.i = stoi(i);

		if (DRV_newtravel.i > 300 || DRV_newtravel.i < 1)
		{
			print("Must be between 1 and 300", DRV_errorcolor, x + 4, y + 2);
			print('X', DRV_errorcolor, x + 1, y + 1);
		}
	} while (DRV_newtravel.i > 300 || DRV_newtravel.i < 1);
	print(char(-5), DRV_acceptcolor, x + 1, y + 1);
}
inline void DRV_NT_f(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 3);
	print("between 1 and 300", DRV_warningcolor, x + 4, y + 4);
	string f;
	do
	{
		do
		{
			f = input(1, 3, x + 6, y + 3, x + 4, y + 4, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (f == "~b" || f == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (f == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 3);
				print(' ', DRV_backcolor, x + 4, y + 4, 30);
				DRV_NT_i(x, y);
				print("between 1 and 300", DRV_warningcolor, x + 4, y + 4);
			}
			else if (f == "~E") exit(0);
		} while (f[0] == '~');
		DRV_newtravel.f = stoi(f);

		if (DRV_newtravel.f > 300 || DRV_newtravel.f < 1)
		{
			print("Must be between 1 and 300", DRV_errorcolor, x + 4, y + 4);
			print('X', DRV_errorcolor, x + 1, y + 3);
		}
		else if (DRV_newtravel.f == DRV_newtravel.i)
		{
			print("Invalid city", DRV_errorcolor, x + 4, y + 4);
			print('X', DRV_errorcolor, x + 1, y + 3);
		}
	} while (DRV_newtravel.f > 300 || DRV_newtravel.f < 1 || DRV_newtravel.f == DRV_newtravel.i);
	print(char(-5), DRV_acceptcolor, x + 1, y + 3);
}
inline void DRV_NT_day(int x, int y)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	string day;
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (day == "~b" || day == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (day == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), DRV_backcolor, x + 8, y + 5);
				DRV_NT_f(x, y);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');
		DRV_newtravel.day = stoi(day);

		if (DRV_newtravel.day > 31 || DRV_newtravel.day < 1)
		{
			print("Must be between 1 and 31", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (DRV_newtravel.day > 31 || DRV_newtravel.day < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_month(int x, int y)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	string month;
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (month == "~b" || month == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (month == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mon + 1, 2), DRV_backcolor, x + 11, y + 5);
				DRV_NT_day(x, y);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');
		DRV_newtravel.month = stoi(month);

		if (DRV_newtravel.month > 12 || DRV_newtravel.month < 1)
		{
			print("Must be between 1 and 12", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (DRV_newtravel.month > 12 || DRV_newtravel.month < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_year(int x, int y)
{
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	string year;
	do
	{
		do
		{
			year = input(4, 4, x + 14, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (year == "~b" || year == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (year == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_year + 1900, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_month(x, y);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');
		DRV_newtravel.year = stoi(year);

		islater = (timer->tm_year + 1900 < DRV_newtravel.year || (timer->tm_year + 1900 == DRV_newtravel.year && timer->tm_yday <= yday(DRV_newtravel.month, DRV_newtravel.day) - 1));
		if (!islater)
		{
			print("Can you traval in time?", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (!islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_hour(int x, int y)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	string hour;
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (hour == "~b" || hour == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (hour == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_hour, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_year(x, y);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');
		DRV_newtravel.hour = stoi(hour);

		if (DRV_newtravel.hour > 23 || DRV_newtravel.hour < 0)
		{
			print("Must be between 0 and 23", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (DRV_newtravel.hour > 23 || DRV_newtravel.hour < 0);
	print(' ', DRV_acceptcolor, x + 1, y + 7);
}
inline void DRV_NT_minute(int x, int y)
{
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	string minute;
	do
	{
		do
		{
			minute = input(2, 2, x + 11, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (minute == "~b" || minute == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (minute == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_min, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_hour(x, y);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');
		DRV_newtravel.minute = stoi(minute);

		islater = (timer->tm_year + 1900 < DRV_newtravel.year || (timer->tm_year + 1900 == DRV_newtravel.year && (timer->tm_yday < yday(DRV_newtravel.month, DRV_newtravel.day) - 1 || (timer->tm_yday == yday(DRV_newtravel.month, DRV_newtravel.day) - 1 && (timer->tm_hour < DRV_newtravel.hour || (timer->tm_hour == DRV_newtravel.hour && timer->tm_min <= DRV_newtravel.minute))))));
		if (DRV_newtravel.minute < 0 || DRV_newtravel.minute >= 60)
		{
			print("Must be between 0 and 59", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
		else if (!islater)
		{
			print("Can you traval in time?", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (DRV_newtravel.minute < 0 || DRV_newtravel.minute >= 60 || !islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}
void new_travel(int length, int width)
{
	//==================================== Show ====================================
	tm* timer = time();
	print("", DRV_backcolor);
	system("cls");
	border(length, width, screen);
	cursor(false);
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", DRV_captioncolor, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("From: ", DRV_captioncolor, x + 2, y + 1);
	print("To: ", DRV_captioncolor, x + 2, y + 3);
	print("Date: ", DRV_captioncolor, x + 2, y + 5);
	print(int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900), DRV_backcolor, x + 8, y + 5);
	print("Time: ", DRV_captioncolor, x + 2, y + 7);
	print(int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), DRV_backcolor, x + 8, y + 7);
	
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	//print("E: Edit information", DRV_captioncolor, 7, screen.Y - 2);
	cursor(true);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	DRV_NT_i(x, y);
	DRV_NT_f(x, y);
	DRV_NT_day(x, y);
	DRV_NT_month(x, y);
	DRV_NT_year(x, y);
	DRV_NT_hour(x, y);
	DRV_NT_minute(x, y);
	//================================ Write in file ===============================
	ifstream travels;
	travels.open("Travels.txt", ios::in);
	int id_travel;
	travels >> id_travel;
	travels.close();

	edit(int_to_str(id_travel), int_to_str(1 + id_travel), "Travels.txt");
	id_travel++;

	ofstream travel;
	travel.open("Travels.txt", ios::app);
	travel << id_travel << "\t" << DRV_newtravel.i << "\t" << DRV_newtravel.f << "\t" << DRV_newtravel.day << "\t" << DRV_newtravel.month << "\t" << DRV_newtravel.year << "\t" << DRV_newtravel.hour << "\t" << DRV_newtravel.minute << "\t" << user.vehicle << "\t" << user.id << "\t0\n";
	travel.close();
	//write in chairs
	fstream chairs("Chairs.txt",ios::app);
	chairs << id_travel << "\t";
	if (user.vehicle == "Bus")
	{
		chairs << bus.capacity;
		for (int i = 0; i < bus.capacity; i++)
			chairs << "\t0";
	}
	else if (user.vehicle == "Train")
	{
		chairs << train.capacity;
		for (int i = 0; i < train.capacity; i++)
			chairs << "\t0";
	}
	else
	{
		chairs << airplane.capacity;
		for (int i = 0; i < airplane.capacity; i++)
			chairs << "\t0";
	}
	chairs << "\n";
	chairs.close();
	//============================== Write in travelinfo ===========================
	travelinfo* t = &t0;
	while (t->next != NULL) t = t->next;
	t->next = new travelinfo;
	t->next->previous = t;
	t = t->next;
	t->id = id_travel;
	t->i = DRV_newtravel.i;
	t->f = DRV_newtravel.f;
	t->day = DRV_newtravel.day;
	t->month = DRV_newtravel.month;
	t->year = DRV_newtravel.year;
	t->hour = DRV_newtravel.hour;
	t->minute = DRV_newtravel.minute;
	t->vehicle = user.vehicle;
	t->id_driver = user.id;
	t->num = t->previous->num + 1;

	nalltravel++;

	DRV_showtop(screen.X - 11, screen.Y - 10 + 1);
	pnl_drivers(screen.X - 11, screen.Y - 10 + 1);

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_driver ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
User DRV_newdriver;
inline void DRV_ED_username(int x, int y)
{
	fstream allaccountinformation;
	print(' ', DRV_acceptcolor, x + 1, y + 1);
	print("between 5 and 15", DRV_warningcolor, x + 12, y + 1);
	string u, p;
	while (1)
	{
		int id = 0;
		do
		{
			DRV_newdriver.username = input(5, 15, x + 4, y + 2, x + 12, y + 1, DRV_backcolor, DRV_errorcolor, "bpzEnle");
			if (DRV_newdriver.username == "~b" || DRV_newdriver.username == "~p" || DRV_newdriver.username == "~z") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (DRV_newdriver.username == "~E") exit(0);

		} while (DRV_newdriver.username[0] == '~');
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == DRV_newdriver.username && user.username != DRV_newdriver.username)
			{
				print("This username alredy exist!", DRV_errorcolor, x + 12, y + 1);
				print(' ', DRV_backcolor, x + 4, y + 2, user.username.length());
				print('X', DRV_errorcolor, x + 1, y + 1);
				id = -1;
				break;
			}
		}
		allaccountinformation.close();
		if (id != -1) break;
	}
	print(char(-5), DRV_acceptcolor, x + 1, y + 1);
}
inline void DRV_ED_password(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 3);
	print("between 4 and 15", DRV_warningcolor, x + 12, y + 3);
	do
	{
		DRV_newdriver.password = input(4, 15, x + 4, y + 4, x + 12, y + 3, DRV_backcolor, DRV_errorcolor, "bpzEnlus", 30, true);
		if (DRV_newdriver.password == "~b" || DRV_newdriver.password == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
		else if (DRV_newdriver.password == "~z")
		{
			print(' ', DRV_acceptcolor, x + 12, y + 3, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 3);
			DRV_ED_username(x, y);
			print("between 4 and 15", DRV_warningcolor, x + 12, y + 3);
		}
		else if (DRV_newdriver.password == "~E") exit(0);
	} while (DRV_newdriver.password[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 3);
}
inline void DRV_ED_confirmpassword(int x, int y)
{
	string pass;
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	print("Confirm your password", DRV_warningcolor, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, DRV_backcolor, DRV_errorcolor, "bpzEnlus", 25, true);
			if (pass == "~b" || pass == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (pass == "~z")
			{
				print(' ', DRV_acceptcolor, x + 20, y + 5, 25);
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				DRV_ED_password(x, y);
				print("Confirm your password", DRV_warningcolor, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == DRV_newdriver.password)
		{
			print(char(-5), DRV_acceptcolor, x + 1, y + 5);
			break;
		}
		else
		{
			print("X", DRV_errorcolor, x + 1, y + 5);
			print("Passwords not matched.", DRV_errorcolor, x + 20, y + 5);
			print(' ', DRV_backcolor, x + 4, y + 6, pass.length());
		}
	}
}
inline void DRV_ED_name(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	print("between 3 and 10", DRV_warningcolor, x + 8, y + 7);
	do
	{
		DRV_newdriver.name = input(3, 10, x + 4, y + 8, x + 8, y + 7, DRV_backcolor, DRV_errorcolor, "bpzElu");
		if (DRV_newdriver.name == "~b" || DRV_newdriver.name == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
		else if (DRV_newdriver.name == "~z")
		{
			print(' ', DRV_acceptcolor, x + 8, y + 7, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 7);
			DRV_ED_confirmpassword(x, y);
			print("between 3 and 10", DRV_warningcolor, x + 8, y + 7);
		}
		else if (DRV_newdriver.name == "~E") exit(0);
	} while (DRV_newdriver.name[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}
inline void DRV_ED_family(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 9);
	print("betwen 5 and 20", DRV_warningcolor, x + 10, y + 9);
	do
	{
		DRV_newdriver.family = input(5, 20, x + 4, y + 10, x + 10, y + 9, DRV_backcolor, DRV_errorcolor, "bpzElu");
		if (DRV_newdriver.family == "~b" || DRV_newdriver.family == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
		else if (DRV_newdriver.family == "~z")
		{
			print(' ', DRV_acceptcolor, x + 10, y + 9, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 9);
			DRV_ED_name(x, y);
			print("betwen 5 and 20", DRV_warningcolor, x + 10, y + 9);
		}
		else if (DRV_newdriver.family == "~E") exit(0);
	} while (DRV_newdriver.family[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 9);
}
inline void DRV_ED_phone(int x, int y)
{
	print(' ', DRV_acceptcolor, x + 1, y + 11);
	print("11 digits", DRV_warningcolor, x + 16, y + 11);

	do
	{
		DRV_newdriver.phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, DRV_backcolor, DRV_errorcolor, "bpzEn");
		if (DRV_newdriver.phone == "~b" || DRV_newdriver.phone == "~p") DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
		else if (DRV_newdriver.phone == "~z")
		{
			print(' ', DRV_acceptcolor, x + 16, y + 11, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 11);
			DRV_ED_family(x, y);
			print("11 digits", DRV_warningcolor, x + 16, y + 11);
		}
		else if (DRV_newdriver.phone == "~E") exit(0);
	} while (DRV_newdriver.phone[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 11);
}

void edit_driver(int length, int width)
{
	//===================================== Show ===================================
	background(DRV_backcolor, screen);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("Username: ", DRV_captioncolor, x + 2, y + 1);
	print(user.username, DRV_backcolor, x + 4, y + 2);
	print("Password: ", DRV_captioncolor, x + 2, y + 3);
	print(user.password, DRV_backcolor, x + 4, y + 4);
	print("Confirm password: ", DRV_captioncolor, x + 2, y + 5);
	print(user.password, DRV_backcolor, x + 4, y + 6);
	print("Name: ", DRV_captioncolor, x + 2, y + 7);
	print(user.name, DRV_backcolor, x + 4, y + 8);
	print("Family: ", DRV_captioncolor, x + 2, y + 9);
	print(user.family, DRV_backcolor, x + 4, y + 10);
	print("Phone number: ", DRV_captioncolor, x + 2, y + 11);
	print(user.phone, DRV_backcolor, x + 4, y + 12);
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("E: Edit information", DRV_captioncolor, 7, screen.Y - 2);
	//===================================== Input ==================================
	bool b = 1;
	while (b)
	{
		char ch = _getch();
		switch (ch)
		{
		case 'e':
		case 'E':
			b = 0;
			break;
		case 2:
		case 16:
		case 26:
			DRV_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			b = 0;
			break;
		case 27:
			exit(0);
		}
	}
	cursor(true);
	//================================== Username ==================================
	DRV_ED_username(x, y);
	//================================== Password ==================================
	DRV_ED_password(x, y);
	DRV_ED_confirmpassword(x, y);
	//===================================== Name ===================================
	DRV_ED_name(x, y);
	//==================================== Family ==================================
	DRV_ED_family(x, y);
	//===================================== Phone ==================================
	DRV_ED_phone(x, y);
	//================================ Write in file ===============================
	string search, replace;

	search = int_to_str(user.id) + "\t" + user.username + "\t" + user.password;
	replace = int_to_str(user.id) + "\t" + DRV_newdriver.username + "\t" + DRV_newdriver.password;
	int check1 = edit(search, replace, "All account information.txt"), check2;

	search = int_to_str(user.id) + "\t" + user.name + "\t" + user.family + "\t" + user.phone;
	replace = int_to_str(user.id) + "\t" + DRV_newdriver.name + "\t" + DRV_newdriver.family + "\t" + DRV_newdriver.phone;
	if (check1) check2 = edit(search, replace, "Drivers information.txt");

	cursor(false);
	if (check1 && check2)
	{
		background(160, screen);
		print("Your information changed successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
		user.username = DRV_newdriver.username;
		user.password = DRV_newdriver.password;
		user.name = DRV_newdriver.name;
		user.family = DRV_newdriver.family;
		user.phone = DRV_newdriver.phone;
	}
	else
	{
		background(79, screen);
		print("Unfurtunately an error occured :(", 79, (screen.X - 34) / 2, screen.Y / 2);
	}
	Sleep(3000);
	DRV_showtop(screen.X - 11, screen.Y - 10 + 1);
	pnl_drivers(screen.X - 11, screen.Y - 10);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ show_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int TR_i;
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
		delete(t);
	}
	
	return n;
}
inline travelinfo* travelshow(bool showfiald, int n, travelinfo *first = &t0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);

	if (!t0.num) return &t0;

	travelinfo *currenttravel = first, *last = first;
	int i;
	for (i = first->num; currenttravel != nullptr && i <= n + first->num; currenttravel = currenttravel->next)
	{
		tm*timer = time();
		bool islater = false, istoday = false;
		islater = (timer->tm_year + 1900 < currenttravel->year || (timer->tm_year + 1900 == currenttravel->year && (timer->tm_yday < yday(currenttravel->month, currenttravel->day) - 1 || (timer->tm_yday == yday(currenttravel->month, currenttravel->day) - 1 && (timer->tm_hour < currenttravel->hour || (timer->tm_hour == currenttravel->hour && timer->tm_min <= currenttravel->minute))))));
		istoday = (timer->tm_year + 1900 == currenttravel->year && timer->tm_yday == yday(currenttravel->month, currenttravel->day) - 1);
		int color;
		if (currenttravel->delay == -1) color = DRV_cancelcolor;
		else if (currenttravel->delay > 0) color = DRV_delaycolor;
		else if (islater && istoday) color = DRV_todaycolor;
		else if (islater) color = DRV_latercolor;
		else color = DRV_faildcolor;
		string str = "   " + int_to_str(i) + "\t" + int_to_str(currenttravel->i) + "\t" + int_to_str(currenttravel->f) + "\t" + int_to_str(currenttravel->day, 2) + "/" + int_to_str(currenttravel->month, 2) + "/" + int_to_str(currenttravel->year) + "\t" + int_to_str(currenttravel->hour, 2) + ":" + int_to_str(currenttravel->minute, 2);

		if (!islater)//radshodeh
		{
			if (showfiald)
			{
				print(str, color, 7, 7 + i - first->num);
				i++;
			}
		}
		else
		{
			//if (istoday) print(str, color, 7, 7 + i - first->num);
			/*else*/ print(str, color, 7, 7 + i - first->num);
			i++;
		}
		if (currenttravel->next == NULL || i == n + first->num) last = currenttravel;
	}
	TR_i = i - 1;
	return last->next;
}
void alltravelshow(bool showfiald, int n, travelinfo *first)
{
	print("Your travels:                ", DRV_backcolor, 7, 6);
	while (1)
	{
		travelinfo *k = travelshow(showfiald, screen.Y - 12, first);
		
		print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
		print("E: Edit travel        C: Cancel travel        D: Details of recent travels", DRV_captioncolor, 53, screen.Y - 2);
		if (first->num > 1) print("                     <-: Previous page", DRV_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalltravel) print("->: Next page", DRV_captioncolor, 7, screen.Y - 2);

		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalltravel)
				alltravelshow(showfiald, screen.Y - 12, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				alltravelshow(showfiald, screen.Y - 12, first);
			}
			break;

		case 'e':
		case 'E': edit_travel(60, 8);
			break;

		case 'c':
		case 'C': cancel_travel();
			break;

		case 'd':
		case 'D': detail();
			break;

		case 2:
		case 16:
		case 26:
			pnl_drivers(screen.X - 11, screen.Y - 10);
			break;
		case 27:
			exit(0);
		}
	}
}

inline void arrow(int x, int y, int linenum, int time, int n, int length)
{
	char ch;
	n == length ? ch = '>' : ch = '-';
	int arrowcolor = DRV_arrowcolor;
	if (user.id / 1000000 == 1)
		arrowcolor = USR_arrowcolor;
	for (int i = 0; i < linenum; i++)
	{
		n == 0 ? print(' ', arrowcolor, x + length , y + i) : print(' ', arrowcolor, x + n - 1, y + i);
		print(ch, arrowcolor, x + n, y + i);
	}
	Sleep(time);
}

void pnl_drivers(int length, int width)
{
	print("Your travels:                ", DRV_backcolor, 7, 6);
	//=================================== Control ==================================
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("T: Transaction        I: Edit/Show information        N: New travel        A: All travels", DRV_captioncolor, 7, screen.Y - 2);
	//=================================== Travel ===================================
	travelinfo *l = travelshow(false, screen.Y - 12);
	//==================================== Keys ====================================
	int i = 0, b = 1;

	while (1)
	{
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch)
			{
			case 't':
			case 'T':alltransactions(screen.Y - 12, &r0); b = 0;
				break;

			case 'i':
			case 'I':edit_driver(50, 12); b = 0;
				break;

			case 'n':
			case 'N':new_travel(60, 8); b = 0;
				break;

			case 'a':
			case 'A':
				alltravelshow(true, screen.Y - 12, &t0);
				b = 0;
				break;

			case 27:
				exit(0);
			}
		}
		if (!b) break;
		arrow(19, 7, TR_i, 500, i, 3);
		i++;
		i %= 4;
	}
}







//-------------------------------------------------------------------- pnl_user --------------------------------------------------------------------
inline void USR_showtop(int length, int width)
{
	cursor(false);
	background(USR_backcolor, screen);
	print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
	print(" Hi " + user.name + " " + user.family + "!" + "                Username: " + user.username, USR_captioncolor, 5, 2);
	print("", USR_backcolor);
	border(length, width, screen);
}//cancel/edit/detail
bool isuserintravel(long int id_user, int id_travel)
{
	string l;
	int id;
	ifstream chairs("Chairs.txt");

	while (getline(chairs, l))
	{
		stringstream s;
		s << l;
		s >> id;
		if (id != id_travel) continue;

		while (s >> id)
			if (id == id_user) return true;
	}
	return false;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_user +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
User USR_newuser;
inline void USR_ED_username(int x, int y)
{
	fstream allaccountinformation;
	print(' ', USR_acceptcolor, x + 1, y + 1);
	print("between 5 and 15", USR_warningcolor, x + 12, y + 1);
	string u, p;
	while (1)
	{
		int id = 0;
		do
		{
			USR_newuser.username = input(5, 15, x + 4, y + 2, x + 12, y + 1, USR_backcolor, USR_errorcolor, "bpzEnle");
			if (USR_newuser.username == "~b" || USR_newuser.username == "~p" || USR_newuser.username == "~z") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			else if (USR_newuser.username == "~E") exit(0);

		} while (USR_newuser.username[0] == '~');
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == USR_newuser.username && user.username != USR_newuser.username)
			{
				print("This username alredy exist!", USR_errorcolor, x + 12, y + 1);
				print(' ', USR_backcolor, x + 4, y + 2, user.username.length());
				print('X', USR_errorcolor, x + 1, y + 1);
				id = -1;
				break;
			}
		}
		allaccountinformation.close();
		if (id != -1) break;
	}
	print(char(-5), USR_acceptcolor, x + 1, y + 1);
}
inline void USR_ED_password(int x, int y)
{
	print(' ', USR_acceptcolor, x + 1, y + 3);
	print("between 4 and 15", USR_warningcolor, x + 12, y + 3);
	do
	{
		USR_newuser.password = input(4, 15, x + 4, y + 4, x + 12, y + 3, USR_backcolor, USR_errorcolor, "bpzEnlus", 30, true);
		if (USR_newuser.password == "~b" || USR_newuser.password == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
		else if (USR_newuser.password == "~z")
		{
			print(' ', USR_acceptcolor, x + 12, y + 3, 30);
			print(' ', USR_acceptcolor, x + 1, y + 3);
			USR_ED_username(x, y);
			print("between 4 and 15", USR_warningcolor, x + 12, y + 3);
		}
		else if (USR_newuser.password == "~E") exit(0);
	} while (USR_newuser.password[0] == '~');
	print(char(-5), USR_acceptcolor, x + 1, y + 3);
}
inline void USR_ED_confirmpassword(int x, int y)
{
	string pass;
	print(' ', USR_acceptcolor, x + 1, y + 5);
	print("Confirm your password", USR_warningcolor, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, USR_backcolor, USR_errorcolor, "bpzEnlus", 25, true);
			if (pass == "~b" || pass == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			else if (pass == "~z")
			{
				print(' ', USR_acceptcolor, x + 20, y + 5, 25);
				print(' ', USR_acceptcolor, x + 1, y + 5);
				USR_ED_password(x, y);
				print("Confirm your password", USR_warningcolor, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == USR_newuser.password)
		{
			print(char(-5), USR_acceptcolor, x + 1, y + 5);
			break;
		}
		else
		{
			print("X", USR_errorcolor, x + 1, y + 5);
			print("Passwords not matched.", USR_errorcolor, x + 20, y + 5);
			print(' ', USR_backcolor, x + 4, y + 6, pass.length());
		}
	}
}
inline void USR_ED_name(int x, int y)
{
	print(' ', USR_acceptcolor, x + 1, y + 7);
	print("between 3 and 10", USR_warningcolor, x + 8, y + 7);
	do
	{
		USR_newuser.name = input(3, 10, x + 4, y + 8, x + 8, y + 7, USR_backcolor, USR_errorcolor, "bpzElu");
		if (USR_newuser.name == "~b" || USR_newuser.name == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
		else if (USR_newuser.name == "~z")
		{
			print(' ', USR_acceptcolor, x + 8, y + 7, 30);
			print(' ', USR_acceptcolor, x + 1, y + 7);
			USR_ED_confirmpassword(x, y);
			print("between 3 and 10", USR_warningcolor, x + 8, y + 7);
		}
		else if (USR_newuser.name == "~E") exit(0);
	} while (USR_newuser.name[0] == '~');
	print(char(-5), USR_acceptcolor, x + 1, y + 7);
}
inline void USR_ED_family(int x, int y)
{
	print(' ', USR_acceptcolor, x + 1, y + 9);
	print("betwen 5 and 20", USR_warningcolor, x + 10, y + 9);
	do
	{
		USR_newuser.family = input(5, 20, x + 4, y + 10, x + 10, y + 9, USR_backcolor, USR_errorcolor, "bpzElu");
		if (USR_newuser.family == "~b" || USR_newuser.family == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
		else if (USR_newuser.family == "~z")
		{
			print(' ', USR_acceptcolor, x + 10, y + 9, 30);
			print(' ', USR_acceptcolor, x + 1, y + 9);
			USR_ED_name(x, y);
			print("betwen 5 and 20", USR_warningcolor, x + 10, y + 9);
		}
		else if (USR_newuser.family == "~E") exit(0);
	} while (USR_newuser.family[0] == '~');
	print(char(-5), USR_acceptcolor, x + 1, y + 9);
}
inline void USR_ED_phone(int x, int y)
{
	print(' ', USR_acceptcolor, x + 1, y + 11);
	print("11 digits", USR_warningcolor, x + 16, y + 11);

	do
	{
		USR_newuser.phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, USR_backcolor, USR_errorcolor, "bpzEn");
		if (USR_newuser.phone == "~b" || USR_newuser.phone == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
		else if (USR_newuser.phone == "~z")
		{
			print(' ', USR_acceptcolor, x + 16, y + 11, 30);
			print(' ', USR_acceptcolor, x + 1, y + 11);
			USR_ED_family(x, y);
			print("11 digits", USR_warningcolor, x + 16, y + 11);
		}
		else if (USR_newuser.phone == "~E") exit(0);
	} while (USR_newuser.phone[0] == '~');
	print(char(-5), USR_acceptcolor, x + 1, y + 11);
}

void edit_user(int length, int width)
{
	//===================================== Show ===================================
	background(USR_backcolor, screen);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("Username: ", USR_captioncolor, x + 2, y + 1);
	print(user.username, USR_backcolor, x + 4, y + 2);
	print("Password: ", USR_captioncolor, x + 2, y + 3);
	print(user.password, USR_backcolor, x + 4, y + 4);
	print("Confirm password: ", USR_captioncolor, x + 2, y + 5);
	print(user.password, USR_backcolor, x + 4, y + 6);
	print("Name: ", USR_captioncolor, x + 2, y + 7);
	print(user.name, USR_backcolor, x + 4, y + 8);
	print("Family: ", USR_captioncolor, x + 2, y + 9);
	print(user.family, USR_backcolor, x + 4, y + 10);
	print("Phone number: ", USR_captioncolor, x + 2, y + 11);
	print(user.phone, USR_backcolor, x + 4, y + 12);
	print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("E: Edit information", USR_captioncolor, 7, screen.Y - 2);
	//===================================== Input ==================================
	bool b = 1;
	while (b)
	{
		char ch = _getch();
		switch (ch)
		{
		case 'e':
		case 'E':
			b = 0;
			break;
		case 2:
		case 16:
		case 26:
			USR_showtop(screen.X - 11, screen.Y - 10);
			pnl_user(screen.X - 11, screen.Y - 10);
			b = 0;
			break;
		case 27:
			exit(0);
		}
	}
	cursor(true);
	//================================== Username ==================================
	USR_ED_username(x, y);
	//================================== Password ==================================
	USR_ED_password(x, y);
	USR_ED_confirmpassword(x, y);
	//===================================== Name ===================================
	USR_ED_name(x, y);
	//==================================== Family ==================================
	USR_ED_family(x, y);
	//===================================== Phone ==================================
	USR_ED_phone(x, y);
	//================================ Write in file ===============================
	string search, replace;

	search = int_to_str(user.id) + "\t" + user.username + "\t" + user.password;
	replace = int_to_str(user.id) + "\t" + USR_newuser.username + "\t" + USR_newuser.password;
	int check1 = edit(search, replace, "All account information.txt"), check2;

	search = int_to_str(user.id) + "\t" + user.name + "\t" + user.family + "\t" + user.phone;
	replace = int_to_str(user.id) + "\t" + USR_newuser.name + "\t" + USR_newuser.family + "\t" + USR_newuser.phone;
	if (check1) check2 = edit(search, replace, "Users Information.txt");

	cursor(false);
	if (check1 && check2)
	{
		background(160, screen);
		print("Your information changed successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
		user.username = USR_newuser.username;
		user.password = USR_newuser.password;
		user.name = USR_newuser.name;
		user.family = USR_newuser.family;
		user.phone = USR_newuser.phone;
	}
	else
	{
		background(79, screen);
		print("Unfurtunately an error occured :(", 79, (screen.X - 34) / 2, screen.Y / 2);
	}
	Sleep(3000);
	USR_showtop(screen.X - 11, screen.Y - 10);
	pnl_user(screen.X - 11, screen.Y - 10);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ cancel_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void USR_cancel_travel()
{
	bool islater;
	string l;
	travelinfo *t = &t0;
	tm *timer = time();
	//===================================== Input ===================================
	print("Which travel do you want to cancel?", USR_captioncolor, 7, screen.Y - 3);
	cursor(true);
	do
	{
		do
		{
			l = input(0, 6, 43, screen.Y - 3, 50, screen.Y - 3, USR_backcolor, USR_errorcolor, "bpzEn", 34);
			if (l == "~E") exit(0);
			else if (l == "~z" || l == "~b")
			{
				print(' ', USR_backcolor, 7, screen.Y - 3, 100);
				cursor(false);
				return;
			}
			else if (l == "~p") USR_showtop(screen.X - 11, screen.Y - 10), pnl_drivers(screen.X - 11, screen.Y - 10);
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);

		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);

		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't cancel past travels!", USR_errorcolor, 50, screen.Y - 3);
		else if (t->delay == -1) print("You can't cancel canceled travels!", USR_errorcolor, 50, screen.Y - 3);

	} while (!islater || t->delay == -1);
	cursor(false);
	//==================================== Account ==================================
	int t_price;
	long int k, id_passenger;

	string ll = find_chairs(t->id);
	stringstream passengers;

	passengers << ll;
	passengers >> k >> k;

	t_price = ifmoney(t->i, t->f, t->vehicle);

	//check if there is enough money in admin & driver acc
	int percent = 50;
	islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));

	if (do_transaction(user.account, (percent / (100.0)) * t_price * (-1)) + 1)
	{
		size_t pos = ll.find(int_to_str(user.id));		
		edit(ll, ll.replace(pos, int_to_str(user.id).length(), "0"),"Chairs.txt");
	}
	else
	{
		print("Your account balance is not enough!", USR_errorcolor, 50, screen.Y - 3);
		Sleep(3000);
	}
	print(' ', USR_captioncolor, 7, screen.Y - 3, 84);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ showtravel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int USR_LN_readTravel(long int id)
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
		line >> t->id;
		if (!isuserintravel(id, t->id)) continue;
		line >> t->i >> t->f >> t->day >> t->month >> t->year >> t->hour >> t->minute >> t->vehicle >> t->id_driver >> t->delay;
		t->num = ++n;
		t->next = new travelinfo;
		t->next->previous = t;
		t = t->next;
	}
	if (t->previous != NULL)
	{
		t->previous->next = nullptr;
		delete(t);
	}

	return n;
}
inline travelinfo* USR_travelshow(bool showfiald, int n, travelinfo *first = &t0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', USR_backcolor, 6, i, screen.X - 13);

	if (!t0.num) return &t0;

	travelinfo *currenttravel = first, *last = first;
	int i;
	for (i = first->num; currenttravel != nullptr && i <= n + first->num; currenttravel = currenttravel->next)
	{
		tm*timer = time();
		bool islater = false, istoday = false;
		islater = (timer->tm_year + 1900 < currenttravel->year || (timer->tm_year + 1900 == currenttravel->year && (timer->tm_yday < yday(currenttravel->month, currenttravel->day) - 1 || (timer->tm_yday == yday(currenttravel->month, currenttravel->day) - 1 && (timer->tm_hour < currenttravel->hour || (timer->tm_hour == currenttravel->hour && timer->tm_min <= currenttravel->minute))))));
		istoday = (timer->tm_year + 1900 == currenttravel->year && timer->tm_yday == yday(currenttravel->month, currenttravel->day) - 1);
		int color;
		if (currenttravel->delay == -1) color = USR_cancelcolor;
		else if (currenttravel->delay > 0) color = USR_delaycolor;
		else if (islater && istoday) color = USR_todaycolor;
		else if (islater) color = USR_latercolor;
		else color = USR_faildcolor;
		string str = "   " + int_to_str(i) + "\t" + int_to_str(currenttravel->i) + "\t" + int_to_str(currenttravel->f) + "\t" + int_to_str(currenttravel->day, 2) + "/" + int_to_str(currenttravel->month, 2) + "/" + int_to_str(currenttravel->year) + "\t" + int_to_str(currenttravel->hour, 2) + ":" + int_to_str(currenttravel->minute, 2);

		if (!islater)//radshodeh
		{
			if (showfiald)
			{
				print(str, color, 7, 7 + i - first->num);
				i++;
			}
		}
		else
		{
			print(str, color, 7, 7 + i - first->num);
			i++;
		}
		if (currenttravel->next == NULL || i == n + first->num) last = currenttravel;
	}
	TR_i = i - 1;
	return last->next;
}
void USR_alltravelshow(bool showfiald, int n, travelinfo *first)
{
	print("Your travels:                ", USR_backcolor, 7, 6);
	while (1)
	{
		travelinfo *k = USR_travelshow(showfiald, screen.Y - 12, first);
		print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);

		if (first->num > 1) print("                     <-: Previous page", USR_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalltravel) print("->: Next page", USR_captioncolor, 7, screen.Y - 2);
		print("C: Cancel travel", USR_captioncolor, 53, screen.Y - 2);
		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalltravel)
				alltravelshow(showfiald, screen.Y - 12, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				alltravelshow(showfiald, screen.Y - 12, first);
			}
			break;

		case 'c':
		case 'C': USR_cancel_travel();
			break;

		case 2:
		case 16:
		case 26:
			pnl_user(screen.X - 11, screen.Y - 10);
			break;
		case 27:
			exit(0);
		}
	}
}


void pnl_user(int length, int width)
{
	print("Your travels:                ", USR_backcolor, 7, 6);
	//=================================== Control ==================================
	print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("T: Transaction        I: Edit/Show information        B: Buy travel        A: All travels", USR_captioncolor, 7, screen.Y - 2);
	//=================================== Travel ===================================
	travelinfo *l = USR_travelshow(false, screen.Y - 12);
	//==================================== Keys ====================================
	int i = 0, b = 1;

	while (1)
	{
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch)
			{
			case 't':
			case 'T':alltransactions(screen.Y - 12, &r0); b = 0;
				break;

			case 'i':
			case 'I':edit_user(50, 12); b = 0;
				break;

			case 'n':
			case 'N':new_travel(60, 8); b = 0;
				break;

			case 'a':
			case 'A':
				USR_alltravelshow(true, screen.Y - 12, &t0);
				b = 0;
				break;

			case 27:
				exit(0);
			}
		}
		if (!b) break;
		arrow(19, 7, TR_i, 500, i, 3);
		i++;
		i %= 4;
	}
}







//-------------------------------------------------------------------- sign up ---------------------------------------------------------------------
inline void signupshow(int length, int width)
{
	background(SU_captioncolor, screen);
	cursor(true);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print(" Please Fill the blank to sign up in MAPSH ticket. ", SU_titrcolor, x + 25, y - 1);
	print("Username: ", SU_captioncolor, x + 2, y + 1);
	print("Password: ", SU_captioncolor, x + 2, y + 3);
	print("Confirm Password: ", SU_captioncolor, x + 2, y + 5);
	print("Name: ", SU_captioncolor, x + 2, y + 7);
	print("Family: ", SU_captioncolor, x + 2, y + 9);
	print("Phone Number: ", SU_captioncolor, x + 2, y + 11);
	print("Inviter: ", SU_captioncolor, x + 2, y + 13);
	print("Bank Account Number: ", SU_captioncolor, x + 2, y + 15);
	print("Bank Account Password: ", SU_captioncolor, x + 2, y + 17);
}

inline void SU_username(int x, int y)
{
	ifstream allaccountinformation;
	print(' ', SU_acceptcolor, x + 1, y + 1);
	print("between 5 and 15", SU_warningcolor, x + 12, y + 1);
	print(' ', SU_acceptcolor, x + 1, y + 1);
	while (1)
	{
		do
		{
			user.username = input(5, 15, x + 4, y + 2, x + 12, y + 1, SU_backcolor, SU_errorcolor, "bzEnle");
			if (user.username == "~b" || user.username == "~z") welcome(30);
			else if (user.username == "~E") exit(0);
		} while (user.username[0] == '~');

		int id = 0;
		string u, p;
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == user.username)
			{
				print("This username alredy exist!", SU_errorcolor, x + 12, y + 1);
				print(' ', SU_backcolor, x + 4, y + 2, user.username.length());
				print('X', SU_errorcolor, x + 1, y + 1);
				id = -1;
				break;
			}
		}
		allaccountinformation.close();
		if (id != -1) break;
	}
	print(char(-5), SU_acceptcolor, x + 1, y + 1);
}
inline void SU_password(int x, int y)
{
	print(' ', SU_acceptcolor, x + 1, y + 3);
	print("between 4 and 15", SU_warningcolor, x + 12, y + 3);
	do
	{
		user.password = input(4, 15, x + 4, y + 4, x + 12, y + 3, SU_backcolor, SU_errorcolor, "bzEnlus", 30, true);
		if (user.password == "~b") welcome(30);
		else if (user.password == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 3);
			print(' ', SU_backcolor, x + 12, y + 3, 30);
			SU_username(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 3);
			print("between 4 and 15", SU_warningcolor, x + 12, y + 3);
		}
		else if (user.password == "~E") exit(0);
	} while (user.password[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 3);
}
inline void SU_confirmpassword(int x, int y)
{
	string pass;
	print(' ', SU_acceptcolor, x + 1, y + 5);
	print("Confirm your password", SU_warningcolor, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, SU_backcolor, SU_errorcolor, "bzEnlus", 30, true);
			if (pass == "~b") welcome(30);
			else if (pass == "~z") 
			{
				print(' ', SU_acceptcolor, x + 1, y + 5);
				print(' ', SU_backcolor, x + 20, y + 5, 30);
				SU_password(x, y);
				print(' ', SU_acceptcolor, x + 1, y + 5);
				print("Confirm your password", SU_warningcolor, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == user.password)
		{
			print(char(-5), SU_acceptcolor, x + 1, y + 5);
			break;
		}
		else
		{
			print("X", SU_errorcolor, x + 1, y + 5);
			print("Passwords not matched.", SU_errorcolor, x + 20, y + 5);
			print(' ', SU_backcolor, x + 4, y + 6, pass.length());
		}
	}
}
inline void SU_name(int x, int y)
{
	print(' ', SU_acceptcolor, x + 1, y + 7);
	print("between 3 and 10", SU_warningcolor, x + 8, y + 7);
	do
	{
		user.name = input(3, 10, x + 4, y + 8, x + 8, y + 7, SU_backcolor, SU_errorcolor, "bzElu");
		if (user.name == "~b") welcome(30);
		else if (user.name == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 7);
			print(' ', SU_backcolor, x + 8, y + 7, 30);
			SU_confirmpassword(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 7);
			print("between 3 and 10", SU_warningcolor, x + 8, y + 7);
		}
		else if (user.name == "~E") exit(0);
	} while (user.name[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 7);
}
inline void SU_family(int x, int y)
{
	print(' ', SU_acceptcolor, x + 1, y + 9);
	print("betwen 5 and 20", SU_warningcolor, x + 10, y + 9);
	do
	{
		user.family = input(5, 20, x + 4, y + 10, x + 10, y + 9, SU_backcolor, SU_errorcolor, "bzElu");
		if (user.family == "~b") welcome(30);
		else if (user.family == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 9);
			print(' ', SU_backcolor, x + 10, y + 9, 30);
			SU_name(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 9);
			print("betwen 5 and 20", SU_warningcolor, x + 10, y + 9);
		}
		else if (user.family == "~E") exit(0);
	} while (user.family[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 9);
}
inline void SU_phone(int x, int y)
{
	print(' ', SU_acceptcolor, x + 1, y + 11);
	print("11 digits", SU_warningcolor, x + 16, y + 11);
	do
	{
		user.phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, SU_backcolor, SU_errorcolor, "bzEn");
		if (user.phone == "~b") welcome(30);
		else if (user.phone == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 11);
			print(' ', SU_backcolor, x + 16, y + 11, 30);
			SU_family(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 11);
			print("11 digits", SU_warningcolor, x + 16, y + 11);
		}
		else if (user.phone == "~E") exit(0);
	} while (user.phone[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 11);
}
inline void SU_inviter(int x, int y)
{
	string inviter;
	print(' ', SU_acceptcolor, x + 1, y + 13);
	print("Inviter's Username is Optional and between 5 and 15.", SU_warningcolor, x + 11, y + 13);
	do
	{
		inviter = input(5, 15, x + 4, y + 14, x + 11, y + 13, SU_backcolor, SU_errorcolor, "bzEnle", 60, false, true);
		if (inviter == "~b") welcome(30);
		else if (inviter == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 13);
			print(' ', SU_backcolor, x + 11, y + 13, 60);
			SU_phone(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 13);
			print("Inviter's Username is Optional and between 5 and 15.", SU_warningcolor, x + 11, y + 13);
		}
		else if (inviter == "~E") exit(0);
	} while (inviter[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 13);
}
inline string SU_account(int x, int y)
{
	ifstream acc;
	string line;
	size_t pos;
	print(' ', SU_acceptcolor, x + 1, y + 15);
	print("6 digits", SU_warningcolor, x + 23, y + 15);
	while (1)
	{
		do
		{
			user.account = input(6, 6, x + 4, y + 16, x + 23, y + 15, SU_backcolor, SU_errorcolor, "bzEn");
			if (user.account == "~b") welcome(30);
			else if (user.account == "~z")
			{
				print(' ', SU_acceptcolor, x + 1, y + 15);
				print(' ', SU_backcolor, x + 23, y + 15, 30);
				SU_inviter(x, y);
				print(' ', SU_acceptcolor, x + 1, y + 15);
				print("6 digits", SU_warningcolor, x + 23, y + 15);
			}
			else if (user.account == "~E") exit(0);
		} while (user.account[0] == '~');

		acc.open("accounts.txt", ios::in);
		while (!acc.eof())
		{
			getline(acc, line); // get line from file
			pos = line.find(user.account); // search
			if (pos != string::npos) break; // string::npos is returned if string is not found
		}
		if (pos == string::npos)
		{
			print("wrong bank account number!", SU_errorcolor, x + 23, y + 15);
			print("X", SU_errorcolor, x + 1, y + 15);
			print(' ', SU_backcolor, x + 4, y + 16, 7);
			acc.close();
		}
		else break;
	}
	print(char(-5), SU_acceptcolor, x + 1, y + 15);
	return line;
}
inline void SU_bankpass(int x, int y, string line)
{
	long long int money;
	string pass, u;
	stringstream l;
	l << line;
	l >> u >> pass >> money;

	print(' ', SU_acceptcolor, x + 1, y + 17);
	print("6 digits", SU_warningcolor, x + 25, y + 17);
	while (1)
	{
		do
		{
			user.accpass = input(4, 4, x + 4, y + 18, x + 25, y + 17, SU_backcolor, SU_errorcolor, "bzEn", 50);
			if (user.accpass == "~b") welcome(30);
			else if (user.accpass == "~z")
			{
				print(' ', SU_acceptcolor, x + 1, y + 17);
				print(' ', SU_backcolor, x + 25, y + 17, 30);
				SU_account(x, y);
				print(' ', SU_acceptcolor, x + 1, y + 17);
				print("6 digits", SU_warningcolor, x + 25, y + 17);
			}
			else if (user.accpass == "~E") exit(0);
		} while (user.accpass[0] == '~');

		if (pass == user.accpass)
		{
			print("bank account connected!", SU_acceptcolor, x + 25, y + 17);
			user.money = money;
			Sleep(500);
			break;
		}
		else
		{
			print("your bank account password is incorrect!", SU_errorcolor, x + 25, y + 17);
			print("X", SU_errorcolor, x + 1, y + 17);
			print(' ', SU_backcolor, x + 4, y + 18, 4);
		}
	}
	print(char(-5), SU_acceptcolor, x + 1, y + 17);
}

void signup(int length, int width)
{
	signupshow(length, width);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	//==================================== Input ===================================
	SU_username(x, y);
	SU_password(x, y);
	SU_confirmpassword(x, y);
	SU_name(x, y);
	SU_family(x, y);
	SU_phone(x, y);
	SU_inviter(x, y);
	string line = SU_account(x, y);	
	SU_bankpass(x, y, line);
	//================================ write in file ===============================
	fstream usersinformation, allaccountinformation;
	usersinformation.open("Users information.txt", ios::app);
	allaccountinformation.open("All account information.txt", ios::app);

	allaccountinformation << '\n' << "1" + user.account << "\t" << user.username << "\t" << user.password;
	usersinformation << '\n' << "1" + user.account << "\t" << user.name << "\t" << user.family << "\t" << user.phone;

	allaccountinformation.close();
	usersinformation.close();

	background(160, screen);
	gotoxy(screen.X / 2 - 11, screen.Y / 2);
	cout << "Welcome to your panel";
	Sleep(1000);
}
//--------------------------------------------------------------------- log in ---------------------------------------------------------------------
string u, p;
int recaptcha(string u, string p)
{
	string username, pass;
	ifstream allaccountinformation, usersinformation, driversinformation;
	string l;
	long int id;
	allaccountinformation.open("All account information.txt", ios::in);

	while (allaccountinformation >> id >> username >> pass)
		if (username == u && pass == p)//shora negahban
		{
			user.username = u;
			user.password = p;
			usersinformation.open("Users information.txt", ios::in);
			//==================================== User ====================================
			while (getline(usersinformation, l))
			{
				long int t;
				stringstream line;
				line << l;
				line >> t;
				if (t == id)
				{
					user.id = t;
					user.account = int_to_str(user.id % 1000000);
					line >> user.name >> user.family >> user.phone;
					usersinformation.close();
					allaccountinformation.close();
					return 1;
				}
			}
			//=================================== Driver ===================================
			driversinformation.open("Drivers information.txt", ios::in);
			while (getline(driversinformation, l))
			{
				long int t;
				stringstream line;
				line << l;
				line >> t;
				if (t == id)
				{
					user.id = t;
					user.account = int_to_str(user.id % 1000000);
					line >> user.name >> user.family >> user.phone >> user.vehicle;
					driversinformation.close();
					allaccountinformation.close();
					return 2;
				}
			}
		}
	allaccountinformation.close();
	return false;
}
inline void LN_username(int length, int width)
{
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	do
	{
		u = input(5, 15, x + 12, y + 2, x + 6, y + 3, LN_backcolor, LN_errorcolor, "bzEnle", 25);
		if (u == "~b" || u == "~z") welcome(1);
		else if (u == "~E") exit(0);
	} while (u[0] == '~');
}
inline void LN_password(int length, int width)
{
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	do
	{
		p = input(4, 15, x + 12, y + 4, x + 6, y + 5, LN_backcolor, LN_errorcolor, "bzEnlus", 25, true);
		if (p == "~b") welcome(1);
		else if (p == "~z")
		{
			print(' ', SU_backcolor, x + 6, y + 5, 25);
			LN_username(length, width);
		}
		else if (p == "~E") exit(0);
	} while (p[0] == '~');
}
void login(int length, int width)
{
	background(LN_backcolor, screen);
	cursor(true);
	border(length, width, screen);
	//================================== User pass ==================================
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;

	print("Username: ", LN_backcolor, x + 2, y + 2);
	print("Password: ", LN_backcolor, x + 2, y + 4);
	
	//vehicles information in struct
	vehicles();

	LN_username(length, width);
	LN_password(length, width);
	//==================================== Check =====================================
	int check = recaptcha(u, p);
	cursor(false);
	if (check)
	{
		background(160, screen);
		print("Hi " + user.name, 160, (screen.X - 2 - user.name.length()) / 2, screen.Y / 2 - 1);
		print("Welcome to your panel", 160, screen.X / 2 - 10, screen.Y / 2);
		Sleep(1000);
		if (check == 1)
		{
			nalltravel = USR_LN_readTravel(user.id);
			nalltransaction = readtransaction(user.account);
			USR_showtop(screen.X - 11, screen.Y - 10);
			pnl_user(screen.X - 11, screen.Y - 10);
		}
		else if (check == 2)
		{
			DRV_showtop(screen.X - 11, screen.Y - 10);

			nalltravel = readTravel(user.id);
			nalltransaction = readtransaction(user.account);
			pnl_drivers(screen.X - 11, screen.Y - 10);
		}
	}
	else
	{
		background(79, screen);
		print("Access Denied", 79, screen.X / 2 - 7, screen.Y / 2);
		Sleep(1000);
		login(37, 5);
	}
}
//-------------------------------------------------------------------- welcome ---------------------------------------------------------------------
void bg()
{
	srand(time(NULL));
	string s;
	for (int i = 0; i < 3000; i++)
	{
		if (rand() % 3 == 1) s = char(rand());
		else s = "MAPSH";
		print(s, WL_backcolor / 16 * 16 + rand() % 16, rand() % screen.X, rand() % screen.Y);
	}
		//print(char(rand() % 222 + 33), WL_backcolor / 16 * 16 + rand() % 16, rand() % screen.X, rand() % screen.Y);
	for (int i = 0; i < 9; i++)
		print(' ', WL_backcolor, screen.X / 2 - 51, screen.Y / 2 - 4 + i, 102);
}
void welcome(int sleeptime)
{
	cursor(false);
	background(WL_backcolor, screen);
	bg();
	//================================== Print first line ==========================
	print(' ', WL_backcolor);
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
	while (true)
	{
		c = _getch();
		if (c == 's' || c == 'S') login(37, 5);
		else if (c == 'u' || c == 'U') signup(100, 18);
		else if (c == 'g' || c == 'G') signup(100, 18);
		else if (c == 27) exit(0);
	}
}
//-------------------------------------------------------------------- loading ---------------------------------------------------------------------
inline void process(int time, int n, int i, COORD screen)
{
	Sleep(time);
	print(char(219), LD_processcolor, (screen.X - n) / 2 + i, screen.Y / 2);
	Sleep(time);
}
void loading(int time, int n, COORD screen)
{
	cursor(false);
	background(LD_backcolor, screen);
	print(" Loading\n", LD_backcolor, screen.X / 2 - 4, screen.Y / 2 - 2);
	border(n + 2, 1, screen);
	for (int i = 0; i < n;)
	{
		process(time, n, i, screen);
		i++;
		if (i > n) break;
		process(time, n, i, screen);
		i++;
		if (i > n) break;
		print("|", LD_backcolor, screen.X / 2 - 5, screen.Y / 2 - 2);

		process(time, n, i, screen);
		i++;
		if (i > n) break;
		process(time, n, i, screen);
		i++;
		if (i > n) break;
		print("/", LD_backcolor, screen.X / 2 - 5, screen.Y / 2 - 2);

		process(time, n, i, screen);
		i++;
		if (i > n) break;
		process(time, n, i, screen);
		i++;
		if (i > n) break;
		print(char(-60), LD_backcolor, screen.X / 2 - 5, screen.Y / 2 - 2);

		process(time, n, i, screen);
		i++;
		if (i > n) break;
		process(time, n, i, screen);
		i++;
		if (i > n) break;
		print("\\", LD_backcolor, screen.X / 2 - 5, screen.Y / 2 - 2);
	}
	Sleep(200);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	fullscreen();
	screen = screensize();
	//loading(50, 50, screen);
	welcome(1);
	/*for (int i = 0; i < 299; i++)
	{
		//print(i, i); print("	fghfgfsghfhfhfa\n", i);
		printf("%d : %c\n", i, i);
	}*/
	gotoxy(0, screen.Y);
}
