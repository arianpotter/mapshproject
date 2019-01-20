#include "F.h"

void DRV_showtop(int, int);//new
void USR_showtop(int, int);//new
void alltravelshow(bool showfiald, int n, travelinfo *first);
void pnl_drivers(int length, int width);
void welcome(int sleeptime);
void signup(int length, int width);
void pnl_user(int length, int width);
void buy(int length, int width, bool isguest);
void USR_chairs(int x0, int y0, travelinfo* t, bool isguest);
travelinfo* choose_buy(bool isguest);

//helps
void main_help()
{
	background(WL_backcolor, screen);
	system("cls");
	border(88, 16, screen);
	print("MAPSH Ticket", WL_backcolor, screen.X / 2 - 6, screen.Y / 2 - 9);
	print("Designers:", WL_backcolor, screen.X / 2 - 5, screen.Y / 2 - 7);
	print("Ali Salemi          Arian Hadi          Mohammad Panahi", WL_backcolor, screen.X / 2 - 28, screen.Y / 2 - 5);
	print("Control keys:", WL_backcolor, screen.X / 2 - 7, screen.Y / 2 - 3);
	print("ESC: Exit", WL_backcolor, screen.X / 2 - 5, screen.Y / 2 - 1);
	print("Ctrl+z: Previous place or work", WL_backcolor, screen.X / 2 - 15, screen.Y / 2 + 1);
	print("Ctrl+b: Previous page", WL_backcolor, screen.X / 2 - 11, screen.Y / 2 + 3);
	print("Ctrl+p: Panel page(Only works in panels)", WL_backcolor, screen.X / 2 - 20, screen.Y / 2 + 5);
	print("H: Help page(In first page of panels)", WL_backcolor, screen.X / 2 - 19, screen.Y / 2 + 7);
	print("Press a key to return", WL_backcolor, screen.X / 2 - 11, screen.Y - 2);
	_getch();
	welcome(1);
}
void DRV_help()
{
	background(DRV_backcolor, screen);
	system("cls");
	border(88, 20, screen);
	print("Travel: Past", DRV_faildcolor, screen.X / 2 - 6, screen.Y / 2 - 9);
	print("Travel: Today", DRV_todaycolor, screen.X / 2 - 7, screen.Y / 2 - 7);
	print("Travel: Normal", DRV_latercolor, screen.X / 2 - 7, screen.Y / 2 - 5);
	print("Travel: Delayed", DRV_faildcolor, screen.X / 2 - 8, screen.Y / 2 - 3);
	print("Travel: Canceled", DRV_cancelcolor, screen.X / 2 - 8, screen.Y / 2 - 1);
	print("Detail page order:", DRV_captioncolor, screen.X / 2 - 9, screen.Y / 2 + 1);
	print("Number        /        Chair number        /        Name        /        Phone number", DRV_captioncolor, screen.X / 2 - 42, screen.Y / 2 + 3);
	print("Transactions order:", DRV_captioncolor, screen.X / 2 - 10, screen.Y / 2 + 5);
	print("+: --> increasing your account balance", DRV_demoneycolor, screen.X / 2 - 19, screen.Y / 2 + 7);
	print("-: --> decreasing your account balance", DRV_inmoneycolor, screen.X / 2 - 19, screen.Y / 2 + 9);
	print("Press a key to exit", DRV_captioncolor, screen.X / 2 - 10, screen.Y - 2);
	cursor(false);
	_getch();
	DRV_showtop(screen.X - 11, screen.Y - 10);//new
	pnl_drivers(screen.X - 11, screen.Y - 10);
}
void USR_help()
{
	background(USR_backcolor, screen);
	system("cls");
	border(40, 16, screen);
	print("Travel: Past", USR_faildcolor, screen.X / 2 - 6, screen.Y / 2 - 7);
	print("Travel: Today", USR_todaycolor, screen.X / 2 - 7, screen.Y / 2 - 5);
	print("Travel: Normal", USR_latercolor, screen.X / 2 - 7, screen.Y / 2 - 3);
	print("Travel: Delayed", USR_faildcolor, screen.X / 2 - 8, screen.Y / 2 - 1);
	print("Travel: Canceled", USR_cancelcolor, screen.X / 2 - 8, screen.Y / 2 + 1);
	print("Transactions order:", USR_captioncolor, screen.X / 2 - 10, screen.Y / 2 + 3);
	print("+: --> increasing your account balance", USR_demoneycolor, screen.X / 2 - 18, screen.Y / 2 + 5);
	print("-: --> decreasing your account balance", USR_inmoneycolor, screen.X / 2 - 18, screen.Y / 2 + 7);
	print("Press a key to exit", USR_captioncolor, screen.X / 2 - 10, screen.Y - 2);
	cursor(false);
	_getch();
	USR_showtop(screen.X - 11, screen.Y - 10);//new
	pnl_user(screen.X - 11, screen.Y - 10);
}
//end of helps

//##################################################################################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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
transactioninfo* transactionshow(int n, transactioninfo *first = &r0)
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

inline passengerinfo* passengershow(int n, passengerinfo* first = &p0)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', DRV_backcolor, 6, i, screen.X - 13);

	if (!p0.num) return &p0;

	passengerinfo *currentpassenger = first, *last = first;

	for (int i = first->num; currentpassenger != nullptr && i <= n + first->num; currentpassenger = currentpassenger->next, i++)
	{
		print("   " + int_to_str(currentpassenger->num) + "\t" + int_to_str(currentpassenger->chair) + "\t" + currentpassenger->name + " " + currentpassenger->family, DRV_backcolor, 7, 7 + i - first->num);
		print(currentpassenger->phone, DRV_backcolor, 57, 7 + i - first->num);
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
			if (p0.num)
				freeln(p0.next);
			p0.num = 0;
			alltravelshow(true, screen.Y - 12, &t0);
			break;
		case 16:
			if (p0.next != NULL) delete[] p0.next;
			p0.num = 0;
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
	long int* p = costed_money(t->id);
	long int a[351];
	for (int i = 0; i < 351; i++)
		a[i] = p[i];

	delayhour = (DRV_edittravel.year - t->year) * 8760 + (DRV_edittravel.month - t->month) * 720 + (DRV_edittravel.day - t->day) * 24 + (DRV_edittravel.hour - t->hour);
	if (DRV_edittravel.minute < t->minute) delayhour--;
	double delayprice = (float)a[350] * (float)delayhour * 5.0 / 100.0;
	//check if there is enough money in admin & driver acc
	tm* timer = time();
	string ll = find_chairs(t->id);
	stringstream passengers, ss;

	passengers << ll;
	ss << ll;

	passengers >> k >> k;
	ss >> k >> k;
	while (ss >> k)
		if (k)
			capacity++;

	if (do_transaction(user.account, (0.9)* a[350] / 1000.0, t->id, 1) == 1)
	{
		LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), (0.9)* a[350] / 1000.0);
		if (do_transaction("200000", (0.1)* a[350] / 1000.0, t->id, 1) == 1)
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
			for (int i = 0; passengers >> id_passenger;)
			{
				if (!id_passenger) continue;
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), (a[i] * (-1) * delayhour * 5.0 / 100.0) / 1000.0, t->id, 1);
				i++;
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, screen.X / 2 - 19, screen.Y / 2 + 4);
			Sleep(3000);
			do_transaction(user.account, (0.9) * a[350] * (-1) / 1000.0, t->id, 1);
			LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), (0.9) * a[350] * (-1) / 1000.0);
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
	long int a[350];
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
	{
		if (k)
			capacity++;
	}

	//check if there is enough money in admin & driver acc
	long int* p = costed_money(t->id);
	long int id_passenger;
	long int tprice = p[350];
	for (int i = 0; i < 350; i++)
		a[i] = p[i];


	if (do_transaction(user.account, (0.9)* tprice / 1000.0, t->id, -1) == 1)
	{
		LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), (0.9)* tprice);
		if (do_transaction("200000", (0.1)* tprice / 1000.0, t->id, -1) == 1)
		{
			string s = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t";
			edit(s + int_to_str(t->delay), s + "-1", "Travels.txt");
			t->delay = -1;
			print(' ', DRV_backcolor, 7, screen.Y - 3, 50);
			//return money to passengers accs
			for (int i = 0; passengers >> id_passenger;)
			{
				if (!id_passenger) continue;
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), a[i] * (-1) / 1000.0, t->id, -1);
				i++;


				//edit code from 1 to -1 in transactions
				string w;
				int code;
				ifstream transaction("Transactions.txt");
				while (getline(transaction, w))
				{
					string date[5], accnum, pri, idt;
					stringstream ww;
					ww << w;
					ww >> accnum >> pri >> date[0] >> date[1] >> date[2] >> date[3] >> date[4] >> idt >> code;
					if (stoi(accnum) == id_passenger && code == 1 && t->id == stoi(idt))
					{
						edit(w, accnum + "\t" + pri + "\t" + date[0] + "\t" + date[1] + "\t" + date[2] + "\t" + date[3] + "\t" + date[4] + "\t" + idt + "\t-1", "Transactions.txt");
						break;
					}
				}
				transaction.close();
			}
		}
		else
		{
			print("Admins account balance is not enough!", DRV_errorcolor, 50, screen.Y - 3);
			Sleep(3000);
			do_transaction(user.account, (0.9) * tprice * (-1) / 1000.0, t->id, 1);
			LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), (-1) * (0.9)* tprice / 1000.0);
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
	fstream chairs("Chairs.txt", ios::app);
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
	LN_addtravel(&t0, id_travel, user.id, DRV_newtravel.i, DRV_newtravel.f, DRV_newtravel.day, DRV_newtravel.month, DRV_newtravel.year, DRV_newtravel.hour, DRV_newtravel.minute, 0, user.vehicle);

	DRV_showtop(screen.X - 11, screen.Y - 10);
	pnl_drivers(screen.X - 11, screen.Y - 10);
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
			case 'h':
			case 'H':DRV_help(), DRV_showtop(length, width);
				break;
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

//##################################################################################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//-------------------------------------------------------------------- pnl_user --------------------------------------------------------------------
inline void USR_showtop(int length, int width)
{
	cursor(false);
	background(USR_backcolor, screen);
	print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
	print(" Hi " + user.name + " " + user.family + "!" + "                Username: " + user.username, USR_captioncolor, 5, 2);
	print("", USR_backcolor);
	border(length, width, screen);
}
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

	//check if there is enough money in admin & driver acc

	long int* p = costed_money(t->id, user.id);
	t_price = *p;
	int percent = 50;
	islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour + 1 < t->hour || (timer->tm_hour + 1 == t->hour && timer->tm_min <= t->minute))))));
	if (islater) percent += 40;

	if (do_transaction(int_to_str(t->id_driver % 1000000), percent * (0.9)* t_price / 100.0 / 1000.0, t->id, -1) + 1)
	{
		if (do_transaction("200000", percent *(0.1)* t_price / 100.0 / 1000.0, t->id, -1) + 1)
		{
			//admin & driver check
			size_t pos = ll.find(int_to_str(user.id));
			string lll = ll;
			edit(ll, lll.replace(pos, int_to_str(user.id).length(), "0"), "Chairs.txt");
			do_transaction(user.account, (percent / (100.0)) * t_price / 1000.0 * (-1), t->id, -1);
			LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), (percent / (100.0)) * t_price * (-1));
			//==================================== Struct ===================================
			/*if (t->previous != NULL) t->previous->next = t->next;
			if (t->next != NULL) t->next->previous = t->previous;
			t->next = t->previous = NULL;*/
			travelinfo* tt = t->next;
			if (t == &t0)
			{
				t0.id = t0.next->id;
				t0.id_driver = t0.next->id_driver;
				t0.i = t0.next->i;
				t0.f = t0.next->f;
				t0.day = t0.next->day;
				t0.month = t0.next->month;
				t0.year = t0.next->year;
				t0.hour = t0.next->hour;
				t0.minute = t0.next->minute;
				t0.delay = t0.next->delay;
				t0.vehicle = t0.next->vehicle;

				tt = t0.next;
				t0.next->next->previous = &t0;
				t0.next = tt->next;
				tt->previous = tt->next = NULL;
				delete tt;
				tt = t0.next;
			}
			else
			{
				if (t->next != NULL) tt = t->next;
				if (t->next != NULL) t->next->previous = t->previous;
				t->previous->next = t->next;
				t->previous = t->next = NULL;
				delete t;
			}
			if (t->next != NULL) for (travelinfo* u = tt; u != NULL; u->num--, u = u->next);
			//edit code from 1 to -1 in transactions
			string w;
			int code;
			ifstream transaction("Transactions.txt");
			while (getline(transaction, w))
			{
				string date[5], accnum, pri, idt;
				stringstream ww;
				ww << w;
				ww >> accnum >> pri >> date[0] >> date[1] >> date[2] >> date[3] >> date[4] >> idt >> code;
				if (stoi(accnum) == user.id % 1000000 && code == 1 && t->id == stoi(idt))
				{
					edit(w, accnum + "\t" + pri + "\t" + date[0] + "\t" + date[1] + "\t" + date[2] + "\t" + date[3] + "\t" + date[4] + "\t" + idt + "\t-1", "Transactions.txt");
					break;
				}
			}
			transaction.close();
		}
		else
		{
			do_transaction(int_to_str(t->id_driver % 1000000), percent * (0.9)* t_price * (-1) / 100.0 / 1000.0, t->id, -1);
			print("You can't cancel this travel now, try later!", USR_errorcolor, 50, screen.Y - 3);
		}
	}
	else
	{
		print("You can't cancel this travel now, try later!", USR_errorcolor, 50, screen.Y - 3);
	}
	Sleep(3000);
	print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
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
inline travelinfo* USR_travelshow(bool showfiald, int n, travelinfo *first = &t0, int nall = nalltravel, bool isbuy = false/*new*/)
{
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', USR_backcolor, 6, i, screen.X - 13);

	if (!first->num) return first;

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
		if (isbuy) str += "\t" + currenttravel->vehicle;//new
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
			if (nall == nalltravel)
			{
				print(str, color, 7, 7 + i - first->num);
				i++;
			}
			else
			{
				if (currenttravel->delay != -1)
				{
					print(str, color, 7, 7 + i - first->num);
					i++;
				}
			}
		}
		if (currenttravel->next == NULL || i == n + first->num) last = currenttravel;
	}
	TR_i = i - 1;
	return last->next;
}
void USR_alltravelshow(bool showfiald, int n, travelinfo *first, bool isbuy = false, bool isguest = false)
{
	int nall = nalltravel;
	if (isbuy) nall = nsearchtravel;
	if (!isbuy) print("Your travels:                ", USR_backcolor, 7, 6);
	else 	print("Found travels:               ", USR_backcolor, 7, 6);

	while (1)
	{
		travelinfo *k = USR_travelshow(showfiald, screen.Y - 12, first, nall, isbuy);
		print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);

		if (first->num > 1) print("                     <-: Previous page", USR_captioncolor, 25, screen.Y - 2);
		if (first->num + n < nall) print("->: Next page", USR_captioncolor, 25, screen.Y - 2);
		if (!isbuy) print("C: Cancel travel", USR_captioncolor, 7, screen.Y - 2);
		else print("C: Choose travel", USR_captioncolor, 7, screen.Y - 2);
		char ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			if (ch == 'M' && first->num + n < nall)
				USR_alltravelshow(showfiald, screen.Y - 12, k->next, nall, isguest);

			if (ch == 'K' && first->num > 1)
			{
				for (int i = 0; i <= n; i++)
					first = first->previous;
				USR_alltravelshow(showfiald, screen.Y - 12, first, nall, isguest);
			}
			break;

		case 'c':
		case 'C':
			if (!isbuy) USR_cancel_travel();
			else
			{
				travelinfo* tt = choose_buy(isguest);
				if (tt != NULL)
					USR_chairs(17, 13, tt, isguest);
			}
			break;
		case 16:
			if (!isguest) pnl_user(screen.X - 11, screen.Y - 10);
			break;
		case 2:
		case 26:
			if (!isbuy) pnl_user(screen.X - 11, screen.Y - 10);
			else buy(60, 8, isguest);//new
			break;
		case 27:
			exit(0);
		}
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ guest info ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
inline void GU_infoshow(int length, int width)
{
	background(SU_captioncolor, screen);
	cursor(true);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print(" Please Fill the blank to complete buy ticket. ", SU_titrcolor, x + 24, y - 1);
	print("Name: ", SU_captioncolor, x + 2, y + 1);
	print("Family: ", SU_captioncolor, x + 2, y + 3);
	print("Phone Number: ", SU_captioncolor, x + 2, y + 5);
	print("Bank Account Number: ", SU_captioncolor, x + 2, y + 7);
	print("Bank Account Password: ", SU_captioncolor, x + 2, y + 9);
}

