#pragma once

#ifndef _DEFINITION_H_
#define _DEFINITION_H_

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
//*********************************
tm* time();

inline void DRV_showtop(int length, int width);

int readtransaction(string acc);
void alltransactions(int n, transactioninfo *first);

int passenger(string chairs);
void allpassengershow(int n, int nalldetail, passengerinfo* first);
void detail();

void edit_travel(int length, int width);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ cancel_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void cancel_travel();
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ new_travel +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void new_travel(int length, int width);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ edit_driver ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void edit_driver(int length, int width);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ show_travel ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int readTravel(long int id);
void alltravelshow(bool showfiald, int n, travelinfo *first);

void pnl_drivers(int length, int width);

void welcome(int sleeptime);
void signup(int length, int width);
void pnl_user(int length, int width);
void buy(int length, int width,bool isguest);
void USR_chairs(int x0, int y0, travelinfo* t);
travelinfo* choose_buy();
//*********************************


/*
void fullscreen();
COORD screensize();

void cursor(bool mode);
void cursor(bool mode, int size);

void gotoxy(int x, int y);

template <typename T>
void print(T s, int color);
template <typename T>
void print(T s, int color, int x, int y);
void print(char s, int color, int xi, int y, int dx);

void background(int color, COORD screen);

void border(int length, int width, COORD screen);





inline string int_to_str(long int a);
inline string int_to_str(long int a, unsigned int size);

inline int yday(int month, int day);

//mode: n:num | l:lower case | u:upper case |s | e
string input(unsigned int min, int max, int x, int y, int xerr, int yerr, int color, int errorcolor, string mode, int maxerrlength = 30, bool ispass = false, bool isoptional = false);

string c(string l, char key);
string code(string l, string key);

int edit(string search, string replace, string fileaddress);

void freeln(passengerinfo* p);
void freeln(travelinfo* t);

//------------------------------------------------------------------ ticketprice -------------------------------------------------------------------
double distance(int i, int f);

//1000 toman
int ifmoney(int i, int f, string vehicle);
//1000 toman
//RETURN	-1: less money | 0: dont find account | 1:OK
//CODE		 1:user | 2:driver | 3:admin | 4:guest || -:cancel
int do_transaction(string acc, double dmoney, int id_travel, int code);

string find_chairs(long int id);

long int* costed_money(int id_travel, long int id_user = -1);

bool isfull(int column, string chair);


void arrow(int x, int y, int linenum, int time, int n, int length);*/
#endif // !_DEFINITION_H_
