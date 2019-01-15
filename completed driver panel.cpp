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
//*********************************



int nalltransaction;



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
void alltravelshow(bool showfiald, int n, int nalltravel, travelinfo *first);
void welcome(int sleeptime);
void signup(int length, int width);
void pnl_drivers(int length, int width, int nalltravel);
void DRV_showtop(int length, int width);
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

//-------------------------------------------------------------------- pnl_user --------------------------------------------------------------------
void pnl_user(int length, int width, int backcolor, int headercolor)
{
	background(backcolor, screen);
	border(length, width, screen);
	/*print(' ', headercolor, 0, 0, screen.X - 1);
	print(person.name + '\t' + person.family, headercolor, 0, 0);*/
}
//------------------------------------------------------------------- pnl_driver -------------------------------------------------------------------
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
	r->previous->next = NULL;
	delete(r);
	return i;
}
inline transactioninfo* transactionshow(int n, transactioninfo *first = &r0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);
	transactioninfo *currenttransaction = first, *last;

	for (int i = first->num; currenttransaction != nullptr && i <= n + first->num; currenttransaction = currenttransaction->next, i++)
	{
		if (currenttransaction->money<0)
			print("   " + int_to_str(currenttransaction->num) + "\t" + int_to_str(currenttransaction->money) + "\t\t" + currenttransaction->date, DRV_inmoneycolor, 7, 7 + i - first->num);
		else 
			print("   " + int_to_str(currenttransaction->num) + "\t " + int_to_str(currenttransaction->money) + "\t\t" + currenttransaction->date, DRV_demoneycolor, 7, 7 + i - first->num);
		if (currenttransaction->next == NULL || i == n + first->num) last = currenttransaction;
	}
	return last;
}
void alltransactions(int n,/* int nalltransaction,*/ int nalltravel, transactioninfo *first)
{
	print("Your transactions:           ", DRV_backcolor, 7, 6);
	while (1)
	{
		transactioninfo *k = transactionshow(n, first);
		print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);

		if (first->num > 1) print("                     <-: Previous page", DRV_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalltransaction) print("->: Next page", DRV_captioncolor, 7, screen.Y - 2);
		//print("E: Edit travel        C: Cancel travel        D: Details of recent travels", DRV_captioncolor, 53, screen.Y - 2);
		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalltravel)
				alltransactions(n, nalltravel, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				alltransactions(n, nalltravel, first);
			}
			break;

		case 2:
		case 26:
			alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			break;
		case 16:
			pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			break;
		case 27:
			exit(0);
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ show_detail +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline travelinfo* DRV_TD_id(int nalltravel)
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
			alltravelshow(true, screen.Y - 12, nalltravel, &t0);
		}
		else if (l == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
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
		}
		p->next = new passengerinfo;
		p->next->previous = p;
		p = p->next;
	}
	p->previous->next = NULL;
	delete(p);
	return n;
}
inline passengerinfo* passengershow(int n, passengerinfo* first = &p0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);
	passengerinfo *currentpassenger = first, *last;

	for (int i = first->num; currentpassenger != nullptr && i <= n + first->num; currentpassenger = currentpassenger->next, i++)
	{
		print("   " + int_to_str(currentpassenger->num) + "\t" + currentpassenger->name + " " + currentpassenger->family, DRV_backcolor, 7, 7 + i - first->num);
		print(currentpassenger->phone, DRV_backcolor, 50, 7 + i - first->num);
		if (currentpassenger->next == NULL || i == n + first->num) last = currentpassenger;
	}
	return last;
}
void allpassengershow(int n, int nalldetail, passengerinfo* first, int nalltravel)
{
	print("Passengers :                 ", DRV_backcolor, 7, 6);
	while (1)
	{
		passengerinfo *k = passengershow(screen.Y - 12, first);
		print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);

		if (first->num > 1) print("                     <-: Previous page", DRV_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalldetail) print("->: Next page", DRV_captioncolor, 7, screen.Y - 2);
		//print("E: Edit travel        C: Cancel travel        D: Details of recent travels", DRV_captioncolor, 53, screen.Y - 2);
		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalldetail)
				allpassengershow(screen.Y - 12, nalldetail, k->next, nalltravel);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				allpassengershow(screen.Y - 12, nalldetail, first, nalltravel);
			}
			break;

		case 2:
		case 26:
			alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			break;
		case 16:
			pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			break;
		case 27:
			exit(0);
		}
	}
}
void detail(int nalltravel)
{
	//================================= Find in file ================================
	travelinfo* t = DRV_TD_id(nalltravel);
	string chair = find_chairs(t->id);
	//===================================== Show ====================================
	int nalldetail = passenger(chair);

	DRV_showtop(screen.X - 11, screen.Y - 10);

	allpassengershow(screen.Y - 12, nalldetail, &p0, nalltravel);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_travel +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline travelinfo* DRV_ET_id(int nalltravel)
{
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
			else if (l == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
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
travelinfo DRV_edit;
inline void DRV_showtop(int length, int width)
{
	cursor(false);
	background(DRV_backcolor, screen);
	print(' ', DRV_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
	print(" Hi " + user.name + " " + user.family + "!" + "                Username: " + user.username + "                Vehicle: " + user.vehicle, DRV_captioncolor, 5, 2);
	print("", DRV_backcolor);
	border(length, width, screen);
	print("Your travels: ", DRV_backcolor, 7, 6);
	//=================================== Control ==================================
	print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("T: Transaction        I: Edit/Show information        N: New travel        A: All travels", DRV_captioncolor, 7, screen.Y - 2);
}
inline void DRV_ET_day(int x, int y, int nalltravel)
{
	string day;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (day == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (day == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			else if (day == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), DRV_backcolor, x + 8, y + 5);
				DRV_showtop(screen.X - 11, screen.Y - 10);
				alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');

		if (stoi(day) > 31 || stoi(day) < 1)
		{
			print("Must be between 1 and 31", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (stoi(day) > 31 || stoi(day) < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	DRV_edit.day = stoi(day);
}
inline void DRV_ET_month(int x, int y, int nalltravel)
{
	string month;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (month == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (month == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			else if (month == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mon + 1, 2), DRV_backcolor, x + 11, y + 5);
				DRV_ET_day(x, y, nalltravel);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');

		if (stoi(month) > 12 || stoi(month) < 1)
		{
			print("Must be between 1 and 12", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (stoi(month) > 12 || stoi(month) < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	DRV_edit.month = stoi(month);
}
inline void DRV_ET_year(int x, int y, int nalltravel, travelinfo *t)
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

			if (year == "~b" || year == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (year == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			else if (year == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_year + 1900, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_month(x, y, nalltravel);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');
		DRV_edit.year = stoi(year);

		islater = (t->year < stoi(year) || (t->year == stoi(year) && yday(t->month, t->day) <= yday(DRV_edit.month, DRV_edit.day)));
		if (!islater)
		{
			print("You can't make travel earlier!", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (!islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_ET_hour(int x, int y, int nalltravel, travelinfo *t)
{
	string hour;
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (hour == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (hour == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			else if (hour == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_hour, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_year(x, y, nalltravel, t);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');

		if (stoi(hour) > 23 || stoi(hour) < 0)
		{
			print("Must be between 0 and 23", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (stoi(hour) > 23 || stoi(hour) < 0);
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	DRV_edit.hour = stoi(hour);
}
inline void DRV_ET_minute(int x, int y, int nalltravel, travelinfo *t)
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

			if (minute == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (minute == "~b") DRV_showtop(screen.X - 11, screen.Y - 10), alltravelshow(true, screen.Y - 12, nalltravel, &t0);
			else if (minute == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_min, 2), DRV_backcolor, x + 14, y + 5);
				DRV_ET_hour(x, y, nalltravel, t);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');
		DRV_edit.minute = stoi(minute);

		islater = (t->year < DRV_edit.year || (t->year == DRV_edit.year && (yday(t->month, t->day) < yday(DRV_edit.month, DRV_edit.day) || (yday(t->month, t->day) == yday(DRV_edit.month, DRV_edit.day) && (t->hour < DRV_edit.hour || (t->hour == DRV_edit.hour && t->minute <= DRV_edit.minute))))));
		if (stoi(minute) < 0 || stoi(minute) >= 60)
		{
			print("Must be between 0 and 59", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
		else if (!islater)
		{
			print("You can't make travel earlier!", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (stoi(minute) < 0 || stoi(minute) >= 60 || !islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}

void edit_travel(int length, int width, int nalltravel)
{
	//===================================== Show ===================================
	print("Which travel do you want to edit?", DRV_captioncolor, 7, screen.Y - 3);
	travelinfo *t = DRV_ET_id(nalltravel);
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
	
	DRV_ET_day(x, y, nalltravel);
	DRV_ET_month(x, y, nalltravel);
	DRV_ET_year(x, y, nalltravel, t);
	DRV_ET_hour(x, y, nalltravel, t);
	DRV_ET_minute(x, y, nalltravel, t);

	//============================= Edit file & linked list =========================
	int delayhour = (DRV_edit.year - t->year) * 8760 + (DRV_edit.month - t->month) * 720 + (DRV_edit.day - t->day) * 24 + (DRV_edit.hour - t->hour);
	if (DRV_edit.minute < t->minute) delayhour--;
	double delayprice = (float) ifmoney(t->i, t->f, t->vehicle) * (float) delayhour * 5.0 / 100.0;
	//check if there is enough money in admin & driver acc
	if (do_transaction(user.account, (0.9)* delayprice * (-1)) + 1)
	{
		if (do_transaction("200000", (0.1)* delayprice * (-1)) + 1)
		{
			string search = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			t->delay += delayhour;
			//if (DRV_edit.minute < t->minute) t->delay--;
			t->day = DRV_edit.day;
			t->month = DRV_edit.month;
			t->year = DRV_edit.year;
			t->hour = DRV_edit.hour;
			t->minute = DRV_edit.minute;
			string replace = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			edit(search, replace, "Travels.txt");

			//return money to passengers accs
			ifstream accounts("accounts.txt");
			string ll = find_chairs(t->id);
			stringstream passengers;
			passengers << ll;
			long int id_passenger;
			passengers >> id_passenger >> id_passenger;
			while (passengers >> id_passenger)
			{
				stringstream s;
				id_passenger %= 1000000;
				for (int i = 200000; i <= id_passenger && getline(accounts, ll); i++);
				s << ll;
				long int money;
				string accpass;
				s >> accpass >> accpass >> money;
				money += delayprice * 1000;
				edit(ll, int_to_str(id_passenger) + "\t" + accpass + "\t" + int_to_str(money), "accounts.txt");
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, screen.X / 2 - 19, screen.Y / 2 + 4);
			cursor(false);
			Sleep(5000);
			//print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
			do_transaction(user.account, (0.9)*delayprice);
		}
	}
	else
	{
		print("Your account balance is not enough!", DRV_errorcolor, screen.X / 2 - 18, screen.Y / 2 + 4);
		cursor(false);
		Sleep(5000);
		//print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
	}
	DRV_showtop(screen.X - 11, screen.Y - 10);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ cancel_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void cancel_travel(int nalltravel)
{
	bool islater;
	travelinfo *t = &t0;
	tm *timer = time();
	print("Which travel do you want to cancel?", DRV_captioncolor, 7, screen.Y - 3);
	string l;

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
			else if (l == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);
		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);

		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't cancel past travels!", DRV_errorcolor, 50, screen.Y - 3);
		else if (t->delay == -1) print("You can't cancel canceled travels!", DRV_errorcolor, 50, screen.Y - 3);
	} while (!islater || t->delay == -1);

	//check if there is enough money in admin & driver acc
	int t_price = ifmoney(t->i, t->f, t->vehicle);
	if (do_transaction(user.account, (0.9)* t_price * (-1)) + 1)
	{
		if (do_transaction("200000", (0.1)* t_price * (-1)) + 1)
		{
			string s = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t";
			edit(s + int_to_str(t->delay), s + "-1", "Travels.txt");
			t->delay = -1;
			print(' ', DRV_backcolor, 7, screen.Y - 3, 50);
			cursor(false);
			//return money to passengers accs
			ifstream accounts("accounts.txt");
			string ll = find_chairs(t->id);
			stringstream passengers;
			passengers << ll;
			long int id_passenger;
			passengers >> id_passenger >> id_passenger;
			while (passengers >> id_passenger)
			{
				stringstream s;
				id_passenger %= 1000000;
				for (int i = 200000; i <= id_passenger && getline(accounts, ll); i++);
				s << ll;
				long int money;
				string accpass;
				s >> accpass >> accpass >> money;
				money += t_price * 1000;
				edit(ll, int_to_str(id_passenger) + "\t" + accpass + "\t" + int_to_str(money), "accounts.txt");
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, 50, screen.Y - 3);
			cursor(false);
			Sleep(5000);
			print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
			do_transaction(user.account, (0.9)*t_price);
		}
	}
	else
	{
		print("Your account balance is not enough!", DRV_errorcolor, 50, screen.Y - 3);
		cursor(false);
		Sleep(5000);
		print(' ', DRV_captioncolor, 7, screen.Y - 3, 84);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ new_travel +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string i, f, year, month, day, hour, minute;
inline void DRV_NT_i(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 1);
	print("between 1 and 300", DRV_warningcolor, x + 4, y + 2);
	do
	{
		do
		{
			i = input(1, 3, x + 8, y + 1, x + 4, y + 2, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (i == "~E") exit(0);
		} while (i[0] == '~');

		if (stoi(i) > 300 || stoi(i) < 1)
		{
			print("Must be between 1 and 300", DRV_errorcolor, x + 4, y + 2);
			print('X', DRV_errorcolor, x + 1, y + 1);
		}
	} while (stoi(i) > 300 || stoi(i) < 1);
	print(char(-5), DRV_acceptcolor, x + 1, y + 1);
}
inline void DRV_NT_f(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 3);
	print("between 1 and 300", DRV_warningcolor, x + 4, y + 4);
	do
	{
		do
		{
			f = input(1, 3, x + 6, y + 3, x + 4, y + 4, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (f == "~b" || f == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (f == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 3);
				print(' ', DRV_backcolor, x + 4, y + 4, 30);
				DRV_NT_i(x, y, nalltravel);
				print("between 1 and 300", DRV_warningcolor, x + 4, y + 4);
			}
			else if (f == "~E") exit(0);
		} while (f[0] == '~');

		if (stoi(f) > 300 || stoi(f) < 1)
		{
			print("Must be between 1 and 300", DRV_errorcolor, x + 4, y + 4);
			print('X', DRV_errorcolor, x + 1, y + 3);
		}
		else if (f == i)
		{
			print("Invalid city", DRV_errorcolor, x + 4, y + 4);
			print('X', DRV_errorcolor, x + 1, y + 3);
		}
	} while (stoi(f) > 300 || stoi(f) < 1 || f == i);
	print(char(-5), DRV_acceptcolor, x + 1, y + 3);
}
inline void DRV_NT_day(int x, int y, int nalltravel)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (day == "~b" || day == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (day == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), DRV_backcolor, x + 8, y + 5);
				DRV_NT_f(x, y, nalltravel);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');

		if (stoi(day) > 31 || stoi(day) < 1)
		{
			print("Must be between 1 and 31", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (stoi(day) > 31 || stoi(day) < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_month(int x, int y, int nalltravel)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (month == "~b" || month == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (month == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mon + 1, 2), DRV_backcolor, x + 11, y + 5);
				DRV_NT_day(x, y, nalltravel);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');

		if (stoi(month) > 12 || stoi(month) < 1)
		{
			print("Must be between 1 and 12", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (stoi(month) > 12 || stoi(month) < 1);
	print(' ', DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_year(int x, int y, int nalltravel)
{
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	do
	{
		do
		{
			year = input(4, 4, x + 14, y + 5, x + 4, y + 6, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (year == "~b" || year == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (year == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				print(' ', DRV_backcolor, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_year + 1900, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_month(x, y, nalltravel);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');

		islater = (timer->tm_year + 1900 < stoi(year) || (timer->tm_year + 1900 == stoi(year) && timer->tm_yday <= yday(stoi(month), stoi(day)) - 1));
		if (!islater)
		{
			print("Can you traval in time?", DRV_errorcolor, x + 4, y + 6);
			print('X', DRV_errorcolor, x + 1, y + 5);
		}
	} while (!islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 5);
}
inline void DRV_NT_hour(int x, int y, int nalltravel)
{
	tm* timer = time();
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");
			if (hour == "~b" || month == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (hour == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_hour, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_year(x, y, nalltravel);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');

		if (stoi(hour) > 23 || stoi(hour) < 0)
		{
			print("Must be between 0 and 23", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (stoi(hour) > 23 || stoi(hour) < 0);
	print(' ', DRV_acceptcolor, x + 1, y + 7);
}
inline void DRV_NT_minute(int x, int y, int nalltravel)
{
	tm* timer = time();
	bool islater;
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	do
	{
		do
		{
			minute = input(2, 2, x + 11, y + 7, x + 4, y + 8, DRV_backcolor, DRV_errorcolor, "bpzEn");

			if (minute == "~b" || minute == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (minute == "~z")
			{
				print(' ', DRV_acceptcolor, x + 1, y + 7);
				print(' ', DRV_backcolor, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_min, 2), DRV_backcolor, x + 14, y + 5);
				DRV_NT_hour(x, y, nalltravel);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');

		islater = (timer->tm_year + 1900 < stoi(year) || (timer->tm_year + 1900 == stoi(year) && (timer->tm_yday < yday(stoi(month), stoi(day)) - 1 || (timer->tm_yday == yday(stoi(month), stoi(day)) - 1 && (timer->tm_hour < stoi(hour) || (timer->tm_hour == stoi(hour) && timer->tm_min <= stoi(minute)))))));
		if (stoi(minute) < 0 || stoi(minute) >= 60)
		{
			print("Must be between 0 and 59", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
		else if (!islater)
		{
			print("Can you traval in time?", DRV_errorcolor, x + 4, y + 8);
			print('X', DRV_errorcolor, x + 1, y + 7);
		}
	} while (stoi(minute) < 0 || stoi(minute) >= 60 || !islater);
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}
int new_travel(int length, int width, int nalltravel)
{
	//==================================== Show ====================================
	tm* timer = time();
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
	DRV_NT_i(x, y, nalltravel);
	DRV_NT_f(x, y, nalltravel);
	DRV_NT_day(x, y, nalltravel);
	DRV_NT_month(x, y, nalltravel);
	DRV_NT_year(x, y, nalltravel);
	DRV_NT_hour(x, y, nalltravel);
	DRV_NT_minute(x, y, nalltravel);
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
	travel << id_travel << "\t" << i << "\t" << f << "\t" << day << "\t" << month << "\t" << year << "\t" << hour << "\t" << minute << "\t" << user.vehicle << "\t" << user.id << "\t0\n";
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
	t->i = stoi(i);
	t->f = stoi(f);
	t->day = stoi(day);
	t->month = stoi(month);
	t->year = stoi(year);
	t->hour = stoi(hour);
	t->minute = stoi(minute);
	t->vehicle = user.vehicle;
	t->id_driver = user.id;
	t->num = t->previous->num + 1;
	pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel + 1);

	return nalltravel + 1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_driver ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
string new_username, new_password, new_name, new_family, new_phone;
inline void DRV_ED_username(int x, int y, int nalltravel)
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
			new_username = input(5, 15, x + 4, y + 2, x + 12, y + 1, DRV_backcolor, DRV_errorcolor, "bpzEnle");
			if (new_username == "~b" || new_username == "~p" || new_username == "~z") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (new_username == "~E") exit(0);

		} while (new_username[0] == '~');
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == new_username && user.username != new_username)
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
inline void DRV_ED_password(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 3);
	print("between 4 and 15", DRV_warningcolor, x + 12, y + 3);
	do
	{
		new_password = input(4, 15, x + 4, y + 4, x + 12, y + 3, DRV_backcolor, DRV_errorcolor, "bpzEnlus", 30, true);
		if (new_password == "~b" || new_password == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
		else if (new_password == "~z")
		{
			print(' ', DRV_acceptcolor, x + 12, y + 3, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 3);
			DRV_ED_username(x, y, nalltravel);
			print("between 4 and 15", DRV_warningcolor, x + 12, y + 3);
		}
		else if (new_password == "~E") exit(0);
	} while (new_password[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 3);
}
inline void DRV_ED_confirmpassword(int x, int y, int nalltravel)
{
	string pass;
	print(' ', DRV_acceptcolor, x + 1, y + 5);
	print("Confirm your password", DRV_warningcolor, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, DRV_backcolor, DRV_errorcolor, "bpzEnlus", 25, true);
			if (pass == "~b" || pass == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			else if (pass == "~z")
			{
				print(' ', DRV_acceptcolor, x + 20, y + 5, 25);
				print(' ', DRV_acceptcolor, x + 1, y + 5);
				DRV_ED_password(x, y, nalltravel);
				print("Confirm your password", DRV_warningcolor, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == new_password)
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
inline void DRV_ED_name(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 7);
	print("between 3 and 10", DRV_warningcolor, x + 8, y + 7);
	do
	{
		new_name = input(3, 10, x + 4, y + 8, x + 8, y + 7, DRV_backcolor, DRV_errorcolor, "bpzElu");
		if (new_name == "~b" || new_name == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
		else if (new_name == "~z")
		{
			print(' ', DRV_acceptcolor, x + 8, y + 7, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 7);
			DRV_ED_confirmpassword(x, y, nalltravel);
			print("between 3 and 10", DRV_warningcolor, x + 8, y + 7);
		}
		else if (new_name == "~E") exit(0);
	} while (new_name[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 7);
}
inline void DRV_ED_family(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 9);
	print("betwen 5 and 20", DRV_warningcolor, x + 10, y + 9);
	do
	{
		new_family = input(5, 20, x + 4, y + 10, x + 10, y + 9, DRV_backcolor, DRV_errorcolor, "bpzElu");
		if (new_family == "~b" || new_family == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
		else if (new_family == "~z")
		{
			print(' ', DRV_acceptcolor, x + 10, y + 9, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 9);
			DRV_ED_name(x, y, nalltravel);
			print("betwen 5 and 20", DRV_warningcolor, x + 10, y + 9);
		}
		else if (new_family == "~E") exit(0);
	} while (new_family[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 9);
}
inline void DRV_ED_phone(int x, int y, int nalltravel)
{
	print(' ', DRV_acceptcolor, x + 1, y + 11);
	print("11 digits", DRV_warningcolor, x + 16, y + 11);

	do
	{
		new_phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, DRV_backcolor, DRV_errorcolor, "bpzEn");
		if (new_phone == "~b" || new_phone == "~p") pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
		else if (new_phone == "~z")
		{
			print(' ', DRV_acceptcolor, x + 16, y + 11, 30);
			print(' ', DRV_acceptcolor, x + 1, y + 11);
			DRV_ED_family(x, y, nalltravel);
			print("11 digits", DRV_warningcolor, x + 16, y + 11);
		}
		else if (new_phone == "~E") exit(0);
	} while (new_phone[0] == '~');
	print(char(-5), DRV_acceptcolor, x + 1, y + 11);
}

void edit_driver(int length, int width, int nalltravel)
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
		case 26:
		case 16:
			pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
			b = 0;
			break;
		case 27:
			exit(0);
		}
	}
	cursor(true);
	//================================== Username ==================================
	DRV_ED_username(x, y, nalltravel);
	//================================== Password ==================================
	DRV_ED_password(x, y, nalltravel);
	DRV_ED_confirmpassword(x, y, nalltravel);
	//===================================== Name ===================================
	DRV_ED_name(x, y, nalltravel);
	//==================================== Family ==================================
	DRV_ED_family(x, y, nalltravel);
	//===================================== Phone ==================================
	DRV_ED_phone(x, y, nalltravel);
	//================================ Write in file ===============================
	string search, replace;

	search = int_to_str(user.id) + "\t" + user.username + "\t" + user.password;
	replace = int_to_str(user.id) + "\t" + new_username + "\t" + new_password;
	int check1 = edit(search, replace, "All account information.txt"), check2;

	search = int_to_str(user.id) + "\t" + user.name + "\t" + user.family + "\t" + user.phone;
	replace = int_to_str(user.id) + "\t" + new_name + "\t" + new_family + "\t" + new_phone;
	if (check1) check2 = edit(search, replace, "Drivers information.txt");

	cursor(false);
	if (check1 && check2)
	{
		background(160, screen);
		print("Your information changed successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
		user.username = new_username;
		user.password = new_password;
		user.name = new_name;
		user.family = new_family;
		user.phone = new_phone;
	}
	else
	{
		background(79, screen);
		print("Unfurtunately an error occured :(", 79, (screen.X - 34) / 2, screen.Y / 2);
	}
	Sleep(3000);
	pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
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
	t->previous->next = nullptr;
	delete(t);
	return n;
}
inline travelinfo* travelshow(bool showfiald, int n, travelinfo *first = &t0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);

	travelinfo *currenttravel = first, *last;
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
void alltravelshow(bool showfiald, int n, int nalltravel, travelinfo *first)
{
	print("Your travels:                ", DRV_backcolor, 7, 6);
	while (1)
	{
		travelinfo *k = travelshow(showfiald, screen.Y - 12, first);
		print(' ', DRV_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
		
		if (first->num > 1) print("                     <-: Previous page", DRV_captioncolor, 7, screen.Y - 2);
		if (first->num + n < nalltravel) print("->: Next page", DRV_captioncolor, 7, screen.Y - 2);
		print("E: Edit travel        C: Cancel travel        D: Details of recent travels", DRV_captioncolor, 53, screen.Y - 2);
		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nalltravel)
				alltravelshow(showfiald, screen.Y - 12, nalltravel, k->next);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				alltravelshow(showfiald, screen.Y - 12, nalltravel, first);
			}
			break;

		case 'e':
		case 'E': edit_travel(60, 8, nalltravel);
			break;

		case 'c':
		case 'C': cancel_travel(nalltravel);
			break;

		case 'd':
		case 'D': detail(nalltravel);
			break;

		case 2:
		case 16:
		case 26:
			pnl_drivers(screen.X - 11, screen.Y - 10, nalltravel);
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
	for (int i = 0; i < linenum; i++)
	{
		n == 0 ? print(' ', DRV_arrowcolor, x + length , y + i) : print(' ', DRV_arrowcolor, x + n - 1, y + i);
		print(ch, DRV_arrowcolor, x + n, y + i);
	}
	Sleep(time);
}

void pnl_drivers(int length, int width, int nalltravel)
{
	//==================================== Show ====================================
	DRV_showtop(length, width);
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
			case 'T':alltransactions(screen.Y - 12, nalltravel, &r0); b = 0;
				break;

			case 'i':
			case 'I':edit_driver(50, 12, nalltravel); b = 0;
				break;

			case 'n':
			case 'N':nalltravel = new_travel(60, 8, nalltravel); b = 0;
				break;

			case 'a':
			case 'A':
				alltravelshow(true, screen.Y - 12, nalltravel, &t0);
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
			pnl_user(screen.X - 16, screen.Y - 16, 115, 78);
		else if (check == 2)
		{
			nalltransaction = readtransaction(user.account);
			pnl_drivers(screen.X - 11, screen.Y - 10, readTravel(user.id));
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