inline void GU_name(int x, int y, travelinfo* t)
{
	print(' ', SU_acceptcolor, x + 1, y + 1);
	print("between 3 and 10", SU_warningcolor, x + 8, y + 1);
	do
	{
		user.name = input(3, 10, x + 4, y + 2, x + 8, y + 1, SU_backcolor, SU_errorcolor, "bzElu");
		if (user.name == "~b" || user.name == "~z")
		{
			cursor(false);
			background(USR_backcolor, screen);
			print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
			print("", USR_backcolor);
			border(screen.X - 11, screen.Y - 10, screen);
			USR_chairs(17, 13, t, true);
		}
		else if (user.name == "~E") exit(0);
	} while (user.name[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 1);
}
inline void GU_family(int x, int y, travelinfo* t)
{
	print(' ', SU_acceptcolor, x + 1, y + 9);
	print("betwen 4 and 20", SU_warningcolor, x + 10, y + 3);
	do
	{
		user.family = input(4, 20, x + 4, y + 4, x + 10, y + 3, SU_backcolor, SU_errorcolor, "bzElu");
		if (user.family == "~b")
		{
			cursor(false);
			background(USR_backcolor, screen);
			print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
			print("", USR_backcolor);
			border(screen.X - 11, screen.Y - 10, screen);
			USR_chairs(17, 13, t, true);
		}
		else if (user.family == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 3);
			print(' ', SU_backcolor, x + 10, y + 3, 30);
			GU_name(x, y, t);
			print(' ', SU_acceptcolor, x + 1, y + 3);
			print("betwen 4 and 20", SU_warningcolor, x + 10, y + 3);
		}
		else if (user.family == "~E") exit(0);
	} while (user.family[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 3);
}
inline void GU_phone(int x, int y, travelinfo* t)
{
	print(' ', SU_acceptcolor, x + 1, y + 5);
	print("11 digits", SU_warningcolor, x + 16, y + 5);
	do
	{
		user.phone = input(11, 11, x + 4, y + 6, x + 16, y + 5, SU_backcolor, SU_errorcolor, "bzEn");
		if (user.phone == "~b")
		{
			cursor(false);
			background(USR_backcolor, screen);
			print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
			print("", USR_backcolor);
			border(screen.X - 11, screen.Y - 10, screen);
			USR_chairs(17, 13, t, true);
		}
		else if (user.phone == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 5);
			print(' ', SU_backcolor, x + 16, y + 5, 30);
			GU_family(x, y, t);
			print(' ', SU_acceptcolor, x + 1, y + 5);
			print("11 digits", SU_warningcolor, x + 16, y + 5);
		}
		else if (user.phone == "~E") exit(0);
	} while (user.phone[0] == '~');
	print(char(-5), SU_acceptcolor, x + 1, y + 5);
}
inline string GU_account(int x, int y, travelinfo* t)
{
	ifstream acc;
	string line;
	size_t pos;
	print(' ', SU_acceptcolor, x + 1, y + 7);
	print("6 digits", SU_warningcolor, x + 23, y + 7);
	while (1)
	{
		do
		{
			user.account = input(6, 6, x + 4, y + 8, x + 23, y + 7, SU_backcolor, SU_errorcolor, "bzEn");
			if (user.account == "~b")
			{
				cursor(false);
				background(USR_backcolor, screen);
				print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
				print("", USR_backcolor);
				border(screen.X - 11, screen.Y - 10, screen);
				USR_chairs(17, 13, t, true);
			}
			else if (user.account == "~z")
			{
				print(' ', SU_acceptcolor, x + 1, y + 7);
				print(' ', SU_backcolor, x + 23, y + 7, 30);
				GU_phone(x, y, t);
				print(' ', SU_acceptcolor, x + 1, y + 7);
				print("6 digits", SU_warningcolor, x + 23, y + 7);
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
			print("wrong bank account number!", SU_errorcolor, x + 23, y + 7);
			print("X", SU_errorcolor, x + 1, y + 7);
			print(' ', SU_backcolor, x + 4, y + 8, 7);
			acc.close();
		}
		else break;
	}
	print(char(-5), SU_acceptcolor, x + 1, y + 7);
	return line;
}
inline void GU_bankpass(int x, int y, string line, travelinfo* t)
{
	long long int money;
	string pass, u;
	stringstream l;
	l << line;
	l >> u >> pass >> money;

	print(' ', SU_acceptcolor, x + 1, y + 9);
	print("6 digits", SU_warningcolor, x + 25, y + 9);
	while (1)
	{
		do
		{
			user.accpass = input(4, 4, x + 4, y + 10, x + 25, y + 9, SU_backcolor, SU_errorcolor, "bzEn", 50);
			if (user.accpass == "~b")
			{
				cursor(false);
				background(USR_backcolor, screen);
				print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
				print("", USR_backcolor);
				border(screen.X - 11, screen.Y - 10, screen);
				USR_chairs(17, 13, t, true);
			}
			else if (user.accpass == "~z")
			{
				print(' ', SU_acceptcolor, x + 1, y + 9);
				print(' ', SU_backcolor, x + 25, y + 9, 50);
				GU_account(x, y, t);
				print(' ', SU_acceptcolor, x + 1, y + 9);
				print("6 digits", SU_warningcolor, x + 25, y + 9);
			}
			else if (user.accpass == "~E") exit(0);
		} while (user.accpass[0] == '~');

		if (pass == user.accpass)
		{
			print("bank account connected!", SU_acceptcolor, x + 25, y + 9);
			user.money = money;
			Sleep(500);
			break;
		}
		else
		{
			print("your bank account password is incorrect!", SU_errorcolor, x + 25, y + 9);
			print("X", SU_errorcolor, x + 1, y + 9);
			print(' ', SU_backcolor, x + 4, y + 10, 4);
		}
	}
	print(char(-5), SU_acceptcolor, x + 1, y + 9);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ buyticket +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
travelinfo USR_buytravel;

inline void USR_BT_i(int x, int y, bool isguest = false)
{
	print(' ', USR_acceptcolor, x + 1, y + 1);
	print("between 1 and 300", USR_warningcolor, x + 4, y + 2);
	string i;
	do
	{
		do
		{
			if (isguest) i = input(1, 3, x + 8, y + 1, x + 4, y + 2, USR_backcolor, USR_errorcolor, "bzEn");
			else i = input(1, 3, x + 8, y + 1, x + 4, y + 2, USR_backcolor, USR_errorcolor, "bpzEn");

			if (i == "~b" || i == "~p" || i == "~z")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (i == "~E") exit(0);
		} while (i[0] == '~');
		USR_buytravel.i = stoi(i);

		if (USR_buytravel.i > 300 || USR_buytravel.i < 1)
		{
			print("Must be between 1 and 300", USR_errorcolor, x + 4, y + 2);
			print('X', USR_errorcolor, x + 1, y + 1);
		}
	} while (USR_buytravel.i > 300 || USR_buytravel.i < 1);
	print(char(-5), USR_acceptcolor, x + 1, y + 1);
}
inline void USR_BT_f(int x, int y, bool isguest = false)
{
	print(' ', USR_acceptcolor, x + 1, y + 3);
	print("between 1 and 300", USR_warningcolor, x + 4, y + 4);
	string f;
	do
	{
		do
		{
			if (isguest) f = input(1, 3, x + 6, y + 3, x + 4, y + 4, USR_backcolor, USR_errorcolor, "bzEn");
			else f = input(1, 3, x + 6, y + 3, x + 4, y + 4, USR_backcolor, USR_errorcolor, "bpzEn");

			if (f == "~b" || f == "~p")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (f == "~z")
			{
				print(' ', USR_acceptcolor, x + 1, y + 3);
				print(' ', USR_backcolor, x + 4, y + 4, 30);
				USR_BT_i(x, y, isguest);
				print("between 1 and 300", USR_warningcolor, x + 4, y + 4);
			}
			else if (f == "~E") exit(0);
		} while (f[0] == '~');
		USR_buytravel.f = stoi(f);

		if (USR_buytravel.f > 300 || USR_buytravel.f < 1)
		{
			print("Must be between 1 and 300", USR_errorcolor, x + 4, y + 4);
			print('X', USR_errorcolor, x + 1, y + 3);
		}
		else if (USR_buytravel.f == USR_buytravel.i)
		{
			print("Invalid city", USR_errorcolor, x + 4, y + 4);
			print('X', USR_errorcolor, x + 1, y + 3);
		}
	} while (USR_buytravel.f > 300 || USR_buytravel.f < 1 || USR_buytravel.f == USR_buytravel.i);
	print(char(-5), USR_acceptcolor, x + 1, y + 3);
}
inline void USR_BT_v(int x, int y, bool isguest = false)
{
	print(' ', USR_acceptcolor, x + 1, y + 5);
	print("Bus, Train or Airplaine", USR_warningcolor, x + 10, y + 6);

	string v;
	do
	{
		do
		{
			if (isguest) v = input(3, 5, x + 11, y + 5, x + 4, y + 6, USR_backcolor, USR_errorcolor, "bzEul", 30, false, true);
			else v = input(3, 5, x + 11, y + 5, x + 4, y + 6, USR_backcolor, USR_errorcolor, "bpzEul", 30, false, true);

			if (v == "~b" || v == "~p")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (v == "~z")
			{
				print(' ', USR_acceptcolor, x + 1, y + 5);
				print(' ', USR_backcolor, x + 4, y + 6, 30);
				USR_BT_f(x, y, isguest);
			}
			else if (v == "~E") exit(0);
		} while (v[0] == '~');
		if (v == "")
		{
			USR_buytravel.vehicle = "-1";
			return;
		}
		USR_buytravel.vehicle = v;

		if (v != "Bus" && v != "Plane" && v != "Train")
		{
			print("Invalid vehicle", USR_errorcolor, x + 4, y + 6);
			print('X', USR_errorcolor, x + 1, y + 5);
		}
	} while (v != "Bus" && v != "Plane" && v != "Train");

	print(' ', USR_acceptcolor, x + 1, y + 5);
}
inline void USR_BT_day(int x, int y, bool isguest = false)
{
	tm* timer = time();
	print(' ', USR_acceptcolor, x + 1, y + 7);//new
	string day;
	do
	{
		do
		{
			if (isguest) day = input(2, 2, x + 8, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bzEn", 30, false, true);//new
			else day = input(2, 2, x + 8, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bpzEn", 30, false, true);

			if (day == "~b" || day == "~p")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (day == "~z")
			{
				print(' ', USR_acceptcolor, x + 1, y + 7);//new
				print(' ', USR_backcolor, x + 4, y + 8, 30);//new
				print(int_to_str(timer->tm_mday, 2), USR_backcolor, x + 8, y + 7);//new
				USR_BT_v(x, y, isguest);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');
		if (day == "")
		{
			USR_buytravel.day = -1;
			return;
		}
		USR_buytravel.day = stoi(day);

		if (USR_buytravel.day > 31 || USR_buytravel.day < 1)
		{
			print("Must be between 1 and 31", USR_errorcolor, x + 4, y + 8);//new
			print('X', USR_errorcolor, x + 1, y + 7);//new
		}
	} while (USR_buytravel.day > 31 || USR_buytravel.day < 1);
	print(' ', USR_acceptcolor, x + 1, y + 7);//new
}
inline void USR_BT_month(int x, int y, bool isguest = false)
{
	tm* timer = time();
	print(' ', USR_acceptcolor, x + 1, y + 5);
	string month;
	do
	{
		do
		{
			if (isguest) month = input(2, 2, x + 11, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bzEn", 30, false, true);//new
			else month = input(2, 2, x + 11, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bpzEn", 30, false, true);

			if (month == "~b" || month == "~p")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (month == "~z")
			{
				print(' ', USR_acceptcolor, x + 1, y + 7);//new
				print(' ', USR_backcolor, x + 4, y + 8, 30);//new
				print(int_to_str(timer->tm_mon + 1, 2), USR_backcolor, x + 11, y + 7);//new
				USR_BT_day(x, y, isguest);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');
		if (month == "")
		{
			USR_buytravel.month = -1;
			return;
		}
		USR_buytravel.month = stoi(month);

		if (USR_buytravel.month > 12 || USR_buytravel.month < 1)
		{
			print("Must be between 1 and 12", USR_errorcolor, x + 4, y + 8);
			print('X', USR_errorcolor, x + 1, y + 7);
		}
	} while (USR_buytravel.month > 12 || USR_buytravel.month < 1);
	print(' ', USR_acceptcolor, x + 1, y + 7);
}
inline void USR_BT_year(int x, int y, bool isguest = false)
{
	tm* timer = time();
	bool islater;
	print(' ', USR_acceptcolor, x + 1, y + 5);
	string year;
	do
	{
		do
		{
			if (isguest) year = input(4, 4, x + 14, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bzEn", 30, false, true);//new
			else year = input(4, 4, x + 14, y + 7, x + 4, y + 8, USR_backcolor, USR_errorcolor, "bpzEn", 30, false, true);

			if (year == "~b" || year == "~p")
			{
				if (isguest) welcome(30);
				else USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			}
			else if (year == "~z")
			{
				print(' ', USR_acceptcolor, x + 1, y + 7);//new
				print(' ', USR_backcolor, x + 4, y + 8, 30);//new
				print(int_to_str(timer->tm_year + 1900, 4), USR_backcolor, x + 14, y + 7);//new
				USR_BT_month(x, y, isguest);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');
		if (year == "")
		{
			USR_buytravel.year = -1;
			print(char(-5), USR_acceptcolor, x + 1, y + 7);//new
			return;
		}
		USR_buytravel.year = stoi(year);

		islater = USR_buytravel.year > timer->tm_year + 1900 || USR_buytravel.year == -1 || (USR_buytravel.year == timer->tm_year + 1900 && (USR_buytravel.month > timer->tm_mon + 1 || USR_buytravel.month == -1 || (USR_buytravel.month == timer->tm_mon + 1 && (USR_buytravel.day >= timer->tm_mday || USR_buytravel.day == -1))));

		if (!islater)
		{
			print("Can you traval in time?", USR_errorcolor, x + 4, y + 8);//new
			print('X', USR_errorcolor, x + 1, y + 7);//new
		}
	} while (!islater);
	print(char(-5), USR_acceptcolor, x + 1, y + 7);//new
}

void searchTravel()
{

	ifstream travels("Travels.txt");
	travelinfo* t = &t1;
	string l;
	int n = 0;
	getline(travels, l);
	while (getline(travels, l))
	{
		stringstream line;
		line << l;
		line >> t->id >> t->i >> t->f >> t->day >> t->month >> t->year >> t->hour >> t->minute >> t->vehicle >> t->id_driver >> t->delay;

		bool istoday = true;
		if (USR_buytravel.day != -1)
			istoday &= (t->day == USR_buytravel.day);
		if (USR_buytravel.month != -1)
			istoday &= (t->month == USR_buytravel.month);
		if (USR_buytravel.year != -1)
			istoday &= (t->year == USR_buytravel.year);
		if (USR_buytravel.vehicle != "-1")//new
			istoday &= (t->vehicle == USR_buytravel.vehicle);//new
		istoday &= (t->i == USR_buytravel.i);
		istoday &= (t->f == USR_buytravel.f);
		if (!istoday || t->delay == -1) continue;
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

	nsearchtravel = n;
}
travelinfo* choose_buy(bool isguest = false)
{
	string l;
	int n;
	travelinfo *t = &t1;
	print("Which travel do you want to buy?", USR_captioncolor, 7, screen.Y - 3);
	cursor(true);
	do
	{
		do
		{
			l = input(1, 5, 40, screen.Y - 3, 46, screen.Y - 3, USR_backcolor, USR_errorcolor, "bpzEn");
			if (l == "~b" || l == "~z")
			{
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				cursor(false);
				return NULL;
			}
			else if (l == "~p" && !isguest) USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			else if (l == "~E")	exit(0);
		} while (l[0] == '~');
		n = stoi(l);
	} while (n > nsearchtravel || l == "0");
	cursor(false);
	print(' ', USR_captioncolor, 7, screen.Y - 3, 100);

	travelinfo* u = &t0;//new
	for (int i = 1; i < n && t->next != NULL; t = t->next, i++);
	while (u != NULL && t0.num)
	{
		if (u->id == t->id)
		{
			print("You have buyed this travel ago!", USR_errorcolor, 45, screen.Y - 3);
			return choose_buy(isguest);
		}
		u = u->next;
	}

	return t;
}


double USR_CHAIR_off;

inline void USR_CHAIR_letter(int rows, bool isguest = false)
{
	string letter;
	cursor(true);
	print("Which row do you want to select?            ", USR_captioncolor, 7, screen.Y - 3);
	do
	{
		do
		{
			letter = input(1, 1, 40, screen.Y - 3, 42, screen.Y - 3, USR_backcolor, USR_errorcolor, "bpzEu");
			if (letter == "~b" || letter == "~z")
			{
				cursor(false);
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				USR_alltravelshow(false, screen.Y - 12, &t1, true, isguest);
			}
			else if (letter == "~p" && !isguest) USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			else if (letter == "~E") exit(0);
		} while (letter[0] == '~');
	} while (letter[0] - 'A' >= rows);
	cursor(false);

	USR_CHAIR_row = letter[0] - 'A';
}
inline void USR_CHAIR_number(int rows, int columns, string chair, bool isguest = false)
{
	string num;
	bool full;
	cursor(true);
	print("Which column do you want to select?         ", USR_captioncolor, 7, screen.Y - 3);
	do
	{
		do
		{
			num = input(1, 3, 43, screen.Y - 3, 46, screen.Y - 3, USR_backcolor, USR_errorcolor, "bpzEn");
			if (num == "~z")
			{
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				USR_CHAIR_letter(rows, isguest);
				cursor(true);
				print("Which column do you want to select?         ", USR_captioncolor, 7, screen.Y - 3);
			}
			else if (num == "~b")
			{
				cursor(false);
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				USR_alltravelshow(false, screen.Y - 12, &t1, true, isguest);
			}
			else if (num == "~p" && !isguest) USR_showtop(screen.X - 11, screen.Y - 10), pnl_user(screen.X - 11, screen.Y - 10);
			else if (num == "~E") exit(0);
		} while (num[0] == '~');

		USR_CHAIR_column = stoi(num);
		full = isfull(columns, chair);
		if (full)
		{
			cursor(false);
			print("This chair is booked :( please choose another", USR_errorcolor, 46, screen.Y - 3);
			Sleep(4000);
			print(' ', USR_captioncolor, 46, screen.Y - 3, 50);
			cursor(true);
			continue;
		}
	} while (stoi(num) > columns || full);
	cursor(false);

	print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
}
double discount_check(string l, bool isguest = false)
{
	double off;
	int n;
	string ll;
	ifstream discount("Discounts.txt");
	while (getline(discount, ll))
	{
		string k;
		stringstream x;
		x << ll;
		x >> k;
		if (k == l)
		{
			x >> off;
			off /= 100.0;
			discount.close();
			return off;
		}
		if (!isguest && k[0] >= '0' && k[0] <= '9' && l == "" && k == int_to_str(user.id))
		{
			x >> n >> off;
			if (off > 0 && off <= 100)
			{
				edit(l + "\t" + int_to_str(n) + "\t" + int_to_str(off), l + "\t" + int_to_str(n), "Discounts.txt");
				return off / 100.0;
			}
		}
	}
	discount.close();
	if (!isguest) return 0.1;
	return 0;
}
inline void USR_CHAIR_discount(int rows, int columns, string chair, bool isguest = false)
{
	cursor(true);
	print("If do you have any discount code enter it here: ", USR_captioncolor, 7, screen.Y - 3);
	string disc;
	do
	{
		do
		{
			disc = input(7, 7, 56, screen.Y - 3, 65, screen.Y - 3, USR_backcolor, USR_errorcolor, "bpzEu", 30, false, true);
			if (disc == "~b")
			{
				cursor(false);
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				USR_alltravelshow(false, screen.Y - 12, &t1, true, isguest);
			}
			if (disc == "~p" && !isguest)
			{
				cursor(false);
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				pnl_user(screen.X - 11, screen.Y - 10);
			}
			if (disc == "~z")
			{
				cursor(false);
				print(' ', USR_captioncolor, 7, screen.Y - 3, 100);
				USR_CHAIR_number(rows, columns, chair, isguest);
				cursor(true);
				print("If do you have any discount code enter it here: ", USR_captioncolor, 7, screen.Y - 3);
			}
			else if (disc == "~E") exit(0);
		} while (disc[0] == '~');
		USR_CHAIR_off = discount_check(disc, isguest);
		if (disc != "" && ((USR_CHAIR_off == 0 && isguest) || (USR_CHAIR_off == 0.1 && !isguest)))
			print("Invalid code", USR_errorcolor, 65, screen.Y - 3);

	} while (disc != "" && ((USR_CHAIR_off == 0 && isguest) || (USR_CHAIR_off == 0.1 && !isguest)));
	cursor(false);
	//if (disc == "") disc = int_to_str(user.id);
}


//vahhicle: Bus | Train | Plane
void USR_chairs(int x0, int y0, travelinfo* t, bool isguest = false)
{
	print(' ', USR_backcolor, 6, screen.Y - 2, 100);
	for (int i = 7; i < screen.Y - 4; i++)
		print(' ', USR_backcolor, 6, i, screen.X - 13);

	print("Chairs of travel:            ", USR_backcolor, 7, 6);

	int capacity, row, column, id;
	string l = find_chairs(t->id);
	stringstream s;
	string ll, lll;

	s << l;
	s >> capacity >> capacity;
	int speed;
	if (t->vehicle == "Bus")
		row = 4, speed = bus.velocity;
	else if (t->vehicle == "Train")
		row = 4, speed = train.velocity;
	else if (t->vehicle == "Plane")
		row = 8, speed = airplane.velocity;
	column = capacity / row;

	//=================================== Boarder ==================================
	//┌────────────────────┐
	print(char(218), USR_backcolor, x0 - 8, y0 - 2);
	print(char(196), USR_backcolor, x0 - 7, y0 - 2, column * 4 + 3);
	print(char(191), USR_backcolor, x0 + column * 4 - 3, y0 - 2);
	//|						|
	for (int i = -1; i < 2 * row; i++)
	{
		print(char(179), USR_backcolor, x0 - 8, y0 + i);
		print(char(179), USR_backcolor, x0 + column * 4 - 3, y0 + i);
	}
	//└────────────────────┘
	print(char(192), USR_backcolor, x0 - 8, y0 + row * 2);
	print(char(196), USR_backcolor, x0 - 7, y0 + row * 2, column * 4 + 3);
	print(char(217), USR_backcolor, x0 + column * 4 - 3, y0 + row * 2);
	//==================================== chair ===================================
	//top num
	for (int j = 0; j < column; j++)
		print(j + 1, USR_fullchaircolor, x0 + 4 * j, y0 - 3);

	for (int i = 0, k = 0; i < row; i++)
	{
		if (i == 0 || i == 1) k = -1;
		else if (i == row - 1 || i == row - 2) k = +1;
		else k = 0;

		//left letter
		char ch = i + 'A';
		print(ch, USR_fullchaircolor, x0 - 10, y0 + 2 * i + k);
		//chair
		for (int j = 0; j < column; j++)
		{
			s >> id;
			if (id) print("]", USR_fullchaircolor, x0 + 4 * j, y0 + 2 * i + k);
			else print("]", USR_emptychaircolor, x0 + 4 * j, y0 + 2 * i + k);
		}
	}

	//============================== details & discounts ===========================
	double t_time = distance(t->i, t->f) / speed;
	if ((int)(t_time * 10) % 10 > 5) t_time = (int)t_time + 1;
	if ((int)(t_time * 10) % 10 < 5) t_time = (int)t_time;
	if ((int)(t_time * 10) % 10 == 5) t_time = (int)t_time + 0.5;
	if (!t_time) t_time = 0.5;
	int t_minute = 0;
	if (t_time * 10 != ((int)t_time) * 10) t_minute = 30;

	long int x = ifmoney(t->i, t->f, t->vehicle);
	print("From: " + int_to_str(t->i) + "          To: " + int_to_str(t->f) + "          Date: " + int_to_str(t->day, 2) + "/" + int_to_str(t->month, 2) + "/" + int_to_str(t->year) + "          Time: " + int_to_str(t->hour, 2) + ":" + int_to_str(t->minute, 2) + "          The vehicle: " + t->vehicle + "          Estimated time: " + int_to_str((int)t_time, 2) + ":" + int_to_str(t_minute, 2) + "          Price: " + int_to_str(x * 1000) + " TOMAN", USR_backcolor, 9, 8);
	//==================================== input ===================================
	USR_CHAIR_letter(row, isguest);
	USR_CHAIR_number(row, column, l, isguest);
	int chairnum = USR_CHAIR_row*column + USR_CHAIR_column;

	USR_CHAIR_discount(row, column, l, isguest);
	//=============================== guest information ============================
	if (isguest)
	{
		int x = screen.X / 2 - 50, y = screen.Y / 2 - 5;
		GU_infoshow(100, 10);

		GU_name(x, y, t);
		GU_family(x, y, t);
		GU_phone(x, y, t);
		string line = GU_account(x, y, t);
		GU_bankpass(x, y, line, t);
	}
	cursor(false);
	//================================= do transaction =============================
	double price = x * (1 - USR_CHAIR_off);
	if (do_transaction(user.account, price * (-1), t->id, 1) == 1)
	{
		do_transaction(int_to_str(t->id_driver % 1000000), price * (0.9), t->id, 1);
		do_transaction("200000", price * (0.1), t->id, 1);
		//================================ write in file 2 =============================
		if (isguest)
		{
			ifstream guest("Guests.txt");
			int n;
			guest >> n;
			n++;
			user.id = n * 1000000 + stoi(user.account);
			guest.close();

			edit(int_to_str(n - 1), int_to_str(n), "Guests.txt");

			fstream oguest("Guests.txt", ios::app);
			oguest << user.id << "\t" << user.name << "\t" << user.family << "\t" << user.phone << "\t" << user.account << "\t" << t->id << "\n";
			oguest.close();
		}
		else
		{
			int n, m;
			ifstream discount("Discounts.txt");
			while (getline(discount, l))
			{
				stringstream s;
				s << l;
				s >> ll >> n;
				if (ll == int_to_str(user.id)) break;
			}
			discount.close();
			m = n++;
			if (m == 2)
			{
				edit(l, l + "\t40", "Discounts.txt");
				n = 0;
			}
			edit(ll + "\t" + int_to_str(m), ll + "\t" + int_to_str(n), "Discounts.txt");

			//============================== add to linked list ============================
			tm* timer = time();
			
			LN_addtravel(&t0, t->id, t->id_driver, t->i, t->f, t->day, t->month, t->year, t->hour, t->minute, t->delay, t->vehicle);
			LN_addtransaction(user.account, int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900) + "\t" + int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), price * (0.9));
		}
		//================================= write in file ==============================
		stringstream ss;
		l = find_chairs(t->id);
		ss << l;
		lll = "";
		for (int i = -1; i < chairnum && ss >> ll; lll += ll + "\t", i++);
		edit(lll + "0", lll + int_to_str(user.id), "Chairs.txt");

		background(160, screen);
		print("We wish you a happy travel :)", 160, screen.X / 2 - 15, screen.Y / 2);
		print("Tracking code: ", 164, screen.X / 2 - 17, screen.Y / 2 + 4);
		cout << t->vehicle[0] << int_to_str(t->month, 2) << "/" << int_to_str(chairnum, 3) << "h" << int_to_str(t->year, 2) << "8" << int_to_str(t->id, 4) << "J" << int_to_str(t->day, 2) << "5";
		if (!isguest) print("Press a key to go to panel", 160, screen.X / 2 - 12, screen.Y - 3);
		if (isguest) print("Press a key to go to Welcome page", 160, screen.X / 2 - 17, screen.Y - 3);
	}
	else
	{
		background(79, screen);
		print("Unfortunately your account balance is not enough to buy this travel D:", 79, screen.X / 2 - 35, screen.Y / 2);
		if (!isguest) print("Press a key to go to panel", 79, screen.X / 2 - 12, screen.Y - 3);
		if (isguest) print("Press a key to go to Welcome page", 79, screen.X / 2 - 17, screen.Y - 3);
	}
	_getch();
	if (isguest) welcome(30);
	//freeln(&t1);
	USR_showtop(screen.X - 11, screen.Y - 10);
	pnl_user(screen.X - 11, screen.Y - 10);
}

void buy(int length, int width, bool isguest)//found
{
	tm* timer = time();
	print("", USR_backcolor);
	system("cls");
	border(length, width, screen);
	cursor(false);
	print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", USR_captioncolor, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("From: ", USR_captioncolor, x + 2, y + 1);
	print("To: ", USR_captioncolor, x + 2, y + 3);
	print("Vehicle: ", USR_captioncolor, x + 2, y + 5);//new
	print("Date: ", USR_captioncolor, x + 2, y + 7);//new
	print(int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900), USR_backcolor, x + 8, y + 7);
	//new
	//===================================== Input ===================================
	cursor(true);
	USR_BT_i(x, y, isguest);
	USR_BT_f(x, y, isguest);
	USR_BT_v(x, y, isguest);//new
	USR_BT_day(x, y, isguest);
	USR_BT_month(x, y, isguest);
	USR_BT_year(x, y, isguest);
	cursor(false);

	searchTravel();
	if (isguest)
	{
		cursor(false);
		background(USR_backcolor, screen);
		print(' ', USR_captioncolor, 5, 2, screen.X - 2 * 5 - 1);
		print("", USR_backcolor);
		border(screen.X - 11, screen.Y - 10, screen);
	}
	else USR_showtop(screen.X - 11, screen.Y - 10);
	print("Found travels:               ", USR_backcolor, 7, 6);
	//=================================== Control ==================================
	print(' ', USR_captioncolor, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("T: Transaction        I: Edit/Show information        B: Buy travel        A: All travels", USR_captioncolor, 7, screen.Y - 2);

	USR_alltravelshow(false, screen.Y - 12, &t1, true, isguest);
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
			case 'h':
			case 'H': USR_help(), USR_showtop(length, width);
				break;
			case 't':
			case 'T':alltransactions(screen.Y - 12, &r0); b = 0;
				break;

			case 'i':
			case 'I':edit_user(50, 12); b = 0;
				break;

			case 'b':
			case 'B':
				buy(60, 8, false);
				USR_showtop(length, width);
				pnl_user(length, width);
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
		TR_i = nalltravel;//new
		arrow(19, 7, TR_i, 500, i, 3);
		i++;
		i %= 4;
	}
}


//##################################################################################################################################################

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//-------------------------------------------------------------------- pnl_admin -------------------------------------------------------------------
void admin_pnl();
struct page
{
	int num;
	struct page *next;
};
struct page* head;
void insert(int index, int value) 
{
	struct page* temp = head;
	for (int i = 1; i<index; i++)
		temp = temp->next;
	
	struct page* newpage;
	newpage = (struct page*)malloc(sizeof(page));
	newpage->num = value;
	newpage->next = temp->next;
	temp->next = newpage;
}
int search_index(int index)
{
	struct page* temp = head;
	for (int i = 1; i<index; i++)
		temp = temp->next;
	
	return temp->num;
}
string date(string sh) 
{
	string temp;
	string t;
	int j = 0;
	for (int i = 0; j<7; i++) 
	{
		if (sh[i] >= '0'&&sh[i] <= '9') 
			temp += sh[i];

		else
		{
			switch (j)
			{
			case 3:
				t += temp;
				t += '/';
				break;

			case 4:
				t += temp;
				t += '/';
				break;

			case 5:
				t += temp;
				t += ' ';
				break;

			case 6:
				t += temp;
				t += ':';
				break;

			}
			j++;
			temp = "";
		}
	}
	return t;
}
double diff(string t) 
{
	//string t="26/12/2018 23:57";
	time_t now;
	time(&now);
	struct tm *dt;
	dt = localtime(&now);
	string temp;
	int j = 0;
	for (int i = 0; i <= t.length(); i++) 
	{
		if (t[i] >= '0'&&t[i] <= '9')
			temp += t[i];

		else
		{
			switch (j) 
			{
			case 0:
				dt->tm_mday = atoi(temp.c_str());
				temp = "";
				j++;
				break;
			
			case 1: 
				dt->tm_mon = atoi(temp.c_str()) - 1;
				temp = "";
				j++;
				break;
			
			case 2: 
				dt->tm_year = atoi(temp.c_str()) - 1900;
				temp = "";
				j++;
				break;
			
			case 3: 
				dt->tm_hour = atoi(temp.c_str());
				temp = "";
				j++;
				break;
			
			case 4: 
				dt->tm_min = atoi(temp.c_str());
				temp = "";
				j++;
				break;
			}
		}
	}
	return difftime(now, mktime(dt)) / 3600;
}
int check(string sh)
{
	stringstream sht;
	string temp;
	sht << sh;
	sht >> temp;
	temp = "";
	sht >> temp;
	if (atoll(temp.c_str()) >= 0)return 1;
	else return 0;
}
string ran()
{
	srand(time(0));
	string t;
	for (int i = 0; i<7; i++)
		t += char(rand() % 26 + 65);
	return t;
}
int check2(string t)
{
	string temp;
	stringstream sh;
	sh << t;
	for (int i = 0; i<11; i++)
		sh >> temp;
	if (atoi(temp.c_str()) == -1)return 1;
	else return 0;
}

void admin_travel_pnl(long long int, int);

void admin_transaction(long long int g, int gp)
{
	cursor(false);
	system("cls");
	background(10, screen);
	char ch;
	border(screen.X - 11, screen.Y - 10, screen);
	ifstream travel;
	travel.open("Transactions.txt", ios::in);
	if (g == 0) 
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->";
	}
	else
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->   Previous Page: <-";

	}
	travel.seekg(g);
	int i = 0;
	int j = 0;
	string sh;
	string temp;
	while (8 + i<screen.Y - 4 && getline(travel, sh)) 
	{
		stringstream shtt;
		shtt << sh;
		shtt >> temp;
		if (temp == "200000") 
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<7; i++) 
			{
				if (i == 3 || i == 4)cout << '/';
				if (i == 6)cout << ':';
				sht >> temp;
				if (i != 3 && i != 2 && i != 5)temp += '\t';
				print(temp, 15);
			}

			i = i + 2;
			j++;
		}
		else if (check(sh)) 
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<7; i++) 
			{
				if (i == 3 || i == 4)cout << '/';
				if (i == 6)cout << ':';
				sht >> temp;
				if (i != 3 && i != 2 && i != 5)temp += '\t';
				print(temp, 9);
			}

			i = i + 2;
			j++;
		}
		else 
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<7; i++) 
			{
				if (i == 3 || i == 4)cout << '/';
				if (i == 6)cout << ':';
				sht >> temp;
				if (i != 3 && i != 2 && i != 5)temp += '\t';
				print(temp, 12);
			}

			i = i + 2;
			j++;
		}

	}
	if (sh == ""&&g != 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "                                     ";
		gotoxy(5, screen.Y - 2);
		print("Previous Page: <-", 10);
	}
	while (1)
	{
		ch = getch();
		if (ch == 26)admin_pnl();
		if (ch == -32)
		{
			ch = getch();
			if (ch == 'M'&&sh != "") 
			{
				insert(gp, travel.tellg() - 5);//moshkel
				admin_transaction(search_index(gp + 1), gp + 1);
			}
			if (ch == 'K'&&g != 0)
				admin_transaction(search_index(gp - 1), gp - 1);
		}
		else continue;
	}
}

void admin_discount(long long int g, int gp)
{
	cursor(false);
	system("cls");
	background(10, screen);
	char ch;
	border(screen.X - 11, screen.Y - 10, screen);
	gotoxy(screen.X / 2, screen.Y - 2);
	cout << "Press to make a discount: N";
	gotoxy(screen.X / 2 + 32, screen.Y - 2);
	cout << "Choose a discount by name: C";
	ifstream travel;
	travel.open("Discounts.txt", ios::in);
	if (g == 0) 
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->";
	}
	else 
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->   Previous Page: <-";
	}
	travel.seekg(g);
	int i = 0;
	int j = 0;
	string sh, temp;
	while (8 + i<screen.Y - 4 && getline(travel, sh)) 
	{
		gotoxy(10, screen.Y - 60 + i);
		stringstream sht;
		sht << sh;
		sht >> temp;
		if (temp[0] >= '0'&&temp[0] <= '9')continue;
		print(sh, 9);
		cout << "%";
		i = i + 2;
	}
	if (sh == ""&&gp != 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "                                     ";
		gotoxy(5, screen.Y - 2);
		print("Previous Page: <-", 10);
	}
	while (1) 
	{
		ch = getch();
		if (ch == 26)admin_pnl();
		if (ch == -32) {
			ch = getch();
			if (ch == 'M'&&sh != "") 
			{
				insert(gp, travel.tellg() - 25);//moshkel
				admin_discount(search_index(gp + 1), gp + 1);
			}
			if (ch == 'K'&&g != 0)
				admin_discount(search_index(gp - 1), gp - 1);
		}
		if (ch == 'n')
		{
			gotoxy(screen.X / 2, screen.Y - 2);
			print("                                 ", 10);
			print("Enter a number for amount of discount: ", 10);
			string d2 = input(1, 2, screen.X / 2 + 72, screen.Y - 2, screen.X / 2 - 20, screen.Y - 2, 9, 12, "bzEn");
			if (d2 == "~z")admin_discount(0, 0);
			string d = ran();
			gotoxy(screen.X / 2, screen.Y - 2);
			print("                                            ", 10);
			gotoxy(screen.X / 2, screen.Y - 2);
			cout << "Discount is: " << d << " " << d2 << "%";
			ofstream di;
			di.open("Discounts.txt", ios::app);
			di << d << "\t" << d2 << "\n";
			print("                                                                 ", 10);
			di.close();
			Sleep(2000);
			admin_discount(0, 0);
		}
		if (ch == 'c')
		{
			ifstream disc;
			disc.open("Discounts.txt");
			int id = 0;
			string se, tempse;
			gotoxy(screen.X / 2, screen.Y - 2);
			print("                                                               ", 10);
			gotoxy(screen.X / 2, screen.Y - 2);
			print("Enter the exact code of desire discount to change: ", 10);
			string s = input(7, 7, screen.X / 2 + 51, screen.Y - 2, screen.X / 2 - 20, screen.Y - 2, 9, 12, "bzElu");
			while (getline(disc, se))
			{
				stringstream sett;
				sett << se;
				sett >> tempse;
				if (tempse == s)
				{
					id = 1;
					break;
				}

			}
			disc.close();
			if (id = 0)
			{
				gotoxy(screen.X / 2, screen.Y - 2);
				print("                                                               ", 10);
				gotoxy(screen.X / 2, screen.Y - 2);
				print("This discount doesn't exists!", 12);
				Sleep(1000);
				admin_discount(0, 0);
			}
			if (s == "~z")admin_discount(0, 0);
			gotoxy(screen.X / 2, screen.Y - 2);
			print("                                                                  ", 10);
			gotoxy(screen.X / 2, screen.Y - 2);
			print("Enter the new discount value: ", 10);
			string r = input(1, 2, screen.X / 2 + 30, screen.Y - 2, screen.X / 2 - 20, screen.Y - 2, 9, 12, "bzEn");
			if (r == "~z")admin_discount(0, 0);
			print(' ', 10, screen.X / 2, screen.Y - 2, 50);
			int cd;
			if (r == "0") cd = edit(se + "\n", "", "Discounts.txt");
			else  cd = edit(se, s + "\t" + r, "Discounts.txt");
			if (cd == 1) {
				gotoxy(screen.X / 2, screen.Y - 2);
				cout << "Changed successfully!";
			}
			else 
			{
				gotoxy(screen.X / 2, screen.Y - 2);
				print("Error!", 12);
			}
			Sleep(1000);
			admin_discount(0, 0);
		}
		else continue;
	}
}

inline travelinfo* AD_ET_id()
{
	//===================================== Show ===================================
	print("Which travel do you want to edit?", 10, 7, screen.Y - 3);

	string l;
	travelinfo *t = &t0;
	tm *timer = time();
	bool islater;

	cursor(true);
	do
	{
		do
		{
			l = input(0, 6, 41, screen.Y - 3, 48, screen.Y - 3, 9, 12, "bpzEn");
			if (l == "~E") exit(0);
			else if (l == "~z" || l == "~b")
			{
				print(' ', 10, 7, screen.Y - 3, 100);
				cursor(false);
				return NULL;
			}
			else if (l == "~p")
				admin_pnl();
			
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);

		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);
		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't edit past travels!", 12, 48, screen.Y - 3);
		else if (t->delay == -1) print("You can't edit canceled travels!", 12, 48, screen.Y - 3);

	} while (!islater || t->delay == -1);
	return t;
}
travelinfo AD_edittravel;
inline void AD_ET_day(int x, int y)
{
	string day;
	tm* timer = time();
	print(' ', 10, x + 1, y + 5);
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 5, x + 4, y + 6, 9, 12, "bpzEn");
			if (day == "~p") admin_pnl();
			else if (day == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), 10, x + 8, y + 5);
				admin_travel_pnl(0, 0);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');
		AD_edittravel.day = stoi(day);

		if (AD_edittravel.day > 31 || AD_edittravel.day < 1)
		{
			print("Must be between 1 and 31", 12, x + 4, y + 6);
			print('X', 12, x + 1, y + 5);
		}
	} while (AD_edittravel.day > 31 || AD_edittravel.day < 1);
	print(' ', 10, x + 1, y + 5);
}
inline void AD_ET_month(int x, int y)
{
	string month;
	tm* timer = time();
	print(' ', 10, x + 1, y + 5);
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 5, x + 4, y + 6, 9, 12, "bpzEn");
			if (month == "~p") admin_pnl();
			else if (month == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mon + 1, 2), 10, x + 11, y + 5);
				AD_ET_day(x, y);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');
		AD_edittravel.month = stoi(month);

		if (AD_edittravel.month > 12 || AD_edittravel.month < 1)
		{
			print("Must be between 1 and 12", 12, x + 4, y + 6);
			print('X', 12, x + 1, y + 5);
		}
	} while (AD_edittravel.month > 12 || AD_edittravel.month < 1);
	print(' ', 10, x + 1, y + 5);
}
inline void AD_ET_year(int x, int y, travelinfo *t)
{
	string year;
	tm* timer = time();
	bool islater;
	print(' ', 10, x + 1, y + 5);
	do
	{
		do
		{
			year = input(4, 4, x + 14, y + 5, x + 4, y + 6, 9, 12, "bpzEn");

			if (year == "~b" || year == "~p") admin_pnl();
			else if (year == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_year + 1900, 2), 12, x + 14, y + 5);
				AD_ET_month(x, y);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');
		AD_edittravel.year = stoi(year);

		islater = (t->year < AD_edittravel.year || (t->year == AD_edittravel.year && yday(t->month, t->day) <= yday(AD_edittravel.month, AD_edittravel.day)));
		if (!islater)
		{
			print("You can't make travel earlier!", 12, x + 4, y + 6);
			print('X', 12, x + 1, y + 5);
		}
	} while (!islater);
	print(char(-5), 10, x + 1, y + 5);
}
inline void AD_ET_hour(int x, int y, travelinfo *t)
{
	string hour;
	tm* timer = time();
	print(' ', 10, x + 1, y + 7);
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 7, x + 4, y + 8, 9, 12, "bpzEn");
			if (hour == "~p") admin_pnl();
			else if (hour == "~z")
			{
				print(' ', 10, x + 1, y + 7);
				print(' ', 10, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_hour, 2), 10, x + 14, y + 5);
				AD_ET_year(x, y, t);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');
		AD_edittravel.hour = stoi(hour);

		if (AD_edittravel.hour > 23 || AD_edittravel.hour < 0)
		{
			print("Must be between 0 and 23", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
	} while (AD_edittravel.hour > 23 || AD_edittravel.hour < 0);
	print(' ', 10, x + 1, y + 7);
}
inline void AD_ET_minute(int x, int y, travelinfo *t)
{
	string minute;
	tm* timer = time();
	bool islater;
	print(' ', 10, x + 1, y + 7);
	do
	{
		do
		{
			minute = input(2, 2, x + 11, y + 7, x + 4, y + 8, 9, 12, "bpzEn");

			if (minute == "~p") admin_pnl();
			else if (minute == "~z")
			{
				print(' ', 10, x + 1, y + 7);
				print(' ', 10, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_min, 2), 10, x + 14, y + 5);
				AD_ET_hour(x, y, t);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');
		AD_edittravel.minute = stoi(minute);

		islater = (t->year < AD_edittravel.year || (t->year == AD_edittravel.year && (yday(t->month, t->day) < yday(AD_edittravel.month, AD_edittravel.day) || (yday(t->month, t->day) == yday(AD_edittravel.month, AD_edittravel.day) && (t->hour < AD_edittravel.hour || (t->hour == AD_edittravel.hour && t->minute <= AD_edittravel.minute))))));
		if (AD_edittravel.minute < 0 || AD_edittravel.minute >= 60)
		{
			print("Must be between 0 and 59", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
		else if (!islater)
		{
			print("You can't make travel earlier!", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
	} while (AD_edittravel.minute < 0 || AD_edittravel.minute >= 60 || !islater);
	print(char(-5), 10, x + 1, y + 7);
}

void AD_edit_travel(int length, int width)
{
	travelinfo *t = AD_ET_id();
	if (t == NULL) return;

	system("cls");
	border(length, width, screen);
	cursor(false);
	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", 10, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("From: ", 10, x + 2, y + 1);
	print(t->i, 10, x + 8, y + 1);
	print("To: ", 10, x + 2, y + 3);
	print(t->f, 10, x + 6, y + 3);
	print("Date: ", 10, x + 2, y + 5);
	print(int_to_str(t->day, 2) + "/" + int_to_str(t->month, 2) + "/" + int_to_str(t->year), 10, x + 8, y + 5);
	print("Time: ", 10, x + 2, y + 7);
	print(int_to_str(t->hour, 2) + ":" + int_to_str(t->minute, 2), 10, x + 8, y + 7);

	//===================================== Input ===================================
	cursor(true);

	AD_ET_day(x, y);
	AD_ET_month(x, y);
	AD_ET_year(x, y, t);
	AD_ET_hour(x, y, t);
	AD_ET_minute(x, y, t);

	cursor(false);
	//============================= Edit file & linked list =========================
	int delayhour, capacity = 0;
	long int k;
	long int* p = costed_money(t->id);
	long int a[351];
	for (int i = 0; i < 351; i++)
		a[i] = p[i];
	
	delayhour = (AD_edittravel.year - t->year) * 8760 + (AD_edittravel.month - t->month) * 720 + (AD_edittravel.day - t->day) * 24 + (AD_edittravel.hour - t->hour);
	if (AD_edittravel.minute < t->minute) delayhour--;
	double delayprice = (float)a[350] * (float)delayhour * 5.0 / 100.0;
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
	if (do_transaction(int_to_str(t->id_driver %= 2000000), (0.9)* a[350] / 1000.0, t->id, 1) == 1)
	{

		if (do_transaction("200000", (0.1)* a[350] / 1000.0, t->id, 1) == 1)
		{
			string search = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			t->delay += delayhour;
			//if (DRV_edit.minute < t->minute) t->delay--;
			t->day = AD_edittravel.day;
			t->month = AD_edittravel.month;
			t->year = AD_edittravel.year;
			t->hour = AD_edittravel.hour;
			t->minute = AD_edittravel.minute;
			string replace = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t" + int_to_str(t->delay);
			edit(search, replace, "Travels.txt");

			//return money to passengers accs
			long int id_passenger;
			for (int i = 0; passengers >> id_passenger;)
			{
				if (!id_passenger) continue;
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), (a[i] * (-1) * delayhour * 5.0 / 100.0) / 1000.0, t->id, 1);
				i++;
			}
		}
		else
		{
			print("Your account balance is not enough!", 12, screen.X / 2 - 19, screen.Y / 2 + 4);
			Sleep(3000);
			do_transaction(user.account, (0.9) * a[350] * (-1) / 1000.0, t->id, 1);
		}
	}
	else
	{
		print("Driver account balance is not enough!", 12, screen.X / 2 - 18, screen.Y / 2 + 4);
		Sleep(3000);
	}
	admin_travel_pnl(0, 0);
}
void AD_cancel_travel()
{
	long int a[350];
	bool islater;
	string l;
	travelinfo *t = &t0;
	tm *timer = time();
	//===================================== Input ===================================
	print("Which travel do you want to cancel?", 10, 7, screen.Y - 3);
	cursor(true);
	do
	{
		do
		{
			l = input(0, 6, 43, screen.Y - 3, 50, screen.Y - 3, 9, 12, "bpzEn", 34);
			if (l == "~E") exit(0);
			else if (l == "~z" || l == "~b")
			{
				print(' ', 10, 7, screen.Y - 3, 100);
				cursor(false);
				return;
			}
			else if (l == "~p") admin_pnl();
			else if (l == "") l = "0";
		} while (stoi(l) > nalltravel || stoi(l) < 1);

		t = &t0;
		for (int i = 1; i < stoi(l); i++, t = t->next);

		islater = (timer->tm_year + 1900 < t->year || (timer->tm_year + 1900 == t->year && (timer->tm_yday < yday(t->month, t->day) - 1 || (timer->tm_yday == yday(t->month, t->day) - 1 && (timer->tm_hour < t->hour || (timer->tm_hour == t->hour && timer->tm_min <= t->minute))))));
		if (!islater) print("You can't cancel past travels!", 12, 50, screen.Y - 3);
		else if (t->delay == -1) print("You can't cancel canceled travels!", 12, 50, screen.Y - 3);

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
	{
		if (k)
			capacity++;
	}

	//check if there is enough money in admin & driver acc
	long int *p = costed_money(t->id);
	long int id_passenger;
	long int tprice = p[350];
	for (int i = 0; i < 350; i++)
		a[i] = p[i];

	if (do_transaction(int_to_str(t->id_driver %= 2000000), (0.9)* tprice / 1000.0, t->id, 1) == 1)
	{
		if (do_transaction("200000", (0.1)* tprice / 1000.0, t->id, 1) == 1)
		{
			string s = int_to_str(t->id) + "\t" + int_to_str(t->i) + "\t" + int_to_str(t->f) + "\t" + int_to_str(t->day) + "\t" + int_to_str(t->month) + "\t" + int_to_str(t->year) + "\t" + int_to_str(t->hour) + "\t" + int_to_str(t->minute) + "\t" + t->vehicle + "\t" + int_to_str(t->id_driver) + "\t";
			edit(s + int_to_str(t->delay), s + "-1", "Travels.txt");
			t->delay = -1;
			print(' ', DRV_backcolor, 7, screen.Y - 3, 50);
			//return money to passengers accs
			for (int i = 0; passengers >> id_passenger;)
			{
				if (!id_passenger) continue;
				id_passenger %= 1000000;
				do_transaction(int_to_str(id_passenger), a[i] * (-1) / 1000.0, t->id, 1);
				i++;
			}
		}
		else
		{
			print("Your account balance is not enough!", 12, 50, screen.Y - 3);
			Sleep(3000);
			do_transaction(int_to_str(t->id_driver %= 2000000), (0.9) * tprice * (-1) / 1000.0, t->id, 1);
			print(' ', 10, 7, screen.Y - 3, 84);
		}
	}
	else
	{
		print("Driver account balance is not enough!", 12, 50, screen.Y - 3);
		Sleep(3000);
		print(' ', 10, 7, screen.Y - 3, 84);
	}
}

void admin_travel_pnl(long long int g, int gp) {
	nalltravel = readTravel(-1);
	cursor(false);
	system("cls");
	background(10, screen);
	char ch;
	border(screen.X - 11, screen.Y - 10, screen);
	gotoxy(screen.X / 2, screen.Y - 2);
	cout << "Edit a travel: E";
	gotoxy(screen.X / 2 + 21, screen.Y - 2);
	cout << "Cancel a travel: C";
	ifstream travel;
	travel.open("travels.txt", ios::in);
	if (g == 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->";
	}
	else
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->   Previous Page: <-";
	}
	travel.seekg(g);
	int i = 0;
	int j = 0;
	string sh;
	string temp;
	while (8 + i<screen.Y - 4 && getline(travel, sh))
	{
		date(sh);
		if (diff(date(sh))<0 && diff(date(sh))>-24) 
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<10; i++)
			{
				if (i == 4 || i == 5)cout << '/';
				if (i == 7)cout << ':';
				sht >> temp;
				if (i != 3 && i != 4 && i != 6)temp += '\t';
				print(temp, 9);
			}
			i = i + 2;
			j++;
		}
		if (diff(date(sh))>0 || check2(sh) == 1)
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<10; i++) 
			{
				if (i == 4 || i == 5)cout << '/';
				if (i == 7)cout << ':';
				sht >> temp;
				if (i != 3 && i != 4 && i != 6)temp += '\t';
				print(temp, 4);
			}

			i = i + 2;
			j++;
		}
		if (diff(date(sh))<-24) 
		{
			gotoxy(10, screen.Y - 60 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<10; i++) {
				if (i == 4 || i == 5)cout << '/';
				if (i == 7)cout << ':';
				sht >> temp;
				if (i != 3 && i != 4 && i != 6)temp += '\t';
				print(temp, 10);
			}

			i = i + 2;
			j++;
		}
	}
	if (sh == "")
	{
		gotoxy(5, screen.Y - 2);
		cout << "                                     ";
		gotoxy(5, screen.Y - 2);
		cout << "Previous Page: <-";
	}
	while (1)
	{
		ch = getch();
		if (ch == 26)admin_pnl();
		if (ch == -32) {
			ch = getch();
			if (ch == 'M'&&sh != "")
			{
				insert(gp, travel.tellg() - 37);//moshkel
				admin_travel_pnl(search_index(gp + 1), gp + 1);
			}
			if (ch == 'K'&&g != 0)
				admin_travel_pnl(search_index(gp - 1), gp - 1);
		}
		if (ch == 'e')AD_edit_travel(60, 8);
		if (ch == 'c')AD_cancel_travel();
		else continue;
	}
}

void admin_user_pnl(long long int g, int gp)
{
	cursor(false);
	system("cls");
	background(10, screen);
	char ch;
	border(screen.X - 11, screen.Y - 10, screen);
	ifstream travel;
	travel.open("Users information.txt", ios::in);
	if (g == 0) 
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->";
	}
	else
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->   Previous Page: <-";
	}
	travel.seekg(g);
	int i = 0;
	int j = 0;
	string sh;
	getline(travel, sh);
	while (8 + i<screen.Y - 4 && getline(travel, sh))
	{
		gotoxy(10, screen.Y - 60 + i);
		print(sh, 9);
		i = i + 2;
	}
	if (sh == ""&&gp != 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "                                     ";
		gotoxy(5, screen.Y - 2);
		print("Previous Page: <-", 10);
	}
	while (1) {
		ch = getch();
		if (ch == 26)admin_pnl();
		if (ch == -32) {
			ch = getch();
			if (ch == 'M'&&sh != "")
			{
				insert(gp, travel.tellg() - 25);//moshkel
				admin_user_pnl(search_index(gp + 1), gp + 1);
			}
			if (ch == 'K'&&g != 0)
				admin_user_pnl(search_index(gp - 1), gp - 1);
		}
		else continue;
	}
}

inline void D_signupshow(int length, int width)
{
	background(10, screen);
	cursor(true);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print(" Please Fill the blank to add a driver ", 11, x + 25, y - 1);
	print("Username: ", 10, x + 2, y + 1);
	print("Password: ", 10, x + 2, y + 3);
	print("Confirm Password: ", 10, x + 2, y + 5);
	print("Name: ", 10, x + 2, y + 7);
	print("Family: ", 10, x + 2, y + 9);
	print("Phone Number: ", 10, x + 2, y + 11);
	print("vehicle: ", 10, x + 2, y + 13);
	print("Bank Account Number: ", 10, x + 2, y + 15);
	print("Bank Account Password: ", 10, x + 2, y + 17);
}
inline void D_SU_username(int x, int y)
{
	ifstream allaccountinformation;
	print(' ', 10, x + 1, y + 1);
	print("between 5 and 15", 15, x + 12, y + 1);
	print(' ', 10, x + 1, y + 1);
	while (1)
	{
		do
		{
			user.username = input(5, 15, x + 4, y + 2, x + 12, y + 1, 9, 12, "bzEnle");
			if (user.username == "~b" || user.username == "~z") admin_pnl();
			else if (user.username == "~E") exit(0);
		} while (user.username[0] == '~');

		int id = 0;
		string u, p;
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == user.username)
			{
				print("This username alredy exist!", 12, x + 12, y + 1);
				print(' ', 10, x + 4, y + 2, user.username.length());
				print('X', 12, x + 1, y + 1);
				id = -1;
				break;
			}
		}
		allaccountinformation.close();
		if (id != -1) break;
	}
	print(char(-5), 10, x + 1, y + 1);
}
inline void D_SU_password(int x, int y)
{
	print(' ', 10, x + 1, y + 3);
	print("between 4 and 15", 15, x + 12, y + 3);
	do
	{
		user.password = input(4, 15, x + 4, y + 4, x + 12, y + 3, 9, 12, "bzEnlus", 30, true);
		if (user.password == "~b") admin_pnl();
		else if (user.password == "~z")
		{
			print(' ', 10, x + 1, y + 3);
			print(' ', 10, x + 12, y + 3, 30);
			D_SU_username(x, y);
			print(' ', 10, x + 1, y + 3);
			print("between 4 and 15", 15, x + 12, y + 3);
		}
		else if (user.password == "~E") exit(0);
	} while (user.password[0] == '~');
	print(char(-5), 10, x + 1, y + 3);
}
inline void D_SU_confirmpassword(int x, int y)
{
	string pass;
	print(' ', 10, x + 1, y + 5);
	print("Confirm your password", 15, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, 9, 12, "bzEnlus", 30, true);
			if (pass == "~b") admin_pnl();
			else if (pass == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 20, y + 5, 30);
				D_SU_password(x, y);
				print(' ', 10, x + 1, y + 5);
				print("Confirm your password", 15, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == user.password)
		{
			print(char(-5), 10, x + 1, y + 5);
			break;
		}
		else
		{
			print("X", 12, x + 1, y + 5);
			print("Passwords not matched.", 12, x + 20, y + 5);
			print(' ', 10, x + 4, y + 6, pass.length());
		}
	}
}
inline void D_SU_name(int x, int y)
{
	print(' ', 10, x + 1, y + 7);
	print("between 3 and 10", 15, x + 8, y + 7);
	do
	{
		user.name = input(3, 10, x + 4, y + 8, x + 8, y + 7, 9, 12, "bzElu");
		if (user.name == "~b") admin_pnl();
		else if (user.name == "~z")
		{
			print(' ', 10, x + 1, y + 7);
			print(' ', 10, x + 8, y + 7, 30);
			D_SU_confirmpassword(x, y);
			print(' ', 10, x + 1, y + 7);
			print("between 3 and 10", 15, x + 8, y + 7);
		}
		else if (user.name == "~E") exit(0);
	} while (user.name[0] == '~');
	print(char(-5), 10, x + 1, y + 7);
}
inline void D_SU_family(int x, int y)
{
	print(' ', 10, x + 1, y + 9);
	print("betwen 5 and 20", 15, x + 10, y + 9);
	do
	{
		user.family = input(5, 20, x + 4, y + 10, x + 10, y + 9, 9, 12, "bzElu");
		if (user.family == "~b") admin_pnl();
		else if (user.family == "~z")
		{
			print(' ', 10, x + 1, y + 9);
			print(' ', 10, x + 10, y + 9, 30);
			D_SU_name(x, y);
			print(' ', 10, x + 1, y + 9);
			print("betwen 5 and 20", 15, x + 10, y + 9);
		}
		else if (user.family == "~E") exit(0);
	} while (user.family[0] == '~');
	print(char(-5), 10, x + 1, y + 9);
}
inline void D_SU_phone(int x, int y)
{
	print(' ', 10, x + 1, y + 11);
	print("11 digits", 15, x + 16, y + 11);
	do
	{
		user.phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, 9, 12, "bzEn");
		if (user.phone == "~b") admin_pnl();
		else if (user.phone == "~z")
		{
			print(' ', 10, x + 1, y + 11);
			print(' ', 10, x + 16, y + 11, 30);
			D_SU_family(x, y);
			print(' ', 10, x + 1, y + 11);
			print("11 digits", 15, x + 16, y + 11);
		}
		else if (user.phone == "~E") exit(0);
	} while (user.phone[0] == '~');
	print(char(-5), 10, x + 1, y + 11);
}
inline void D_SU_vehicle(int x, int y)
{
	print(' ', 10, x + 1, y + 13);
	print("Bus,Plane or Train", 15, x + 11, y + 13);
	do
	{
		user.vehicle = input(3, 5, x + 4, y + 14, x + 11, y + 13, 9, 12, "bzElu");
		if (user.vehicle == "~b") admin_pnl();
		else if (user.vehicle == "~z")
		{
			print(' ', 10, x + 1, y + 13);
			print(' ', 10, x + 10, y + 13, 60);
			D_SU_phone(x, y);
			print(' ', 10, x + 1, y + 13);
			print("Bus,Plane or Train", 15, x + 11, y + 13);
		}
		else if (user.vehicle == "~E") exit(0);
	} while (user.vehicle[0] == '~');
	print(char(-5), 10, x + 1, y + 13);
}
inline string D_SU_account(int x, int y)
{
	ifstream acc;
	string line;
	size_t pos;
	print(' ', 10, x + 1, y + 15);
	print("6 digits", 15, x + 23, y + 15);
	while (1)
	{
		do
		{
			user.account = input(6, 6, x + 4, y + 16, x + 23, y + 15, 9, 12, "bzEn");
			if (user.account == "~b") admin_pnl();
			else if (user.account == "~z")
			{
				print(' ', 10, x + 1, y + 15);
				print(' ', 10, x + 23, y + 15, 30);
				D_SU_vehicle(x, y);
				print(' ', 10, x + 1, y + 15);
				print("6 digits", 15, x + 23, y + 15);
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
			print("wrong bank account number!", 12, x + 23, y + 15);
			print("X", 12, x + 1, y + 15);
			print(' ', 10, x + 4, y + 16, 7);
			acc.close();
		}
		else break;
	}
	print(char(-5), 10, x + 1, y + 15);
	return line;
}
inline void D_SU_bankpass(int x, int y, string line)
{
	long long int money;
	string pass, u;
	stringstream l;
	l << line;
	l >> u >> pass >> money;

	print(' ', 10, x + 1, y + 17);
	print("6 digits", 15, x + 25, y + 17);
	while (1)
	{
		do
		{
			user.accpass = input(4, 4, x + 4, y + 18, x + 25, y + 17, 9, 12, "bzEn", 50);
			if (user.accpass == "~b") admin_pnl();
			else if (user.accpass == "~z")
			{
				print(' ', 10, x + 1, y + 17);
				print(' ', 10, x + 25, y + 17, 30);
				D_SU_account(x, y);
				print(' ', 10, x + 1, y + 17);
				print("6 digits", 15, x + 25, y + 17);
			}
			else if (user.accpass == "~E") exit(0);
		} while (user.accpass[0] == '~');

		if (pass == user.accpass)
		{
			print("bank account connected!", 10, x + 25, y + 17);
			user.money = money;
			Sleep(500);
			break;
		}
		else
		{
			print("your bank account password is incorrect!", 12, x + 25, y + 17);
			print("X", 12, x + 1, y + 17);
			print(' ', 10, x + 4, y + 18, 4);
		}
	}
	print(char(-5), 10, x + 1, y + 17);
}
void driver_signup(int length, int width)
{
	D_signupshow(length, width);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	//==================================== Input ===================================
	D_SU_username(x, y);
	D_SU_password(x, y);
	D_SU_confirmpassword(x, y);
	D_SU_name(x, y);
	D_SU_family(x, y);
	D_SU_phone(x, y);
	D_SU_vehicle(x, y);
	string line = D_SU_account(x, y);
	D_SU_bankpass(x, y, line);
	//================================ write in file ===============================
	fstream usersinformation, allaccountinformation;
	usersinformation.open("Drivers information.txt", ios::app);
	allaccountinformation.open("All account information.txt", ios::app);

	allaccountinformation << "\n" << "2" + user.account << "\t" << user.username << "\t" << user.password;
	usersinformation << "\n" << "2" + user.account << "\t" << user.name << "\t" << user.family << "\t" << user.phone << "\t" << user.vehicle;

	allaccountinformation.close();
	usersinformation.close();
	background(160, screen);
	print("Driver added successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
	Sleep(1000);
	admin_pnl();

}

void admin_driver_pnl(long long int g, int gp) {
	cursor(false);
	system("cls");
	background(10, screen);
	char ch;
	border(screen.X - 11, screen.Y - 10, screen);
	ifstream travel;
	travel.open("Drivers information.txt", ios::in);
	if (g == 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->";
	}
	else
	{
		gotoxy(5, screen.Y - 2);
		cout << "Next Page: ->   Previous Page: <-";
	}
	travel.seekg(g);
	int i = 0;
	int j = 0;
	string sh;
	while (8 + i<screen.Y - 4 && getline(travel, sh))
	{
		gotoxy(10, screen.Y - 60 + i);
		print(sh, 9);
		i = i + 2;
	}
	if (sh == ""&&gp != 0)
	{
		gotoxy(5, screen.Y - 2);
		cout << "                                     ";
		gotoxy(5, screen.Y - 2);
		print("Previous Page: <-", 10);
	}
	while (1)
	{
		ch = getch();
		if (ch == 26)admin_pnl();
		if (ch == -32)
		{
			ch = getch();
			if (ch == 'M'&&sh != "")
			{
				insert(gp, travel.tellg() - 43);//moshkel
				admin_driver_pnl(search_index(gp + 1), gp + 1);
			}
			if (ch == 'K'&&g != 0)
				admin_driver_pnl(search_index(gp - 1), gp - 1);
		}
		else continue;
	}

}

int price, capacity, velocity;
inline void vp_b_price() 
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 102, 28, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	price = stoi(i);
}
inline void vp_b_capacity()
{
	cursor(true);
	string i;
	do
	{
		do
		{
			i = input(1, 5, 130, 28, 0, 0, 9, DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i == "~z")vp_b_price();
			else if (i == "~E") exit(0);
		} while (i[0] == '~');
		capacity = stoi(i);
	} while (capacity>60 || capacity % 4);
}
inline void vp_b_velocity()
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 154, 28, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p") admin_pnl();
		else if (i == "~z")vp_b_capacity();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	velocity = stoi(i);
}
inline void vp_t_price()
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 102, 34, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	price = stoi(i);
}
inline void vp_t_capacity()
{
	cursor(true);
	string i;
	do
	{
		do
		{
			i = input(1, 5, 130, 34, 0, 0, 9, DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i == "~z")vp_t_price();
			else if (i == "~E") exit(0);
		} while (i[0] == '~');
		capacity = stoi(i);
	} while (capacity>160 || capacity % 4);
}
inline void vp_t_velocity()
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 154, 34, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p") admin_pnl();
		else if (i == "~z")vp_t_capacity();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	velocity = stoi(i);
}
inline void vp_p_price()
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 102, 40, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	price = stoi(i);
}
inline void vp_p_capacity()
{
	cursor(true);
	string i;
	do
	{

		do
		{
			i = input(1, 5, 130, 40, 0, 0, 9, DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i == "~z")vp_p_price();
			else if (i == "~E") exit(0);
		} while (i[0] == '~');
		capacity = stoi(i);
	} while (capacity>350 || capacity % 8);
}
inline void vp_p_velocity()
{
	cursor(true);
	string i;
	do
	{
		i = input(1, 5, 154, 40, 0, 0, 9, DRV_errorcolor, "bpzEn");
		if (i == "~b" || i == "~p") admin_pnl();
		else if (i == "~z")vp_p_capacity();
		else if (i == "~E") exit(0);
	} while (i[0] == '~');
	velocity = stoi(i);
}
void admin_vehicles_pnl()
{
	string s, temp;
	char ch;
	ifstream v;
	v.open("Vehicle information.txt", ios::in | ios::out);
	system("cls");
	background(10, screen);
	border(screen.X - 150, screen.Y - 50, screen);
	gotoxy(5, screen.Y - 6);
	cout << "Home: Ctrl+P";
	gotoxy(30, screen.Y - 10);
	cout << "Bus: B";
	gotoxy(30, screen.Y - 8);
	cout << "Train: T";
	gotoxy(30, screen.Y - 6);
	cout << "Airplane: A";
	gotoxy(screen.X - 12, screen.Y - 6);
	cout << "Help: H";

	gotoxy(screen.X / 2 - 13, 26);
	print("----------     ----------", 9);
	getline(v, s);
	stringstream st, st2;
	st << s;
	st >> temp;
	gotoxy(76, 28);
	cout << "     Price per kilometer: " << temp;
	st >> temp;
	cout << "\t\tCapacity: " << temp;
	st >> temp;
	cout << "\t\tVelocity: " << temp;
	gotoxy(screen.X / 2 - 13, 32);
	cout << "----------       ----------";
	getline(v, s);
	st.clear();
	st << s;
	st >> temp;
	gotoxy(76, 34);
	cout << "     Price per kilometer: " << temp;
	st >> temp;
	cout << "\t\tCapacity: " << temp;
	st >> temp;
	cout << "\t\tVelocity: " << temp;
	gotoxy(screen.X / 2 - 13, 38);
	cout << "----------          ----------";
	getline(v, s);
	st.clear();
	st << s;
	st >> temp;
	gotoxy(76, 40);
	cout << "     Price per kilometer: " << temp;
	st >> temp;
	cout << "\t\tCapacity: " << temp;
	st >> temp;
	cout << "\t\tVelocity: " << temp;
	while (1)
	{
		if (kbhit())
		{
			ch = getch();
			if (ch == 16)break;
			if (ch == 'b') 
				vp_b_price(); vp_b_capacity(); vp_b_velocity(); edit(int_to_str(bus.price) + '\t' + int_to_str(bus.capacity) + '\t' + int_to_str(bus.velocity), int_to_str(price) + '\t' + int_to_str(capacity) + '\t' + int_to_str(velocity), "Vehicle information.txt"); vehicles();
			
			if (ch == 't') 
				vp_t_price(); vp_t_capacity(); vp_t_velocity(); edit(int_to_str(train.price) + '\t' + int_to_str(train.capacity) + '\t' + int_to_str(train.velocity), int_to_str(price) + '\t' + int_to_str(capacity) + '\t' + int_to_str(velocity), "Vehicle information.txt"); vehicles();
		
			if (ch == 'a')
				vp_p_price(); vp_p_capacity(); vp_p_velocity(); edit(int_to_str(airplane.price) + '\t' + int_to_str(airplane.capacity) + '\t' + int_to_str(airplane.velocity), int_to_str(price) + '\t' + int_to_str(capacity) + '\t' + int_to_str(velocity), "Vehicle information.txt"); vehicles();

			if (ch == 26)break;
		}
		cursor(false);
		Sleep(500);
		gotoxy(screen.X / 2 - 2, 26);
		print("BUS", 13);
		gotoxy(screen.X / 2 - 2, 32);
		print("TRAIN", 13);
		gotoxy(screen.X / 2 - 2, 38);
		print("AIRPLANE", 13);
		Sleep(500);
		gotoxy(screen.X / 2 - 2, 26);
		print("BUS", 14);
		gotoxy(screen.X / 2 - 2, 32);
		print("TRAIN", 14);
		gotoxy(screen.X / 2 - 2, 38);
		print("AIRPLANE", 14);
	}
	switch (ch) {
	case 16:admin_pnl(); break;
	case 26:admin_pnl(); break;
	}
}

string new_username, new_password, new_name, new_family, new_phone;
inline void AD_ED_username(int x, int y)
{
	fstream allaccountinformation;
	print(' ', 10, x + 1, y + 1);
	print("between 5 and 15", 15, x + 12, y + 1);
	string u, p;
	while (1)
	{
		int id = 0;
		do
		{
			new_username = input(5, 15, x + 4, y + 2, x + 12, y + 1, 9, 12, "bpzEnle");
			if (new_username == "~b" || new_username == "~p" || new_username == "~z") admin_pnl();
			else if (new_username == "~E") exit(0);

		} while (new_username[0] == '~');
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id >> u >> p)
		{
			if (u == new_username && user.username != new_username)
			{
				print("This username alredy exist!", 12, x + 12, y + 1);
				print(' ', 10, x + 4, y + 2, user.username.length());
				print('X', 12, x + 1, y + 1);
				id = -1;
				break;
			}
		}
		allaccountinformation.close();
		if (id != -1) break;
	}
	print(char(-5), 10, x + 1, y + 1);
}
inline void AD_ED_password(int x, int y)
{
	print(' ', 10, x + 1, y + 3);
	print("between 4 and 15", 15, x + 12, y + 3);
	do
	{
		new_password = input(4, 15, x + 4, y + 4, x + 12, y + 3, 9, 12, "bpzEnlus", 30, true);
		if (new_password == "~b" || new_password == "~p") admin_pnl();
		else if (new_password == "~z")
		{
			print(' ', 10, x + 12, y + 3, 30);
			print(' ', 10, x + 1, y + 3);
			AD_ED_username(x, y);
			print("between 4 and 15", 15, x + 12, y + 3);
		}
		else if (new_password == "~E") exit(0);
	} while (new_password[0] == '~');
	print(char(-5), 10, x + 1, y + 3);
}
inline void AD_ED_confirmpassword(int x, int y)
{
	string pass;
	print(' ', 10, x + 1, y + 5);
	print("Confirm your password", 15, x + 20, y + 5);
	while (1)
	{
		do
		{
			pass = input(4, 15, x + 4, y + 6, x + 20, y + 5, 9, 12, "bpzEnlus", 25, true);
			if (pass == "~b" || pass == "~p") admin_pnl();
			else if (pass == "~z")
			{
				print(' ', 10, x + 20, y + 5, 25);
				print(' ', 10, x + 1, y + 5);
				AD_ED_password(x, y);
				print("Confirm your password", 15, x + 20, y + 5);
			}
			else if (pass == "~E") exit(0);
		} while (pass[0] == '~');

		if (pass == new_password)
		{
			print(char(-5), 10, x + 1, y + 5);
			break;
		}
		else
		{
			print("X", 12, x + 1, y + 5);
			print("Passwords not matched.", 12, x + 20, y + 5);
			print(' ', 10, x + 4, y + 6, pass.length());
		}
	}
}
inline void AD_ED_name(int x, int y)
{
	print(' ', 10, x + 1, y + 7);
	print("between 3 and 10", 15, x + 8, y + 7);
	do
	{
		new_name = input(3, 10, x + 4, y + 8, x + 8, y + 7, 9, 12, "bpzElu");
		if (new_name == "~b" || new_name == "~p") admin_pnl();
		else if (new_name == "~z")
		{
			print(' ', 10, x + 8, y + 7, 30);
			print(' ', 10, x + 1, y + 7);
			AD_ED_confirmpassword(x, y);
			print("between 3 and 10", 15, x + 8, y + 7);
		}
		else if (new_name == "~E") exit(0);
	} while (new_name[0] == '~');
	print(char(-5), 10, x + 1, y + 7);
}
inline void AD_ED_family(int x, int y)
{
	print(' ', 10, x + 1, y + 9);
	print("betwen 5 and 20", 15, x + 10, y + 9);
	do
	{
		new_family = input(5, 20, x + 4, y + 10, x + 10, y + 9, 9, 12, "bpzElu");
		if (new_family == "~b" || new_family == "~p") admin_pnl();
		else if (new_family == "~z")
		{
			print(' ', 10, x + 10, y + 9, 30);
			print(' ', 10, x + 1, y + 9);
			AD_ED_name(x, y);
			print("betwen 5 and 20", 15, x + 10, y + 9);
		}
		else if (new_family == "~E") exit(0);
	} while (new_family[0] == '~');
	print(char(-5), 10, x + 1, y + 9);
}
inline void AD_ED_phone(int x, int y)
{
	print(' ', 10, x + 1, y + 11);
	print("11 digits", 15, x + 16, y + 11);

	do
	{
		new_phone = input(11, 11, x + 4, y + 12, x + 16, y + 11, 9, 15, "bpzEn");
		if (new_phone == "~b" || new_phone == "~p") admin_pnl();
		else if (new_phone == "~z")
		{
			print(' ', 10, x + 16, y + 11, 30);
			print(' ', 10, x + 1, y + 11);
			AD_ED_family(x, y);
			print("11 digits", 15, x + 16, y + 11);
		}
		else if (new_phone == "~E") exit(0);
	} while (new_phone[0] == '~');
	print(char(-5), 10, x + 1, y + 11);
}
void edit_admin(int length, int width)
{
	//===================================== Show ===================================
	background(10, screen);
	border(length, width, screen);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("Username: ", 10, x + 2, y + 1);
	print(user.username, 10, x + 4, y + 2);
	print("Password: ", 10, x + 2, y + 3);
	print(user.password, 10, x + 4, y + 4);
	print("Confirm password: ", 10, x + 2, y + 5);
	print(user.password, 10, x + 4, y + 6);
	print("Name: ", 10, x + 2, y + 7);
	print(user.name, 10, x + 4, y + 8);
	print("Family: ", 10, x + 2, y + 9);
	print(user.family, 10, x + 4, y + 10);
	print("Phone number: ", 10, x + 2, y + 11);
	print(user.phone, 10, x + 4, y + 12);
	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("E: Edit information", 10, 7, screen.Y - 2);
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
			admin_pnl();
			b = 0;
			break;
		case 27:
			exit(0);
		}
	}
	cursor(true);
	//================================== Username ==================================
	AD_ED_username(x, y);
	//================================== Password ==================================
	AD_ED_password(x, y);
	AD_ED_confirmpassword(x, y);
	//===================================== Name ===================================
	AD_ED_name(x, y);
	//==================================== Family ==================================
	AD_ED_family(x, y);
	//===================================== Phone ==================================
	AD_ED_phone(x, y);
	//================================ Write in file ===============================
	string search, replace;

	search = int_to_str(user.id) + "\t" + user.username + "\t" + user.password;
	replace = int_to_str(user.id) + "\t" + new_username + "\t" + new_password;
	int check1 = edit(search, replace, "All account information.txt"), check2;

	search = int_to_str(user.id) + "\t" + user.name + "\t" + user.family + "\t" + user.phone;
	replace = int_to_str(user.id) + "\t" + new_name + "\t" + new_family + "\t" + new_phone;
	if (check1) check2 = edit(search, replace, "Users information.txt");

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
	admin_pnl();
}

string id_driver, driver, i, f, year, month, day, hour, minute;
inline void AD_NT_driver(int x, int y) {
	cursor(true);
	print(' ', 10, x + 1, y + 1);
	print("between 5 and 15", 15, x + 8, y + 2);
	do
	{
		do
		{
			driver = input(5, 15, x + 21, y + 1, x + 4, y + 2, 9, 12, "bzEnle");
			if (driver == "~b" || driver == "~p" || driver == "~z") admin_pnl();
			else if (driver == "~E") exit(0);
		} while (driver[0] == '~');

		if (driver.length() > 15 || driver.length() < 5)
		{
			print("Must be between 5 and 15", 12, x + 4, y + 2);
			print('X', 12, x + 1, y + 1);
		}
		ifstream check;
		check.open("All account information.txt");
		string sh, temp;
		int c = 0;
		stringstream sht;
		getline(check, sh);
		while (sh != "") {
			getline(check, sh);
			sht << sh;
			sht >> temp;
			if (temp[0] == '2') {
				id_driver = temp;
				temp = "";
				sht >> temp;
				if (temp == driver) {
					c = 1;
					break;
				}
			}
		}
		if (c == 1)break;
		else print("This driver doesn't exists!", 12, x + 4, y + 2);


	} while (1);

	print(char(-5), 10, x + 1, y + 1);
}
inline void AD_NT_i(int x, int y)
{
	print(' ', 10, x + 1, y + 3);
	print("between 1 and 300", 15, x + 4, y + 4);
	do
	{
		do
		{
			i = input(1, 3, x + 8, y + 3, x + 4, y + 4, 9, 12, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
			else if (i == "~E") exit(0);
		} while (i[0] == '~');

		if (stoi(i) > 300 || stoi(i) < 1)
		{
			print("Must be between 1 and 300", 12, x + 4, y + 4);
			print('X', 12, x + 1, y + 3);
		}
	} while (stoi(i) > 300 || stoi(i) < 1);
	print(char(-5), 10, x + 1, y + 3);
}
inline void AD_NT_f(int x, int y)
{
	print(' ', 10, x + 1, y + 5);
	print("between 1 and 300", 15, x + 4, y + 6);
	do
	{
		do
		{
			f = input(1, 3, x + 6, y + 5, x + 4, y + 6, 9, 12, "bpzEn");
			if (f == "~b" || f == "~p") admin_pnl();
			else if (f == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 4, y + 6, 30);
				AD_NT_i(x, y);
				print("between 1 and 300", 12, x + 4, y + 6);
			}
			else if (f == "~E") exit(0);
		} while (f[0] == '~');

		if (stoi(f) > 300 || stoi(f) < 1)
		{
			print("Must be between 1 and 300", 12, x + 4, y + 6);
			print('X', 12, x + 1, y + 5);
		}
		else if (f == i)
		{
			print("Invalid city", 12, x + 4, y + 6);
			print('X', 12, x + 1, y + 5);
		}
	} while (stoi(f) > 300 || stoi(f) < 1 || f == i);
	print(char(-5), 10, x + 1, y + 5);
}
inline void AD_NT_day(int x, int y)
{
	tm* timer = time();
	print(' ', 10, x + 1, y + 7);
	do
	{
		do
		{
			day = input(2, 2, x + 8, y + 7, x + 4, y + 8, 9, 12, "bpzEn");
			if (day == "~b" || day == "~p") admin_pnl();
			else if (day == "~z")
			{
				print(' ', 10, x + 1, y + 7);
				print(' ', 10, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_mday, 2), 10, x + 8, y + 9);
				AD_NT_f(x, y);
			}
			else if (day == "~E") exit(0);
		} while (day[0] == '~');

		if (stoi(day) > 31 || stoi(day) < 1)
		{
			print("Must be between 1 and 31", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
	} while (stoi(day) > 31 || stoi(day) < 1);
	print(' ', 10, x + 1, y + 7);
}
inline void AD_NT_month(int x, int y)
{
	tm* timer = time();
	print(' ', 10, x + 1, y + 7);
	do
	{
		do
		{
			month = input(2, 2, x + 11, y + 7, x + 4, y + 8, 9, 12, "bpzEn");
			if (month == "~b" || month == "~p") admin_pnl();
			else if (month == "~z")
			{
				print(' ', 10, x + 1, y + 7);
				print(' ', 10, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_mon + 1, 2), 10, x + 11, y + 9);
				AD_NT_day(x, y);
			}
			else if (month == "~E") exit(0);
		} while (month[0] == '~');

		if (stoi(month) > 12 || stoi(month) < 1)
		{
			print("Must be between 1 and 12", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
	} while (stoi(month) > 12 || stoi(month) < 1);
	print(' ', 10, x + 1, y + 7);
}
inline void AD_NT_year(int x, int y)
{
	tm* timer = time();
	bool islater;
	print(' ', 10, x + 1, y + 7);
	do
	{
		do
		{
			year = input(4, 4, x + 14, y + 7, x + 4, y + 8, 9, 12, "bpzEn");

			if (year == "~b" || year == "~p") admin_pnl();
			else if (year == "~z")
			{
				print(' ', 10, x + 1, y + 7);
				print(' ', 10, x + 4, y + 8, 30);
				print(int_to_str(timer->tm_year + 1900, 2), 10, x + 14, y + 9);
				AD_NT_month(x, y);
			}
			else if (year == "~E") exit(0);
		} while (year[0] == '~');

		islater = (timer->tm_year + 1900 < stoi(year) || (timer->tm_year + 1900 == stoi(year) && timer->tm_yday <= yday(stoi(month), stoi(day)) - 1));
		if (!islater)
		{
			print("Can you traval in time?", 12, x + 4, y + 8);
			print('X', 12, x + 1, y + 7);
		}
	} while (!islater);
	print(char(-5), 10, x + 1, y + 7);
}
inline void AD_NT_hour(int x, int y)
{
	tm* timer = time();
	print(' ', 10, x + 1, y + 9);
	do
	{
		do
		{
			hour = input(2, 2, x + 8, y + 9, x + 4, y + 10, 9, 12, "bpzEn");
			if (hour == "~b" || month == "~p") admin_pnl();
			else if (hour == "~z")
			{
				print(' ', 10, x + 1, y + 9);
				print(' ', 10, x + 4, y + 10, 30);
				print(int_to_str(timer->tm_hour, 2), 10, x + 14, y + 11);
				AD_NT_year(x, y);
			}
			else if (hour == "~E") exit(0);
		} while (hour[0] == '~');

		if (stoi(hour) > 23 || stoi(hour) < 0)
		{
			print("Must be between 0 and 23", 12, x + 4, y + 10);
			print('X', 12, x + 1, y + 9);
		}
	} while (stoi(hour) > 23 || stoi(hour) < 0);
	print(' ', DRV_acceptcolor, x + 1, y + 9);
}
inline void AD_NT_minute(int x, int y)
{
	tm* timer = time();
	bool islater;
	print(' ', 10, x + 1, y + 9);
	do
	{
		do
		{
			minute = input(2, 2, x + 11, y + 9, x + 4, y + 10, 9, 12, "bpzEn");

			if (minute == "~b" || minute == "~p") admin_pnl();
			else if (minute == "~z")
			{
				print(' ', 10, x + 1, y + 9);
				print(' ', 10, x + 4, y + 10, 30);
				print(int_to_str(timer->tm_min, 2), 10, x + 14, y + 11);
				AD_NT_hour(x, y);
			}
			else if (minute == "~E") exit(0);
		} while (minute[0] == '~');

		islater = (timer->tm_year + 1900 < stoi(year) || (timer->tm_year + 1900 == stoi(year) && (timer->tm_yday < yday(stoi(month), stoi(day)) - 1 || (timer->tm_yday == yday(stoi(month), stoi(day)) - 1 && (timer->tm_hour < stoi(hour) || (timer->tm_hour == stoi(hour) && timer->tm_min <= stoi(minute)))))));
		if (stoi(minute) < 0 || stoi(minute) >= 60)
		{
			print("Must be between 0 and 59", 12, x + 4, y + 10);
			print('X', 12, x + 1, y + 9);
		}
		else if (!islater)
		{
			print("Can you traval in time?", 12, x + 4, y + 10);
			print('X', 12, x + 1, y + 9);
		}
	} while (stoi(minute) < 0 || stoi(minute) >= 60 || !islater);
	print(char(-5), 10, x + 1, y + 9);
}
void ad_new_travel(int length, int width)
{
	//==================================== Show ====================================
	tm* timer = time();
	system("cls");
	print("", 10);
	border(length, width, screen);
	cursor(false);
	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", 10, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("Driver's username: ", 10, x + 2, y + 1);
	print("From: ", 10, x + 2, y + 3);
	print("To: ", 10, x + 2, y + 5);
	print("Date: ", 10, x + 2, y + 7);
	print(int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900), 10, x + 8, y + 7);
	print("Time: ", 10, x + 2, y + 9);
	print(int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), 10, x + 8, y + 9);

	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	//print("E: Edit information", DRV_captioncolor, 7, screen.Y - 2);
	cursor(true);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AD_NT_driver(x, y);
	AD_NT_i(x, y);
	AD_NT_f(x, y);
	AD_NT_day(x, y);
	AD_NT_month(x, y);
	AD_NT_year(x, y);
	AD_NT_hour(x, y);
	AD_NT_minute(x, y);
	//=============================== Write in file ===============================
	ifstream d;
	string l, temp, v;
	stringstream lt;
	d.open("Drivers information.txt");
	while (getline(d, l))
	{
		lt << l;
		lt >> temp;
		if (temp == id_driver)
		{
			for (int i = 0; i<4; i++)
			{
				temp = "";
				lt >> temp;
			}
			v = temp;
			break;
		}
	}
	ifstream travels;
	travels.open("Travels.txt", ios::in);
	int id_travel;
	travels >> id_travel;
	travels.close();

	edit(int_to_str(id_travel), int_to_str(1 + id_travel), "Travels.txt");
	id_travel++;

	ofstream travel;
	travel.open("Travels.txt", ios::app);
	travel << id_travel << "\t" << i << "\t" << f << "\t" << day << "\t" << month << "\t" << year << "\t" << hour << "\t" << minute << "\t" << v << "\t" << id_driver << "\t0\n";
	travel.close();
	//write in chairs
	fstream chairs("Chairs.txt", ios::app);
	chairs << id_travel << "\t";
	if (v == "Bus")
	{
		chairs << bus.capacity;
		for (int i = 0; i < bus.capacity; i++)
			chairs << "\t0";
	}
	else if (v == "Train")
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
	t->vehicle = v;
	t->id_driver = stoi(id_driver);
	t->num = t->previous->num + 1;
	background(160, screen);
	print("Travel added successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
	Sleep(1000);
	admin_pnl();
	return;
}

void AD_help()
{
	background(10, screen);
	system("cls");
	border(110, 25, screen);
	print("Travel Color Meaning:", 15, screen.X / 2 - 5, screen.Y / 2 - 10);
	print(" Past or Canceled", 4, screen.X / 2 - 15, screen.Y / 2 - 8);
	print(" Today", 9, screen.X / 2 + 2, screen.Y / 2 - 8);
	print(" days after Today", 10, screen.X / 2 + 8, screen.Y / 2 - 8);
	print("Travel page order:", 15, screen.X / 2 - 5, screen.Y / 2 - 6);
	print("Number   /   First City  /   Second City /   Date & Time /   Vehicle /   Driver ID", 15, screen.X / 2 - 40, screen.Y / 2 - 4);
	print("Users page order:", 15, screen.X / 2 - 5, screen.Y / 2 - 1);
	print("User ID  /   Name    /   Family  /   Phone", 15, screen.X / 2 - 18, screen.Y / 2 + 1);
	print("Driver page order:", 15, screen.X / 2 - 5, screen.Y / 2 + 4);
	print("Driver ID    /   Name    /   Family  /   phone   /   vehicle", 15, screen.X / 2 - 25, screen.Y / 2 + 6);
	print("Transactions order:", 15, screen.X / 2 - 5, screen.Y / 2 + 9);
	print("+: --> increasing your account balance", 9, screen.X / 2 - 14, screen.Y / 2 + 11);
	print("-: --> decreasing your account balance", 12, screen.X / 2 - 14, screen.Y / 2 + 12);
	print("Press a key to exit", 15, screen.X / 2 - 10, screen.Y - 2);
	cursor(false);
	_getch();
	admin_pnl();
}

void admin_pnl()
{
	vehicles();
	cursor(false);
	system("cls");
	background(10, screen);
	head = (struct page*)malloc(sizeof(page));
	head->num = 0;
	char ch;
	border(screen.X - 10, screen.Y - 30, screen);
	fstream travel;
	travel.open("travels.txt", ios::in | ios::out | ios::app);
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);
	//travel<<info->tm_mday<<'/'<<info->tm_mon+1<<'/'<<info->tm_year+1900<<' '<<info->tm_hour<<':'<<info->tm_min;
	// travel.close();
	//=======================showing info=============================
	gotoxy(5, 5);
	cout << "Hi Admin";
	gotoxy(5, screen.Y - 10);
	cout << "Home: Ctrl+P";
	gotoxy(5, screen.Y - 8);
	cout << "New Travel: T";
	gotoxy(5, screen.Y - 6);
	cout << "Drivers: D";
	gotoxy(30, screen.Y - 10);
	cout << "Users: U";
	gotoxy(30, screen.Y - 8);
	cout << "New Driver: N";
	gotoxy(30, screen.Y - 6);
	cout << "Transactions: M";
	gotoxy(60, screen.Y - 10);
	cout << "Discounts: P";
	gotoxy(60, screen.Y - 8);
	cout << "Vehicles: V";
	gotoxy(60, screen.Y - 6);
	cout << "Edit Admin's Info: E";
	gotoxy(screen.X - 12, screen.Y - 6);
	cout << "Help: H";

	int i = 0;
	int j = 0;
	string sh;
	string temp;
	while (screen.Y - 50 + i<screen.Y - 15 && getline(travel, sh))
	{
		date(sh);
		if (diff(date(sh))<0 && diff(date(sh))>-24) 
		{
			gotoxy(10, screen.Y - 50 + i);
			stringstream sht;
			sht << sh;
			for (int i = 0; i<10; i++) 
			{
				if (i == 4 || i == 5)cout << '/';
				if (i == 7)cout << ':';
				sht >> temp;
				if (i != 3 && i != 4 && i != 6)temp += '\t';
				print(temp, 9);
			}

			i = i + 2;
			j++;
		}
	}
	if (j == 0)
	{
		gotoxy(screen.X / 2 - 10, screen.Y / 2);
		print("  There aren't any travels for today", 9);
		gotoxy(screen.X / 2 - 10, screen.Y / 2 + 1);
		cout << "For showing all travels history press C.";

	}
	else 
	{
		gotoxy(screen.X / 2 + 50, screen.Y / 2);
		cout << "  For editing travels Or showing all travels history";
		gotoxy(screen.X / 2 + 50, screen.Y / 2 + 1);
		cout << "                      Press C";
	}
	while (1) 
	{
		if (kbhit()) 
		{
			ch = getch();
			/*
			if(ch=='t')break;
			if(ch=='c')break;
			if(ch==16)break;
			if(ch==26)break;
			if(ch=='v')break;
			if(ch=='e')break;
			if(ch=='t')break;
			if(ch=='u')break;
			if(ch=='d')break;
			if(ch=='n')break;
			*/

			switch (ch) 
			{
			case 'c':admin_travel_pnl(0, 0); break;
				//        case 16:welcome(10,500);break;
				//        case 26:login(30,20,10,12);break;
			case 'v':admin_vehicles_pnl(); break;
			case 'e':edit_admin(50, 12); break;
			case 't':ad_new_travel(60, 10); break;
			case 'u':admin_user_pnl(0, 0); break;
			case 'd':admin_driver_pnl(0, 0); break;
			case 'n':driver_signup(100, 18); break;
			case 'm':admin_transaction(0, 0); break;
			case 'p':admin_discount(0, 0); break;
			case 'h':AD_help();
			}
		}
		cursor(false);
		i = 0;
		while (i / 2<j)
		{
			gotoxy(19, screen.Y - 50 + i);
			cout << " ";
			gotoxy(19, screen.Y - 50 + i);
			cout << "-";
			i = i + 2;
		}
		Sleep(400);
		i = 0;
		while (i / 2<j)
		{
			gotoxy(19, screen.Y - 50 + i);
			cout << " ";
			gotoxy(20, screen.Y - 50 + i);
			cout << "-";
			i = i + 2;
		}
		Sleep(400);
		i = 0;
		while (i / 2<j)
		{
			gotoxy(20, screen.Y - 50 + i);
			cout << " ";
			gotoxy(21, screen.Y - 50 + i);
			cout << "-";
			i = i + 2;
		}
		Sleep(400);
		i = 0;

		while (i / 2<j)
		{
			gotoxy(21, screen.Y - 50 + i);
			cout << " ";
			gotoxy(22, screen.Y - 50 + i);
			cout << ">";
			i = i + 2;
		}
		Sleep(400);
		i = 0;
		while (i / 2<j)
		{
			gotoxy(22, screen.Y - 50 + i);
			cout << " ";
			i = i + 2;
		}
	}
}
















//-------------------------------------------------------------------- sign up ---------------------------------------------------------------------
string inviter, id_inviter;

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
	print("betwen 4 and 20", SU_warningcolor, x + 10, y + 9);
	do
	{
		user.family = input(4, 20, x + 4, y + 10, x + 10, y + 9, SU_backcolor, SU_errorcolor, "bzElu");
		if (user.family == "~b") welcome(30);
		else if (user.family == "~z")
		{
			print(' ', SU_acceptcolor, x + 1, y + 9);
			print(' ', SU_backcolor, x + 10, y + 9, 30);
			SU_name(x, y);
			print(' ', SU_acceptcolor, x + 1, y + 9);
			print("betwen 4 and 20", SU_warningcolor, x + 10, y + 9);
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
	ifstream allaccountinformation;
	int id;

	print(' ', SU_acceptcolor, x + 1, y + 13);
	print("Inviter's Username is Optional and between 5 and 15.", SU_warningcolor, x + 11, y + 13);
	do
	{
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
		if (inviter == "") { id = -1; continue; }

		id = 0;
		string u, p;
		allaccountinformation.open("All account information.txt", ios::in);
		while (allaccountinformation >> id_inviter >> u >> p)
		{
			if (u == inviter)
			{
				id = -1;
				break;
			}
		}
		if (id != -1)
		{
			print("This username doesn't exist!", SU_errorcolor, x + 11, y + 13);
			print('X', SU_errorcolor, x + 1, y + 13);
		}
		allaccountinformation.close();
	} while (id != -1);

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
				print(' ', SU_backcolor, x + 25, y + 17, 50);
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
	user.id = 1000000 + stoi(user.account);
	//================================ write in file ===============================
	fstream usersinformation, allaccountinformation;
	usersinformation.open("Users information.txt", ios::app);
	allaccountinformation.open("All account information.txt", ios::app);

	allaccountinformation << "1" + user.account << "\t" << user.username << "\t" << user.password << "\n";
	usersinformation << "1" + user.account << "\t" << user.name << "\t" << user.family << "\t" << user.phone << "\n";

	allaccountinformation.close();
	usersinformation.close();
	//=================================== Inviter ==================================
	string l, ll;
	if (id_inviter != "")
	{
		ifstream discount("Discounts.txt");
		while (getline(discount, l))
		{
			stringstream s;
			s << l;
			s >> ll;
			if (ll == id_inviter) break;
		}
		discount.close();
		edit(l, l + "\t100", "Discounts.txt");

		fstream odiscount("Discounts.txt", ios::app);
		odiscount << user.id << "\t0\t50\t50\n";
		odiscount.close();
	}
	else
	{
		fstream odiscount("Discounts.txt", ios::app);
		odiscount << user.id << "\t0\n";
		odiscount.close();
	}
	background(160, screen);
	gotoxy(screen.X / 2 - 11, screen.Y / 2);
	cout << "Welcome to your panel";
	Sleep(1000);
	USR_showtop(screen.X - 11, screen.Y - 10);
	pnl_user(screen.X - 11, screen.Y - 10);

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

	if (u == "admin" && p == "admin") return 3;

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
		//else if (check == 3) admin_pnl();
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
	//vehicles information in struct
	vehicles();

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
	gotoxy(screen.X / 2 - 23, screen.Y / 2 + 4);
	cout << "To watch intruduction and control keys press H";
	//==================================== goto panels =============================
	char c;
	while (true)
	{
		c = _getch();
		if (c == 's' || c == 'S') login(37, 5);
		else if (c == 'u' || c == 'U') signup(100, 18);
		else if (c == 'g' || c == 'G')	buy(60, 8, true);
		else if (c == 'h' || c == 'H')  main_help();
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
	//main_help();
	//loading(50, 50, screen);
	//DRV_help();
	//USR_help();
	//USR_showtop(screen.X - 12, screen.Y - 11);
	//USR_chairs(17, 10, 1009, "Bus");
	welcome(1);

	/*for (int i = 0; i < 299; i++)
	{
	//print(i, i); print("	fghfgfsghfhfhfa\n", i);
	printf("%d : %c\n", i, i);
	}*/
}
