void admin_pnl();
struct page{
    int num;
    struct page *next;
};
struct page* head;
void insert(int index,int value){
    struct page* temp=head;
    for(int i=1;i<index;i++){
        temp=temp->next;
    }
    struct page* newpage;
    newpage=(struct page*)malloc(sizeof(page));
    newpage->num=value;
    newpage->next=temp->next;
    temp->next=newpage;

}
int search_index(int index){
    struct page* temp=head;
    for(int i=1;i<index;i++){
        temp=temp->next;
    }
    return temp->num;
}
string date(string sh){
        string temp;
        string t;
        int j=0;
        for(int i=0;j<7;i++){
            if(sh[i]>='0'&&sh[i]<='9'){
                temp+=sh[i];
            }
            else{
                switch (j){
    case 3:{
       t+=temp;
       t+='/';
        break;
    }
    case 4:{
        t+=temp;
        t+='/';
        break;
    }
    case 5:{
         t+=temp;
        t+=' ';
        break;
    }
    case 6:{
         t+=temp;
        t+=':';
        break;
    }
    }
    j++;
    temp="";
            }
        }
        return t;
    }
double diff(string t){
    //string t="26/12/2018 23:57";
    time_t now;
    time(&now);
    struct tm *dt;
    dt=localtime(&now);
    string temp;
    int j=0;
    for(int i=0;i<=t.length();i++){
       if(t[i]>='0'&&t[i]<='9'){
        temp+=t[i];
    }
    else{
    switch (j){
    case 0:{
        dt->tm_mday=atoi(temp.c_str());
        temp="";
        j++;
        break;
    }
    case 1:{
        dt->tm_mon=atoi(temp.c_str())-1;
        temp="";
        j++;
        break;
    }
    case 2:{
         dt->tm_year=atoi(temp.c_str())-1900;
         temp="";
        j++;
        break;
    }
    case 3:{
        dt->tm_hour=atoi(temp.c_str());
        temp="";
        j++;
        break;
    }
    case 4:{
        dt->tm_min=atoi(temp.c_str());
        temp="";
        j++;
        break;

    }
    }
    }

}
return difftime(now,mktime(dt))/3600;

}
int check(string sh){
    stringstream sht;
    string temp;
    sht<<sh;
    sht>>temp;
    temp="";
    sht>>temp;
    if(atoll(temp.c_str())>=0)return 1;
    else return 0;
}
string ran(){
    srand(time(0));
    string t;
    for(int i=0;i<7;i++){
        t+=char(rand()%26+65);
    }
    return t;
}
int check2(string t){
    string temp;
        stringstream sh;
        sh<<t;
    for(int i=0;i<11;i++){
        sh>>temp;
    }
    if(atoi(temp.c_str())==-1)return 1;
    else return 0;
}

void admin_travel_pnl(long long int,int);


void admin_transaction(long long int g,int gp){
cursor(false);
system("cls");
background(10,screen);
char ch;
border(screen.X-11,screen.Y-10,screen);
ifstream travel;
travel.open("Transactions.txt",ios::in);
if(g==0){
  gotoxy(5,screen.Y-2);
  cout<<"Next Page: ->";
}
else{
        gotoxy(5,screen.Y-2);
        cout<<"Next Page: ->   Previous Page: <-";

}
travel.seekg(g);
	int i=0;
	int j=0;
	string sh;
	string temp;
	while(8+i<screen.Y-4&&getline(travel,sh)){
        stringstream shtt;
        shtt<<sh;
        shtt>>temp;
        if(temp=="200000"){
            gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<7;i++){
                if(i==3||i==4)cout<<'/';
                if(i==6)cout<<':';
            sht>>temp;
            if(i!=3&&i!=2&&i!=5)temp+='\t';
        print(temp,15);

        }

        i=i+2;
        j++;
        }
        else if(check(sh)){
            gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<7;i++){
                if(i==3||i==4)cout<<'/';
                if(i==6)cout<<':';
            sht>>temp;
            if(i!=3&&i!=2&&i!=5)temp+='\t';
        print(temp,9);

        }

        i=i+2;
        j++;
        }
        else{
            gotoxy(10,screen.Y-60+i);
            stringstream sht;
        sht<<sh;
        for(int i=0;i<7;i++){
                if(i==3||i==4)cout<<'/';
                if(i==6)cout<<':';
            sht>>temp;
            if(i!=3&&i!=2&&i!=5)temp+='\t';
        print(temp,12);
        }

        i=i+2;
        j++;
        }

	}
	if(sh==""&&g!=0){
            gotoxy(5,screen.Y-2);
        cout<<"                                     ";
         gotoxy(5,screen.Y-2);
        print("Previous Page: <-",10);
	}
	while(1){
	ch=getch();
	if(ch==26)admin_pnl();
	if(ch==-32){
        ch=getch();
        if(ch=='M'&&sh!=""){
            insert(gp,travel.tellg()-5);
            admin_transaction(search_index(gp+1),gp+1);
        }
            if(ch=='K'&&g!=0){
        admin_transaction(search_index(gp-1),gp-1);
            }
	}
	else continue;
	}
}


void admin_discount(long long int g,int gp){
    cursor(false);
system("cls");
background(10,screen);
char ch;
border(screen.X-11,screen.Y-10,screen);
gotoxy(screen.X/2,screen.Y-2);
cout<<"Press to make a discount: N";
gotoxy(screen.X/2+32,screen.Y-2);
cout<<"Choose a discount by name: C";
ifstream travel;
travel.open("Discounts.txt",ios::in);
if(g==0){
  gotoxy(5,screen.Y-2);
  cout<<"Next Page: ->";
}
else{
        gotoxy(5,screen.Y-2);
        cout<<"Next Page: ->   Previous Page: <-";

}
travel.seekg(g);
	int i=0;
	int j=0;
	string sh,temp;
	while(8+i<screen.Y-4&&getline(travel,sh)){
        gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        sht>>temp;
        if(temp[0]>='0'&&temp[0]<='9')continue;
        print(sh,9);
        cout<<"%";
        i=i+2;
	}
	if(sh==""&&gp!=0){
            gotoxy(5,screen.Y-2);
        cout<<"                                     ";
         gotoxy(5,screen.Y-2);
        print("Previous Page: <-",10);
	}
	while(1){
	ch=getch();
	if(ch==26)admin_pnl();
	if(ch==-32){
        ch=getch();
        if(ch=='M'&&sh!=""){
            insert(gp,travel.tellg()-25);
            admin_discount(search_index(gp+1),gp+1);
        }
            if(ch=='K'&&g!=0)
        admin_discount(search_index(gp-1),gp-1);
	}
	if(ch=='n'){
        gotoxy(screen.X/2,screen.Y-2);
        print("                                 ",10);
        print("Enter a number for amount of discount: ",10);
        string d2=input(1,2,screen.X/2+72,screen.Y-2,screen.X/2-20,screen.Y-2,9,12,"bzEn");
        if(d2=="~z")admin_discount(0,0);
        string d=ran();
        gotoxy(screen.X/2,screen.Y-2);
        print("                                            ",10);
        gotoxy(screen.X/2,screen.Y-2);
        cout<<"Discount is: "<<d<<" "<<d2<<"%";
        ofstream di;
        di.open("Discounts.txt",ios::app);
        di<<d<<"\t"<<d2<<"\n";
        print("                                                                 ",10);
        di.close();
        Sleep(2000);
        admin_discount(0,0);

	}
	if(ch=='c'){
            ifstream disc;
    disc.open("Discounts.txt");
    int id=0;
    string se,tempse;
         gotoxy(screen.X/2,screen.Y-2);
        print("                                                               ",10);
        gotoxy(screen.X/2,screen.Y-2);
        print("Enter the exact code of desire discount to change: ",10);
        string s=input(7,7,screen.X/2+51,screen.Y-2,screen.X/2-20,screen.Y-2,9,12,"bzElu");
        while(getline(disc,se)){
        stringstream sett;
            sett<<se;
            sett>>tempse;
            if(tempse==s){
                id=1;
                break;
            }

        }
        disc.close();
        if(id=0){
             gotoxy(screen.X/2,screen.Y-2);
        print("                                                               ",10);
        gotoxy(screen.X/2,screen.Y-2);
            print("This discount doesn't exists!",12);
        Sleep(1000);
        admin_discount(0,0);
        }
        if(s=="~z")admin_discount(0,0);
        gotoxy(screen.X/2,screen.Y-2);
        print("                                                                  ",10);
        gotoxy(screen.X/2,screen.Y-2);
        print("Enter the new discount value: ",10);
        string r=input(1,2,screen.X/2+30,screen.Y-2,screen.X/2-20,screen.Y-2,9,12,"bzEn");
        if(r=="~z")admin_discount(0,0);
        print(' ',10,screen.X/2,screen.Y-2,50);
        int cd;
        if(r=="0") cd=edit(se+"\n","","Discounts.txt");
        else  cd=edit(se,s+"\t"+r,"Discounts.txt");
        if(cd==1){
                gotoxy(screen.X/2,screen.Y-2);
            cout<<"Changed successfully!";
        }
        else{
            gotoxy(screen.X/2,screen.Y-2);
            print("Error!",12);
        }
        Sleep(1000);
        admin_discount(0,0);
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
			{
				admin_pnl();
			}
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
			if (day == "~p")
			{
				admin_pnl();
			}
			else if (day == "~z")
			{
				print(' ', 10, x + 1, y + 5);
				print(' ', 10, x + 4, y + 6, 30);
				print(int_to_str(timer->tm_mday, 2), 10, x + 8, y + 5);
				admin_travel_pnl(0,0);
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
	{
		a[i] = p[i];
	}
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
	if (do_transaction(int_to_str(t->id_driver%=2000000), (0.9)* a[350] / 1000.0, t->id, 1) == 1)
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
	admin_travel_pnl(0,0);
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
	{
		a[i] = p[i];

	}


	if (do_transaction(int_to_str(t->id_driver%=2000000), (0.9)* tprice / 1000.0, t->id, 1) == 1)
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
			do_transaction(int_to_str(t->id_driver%=2000000), (0.9) * tprice * (-1) / 1000.0, t->id, 1);
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


void admin_travel_pnl(long long int g,int gp){
nalltravel=readTravel(-1);
cursor(false);
system("cls");
background(10,screen);
char ch;
border(screen.X-11,screen.Y-10,screen);
gotoxy(screen.X/2,screen.Y-2);
cout<<"Edit a travel: E";
gotoxy(screen.X/2+21,screen.Y-2);
cout<<"Cancel a travel: C";
ifstream travel;
travel.open("travels.txt",ios::in);
if(g==0){
  gotoxy(5,screen.Y-2);
  cout<<"Next Page: ->";
}
else{
        gotoxy(5,screen.Y-2);
        cout<<"Next Page: ->   Previous Page: <-";

}
travel.seekg(g);
	int i=0;
	int j=0;
	string sh;
	string temp;
	while(8+i<screen.Y-4&&getline(travel,sh)){
        date(sh);
        if(diff(date(sh))<0&&diff(date(sh))>-24){
            gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<10;i++){
                if(i==4||i==5)cout<<'/';
                if(i==7)cout<<':';
            sht>>temp;
            if(i!=3&&i!=4&&i!=6)temp+='\t';
        print(temp,9);
        }

        i=i+2;
        j++;
        }
        if(diff(date(sh))>0||check2(sh)==1){
            gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<10;i++){
                if(i==4||i==5)cout<<'/';
                if(i==7)cout<<':';
            sht>>temp;
            if(i!=3&&i!=4&&i!=6)temp+='\t';
        print(temp,4);
        }

        i=i+2;
        j++;
        }
        if(diff(date(sh))<-24){
            gotoxy(10,screen.Y-60+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<10;i++){
                if(i==4||i==5)cout<<'/';
                if(i==7)cout<<':';
            sht>>temp;
            if(i!=3&&i!=4&&i!=6)temp+='\t';
        print(temp,10);
        }

        i=i+2;
        j++;
        }
	}
	if(sh==""){
            gotoxy(5,screen.Y-2);
        cout<<"                                     ";
         gotoxy(5,screen.Y-2);
        cout<<"Previous Page: <-";
	}
	while(1){
	ch=getch();
	if(ch==26)admin_pnl();
	if(ch==-32){
        ch=getch();
        if(ch=='M'&&sh!=""){
            insert(gp,travel.tellg()-37);
            admin_travel_pnl(search_index(gp+1),gp+1);
        }
            if(ch=='K'&&g!=0)
        admin_travel_pnl(search_index(gp-1),gp-1);
	}
	if(ch=='e')AD_edit_travel(60,8);
	if(ch=='c')AD_cancel_travel();
	else continue;
	}
}




void admin_user_pnl(long long int g,int gp){
cursor(false);
system("cls");
background(10,screen);
char ch;
border(screen.X-11,screen.Y-10,screen);
ifstream travel;
travel.open("Users information.txt",ios::in);
if(g==0){
  gotoxy(5,screen.Y-2);
  cout<<"Next Page: ->";
}
else{
        gotoxy(5,screen.Y-2);
        cout<<"Next Page: ->   Previous Page: <-";

}
travel.seekg(g);
	int i=0;
	int j=0;
	string sh;
	getline(travel,sh);
	while(8+i<screen.Y-4&&getline(travel,sh)){
        gotoxy(10,screen.Y-60+i);
        print(sh,9);
        i=i+2;
	}
	if(sh==""&&gp!=0){
            gotoxy(5,screen.Y-2);
        cout<<"                                     ";
         gotoxy(5,screen.Y-2);
        print("Previous Page: <-",10);
	}
	while(1){
	ch=getch();
	if(ch==26)admin_pnl();
	if(ch==-32){
        ch=getch();
        if(ch=='M'&&sh!=""){
            insert(gp,travel.tellg()-25);
            admin_user_pnl(search_index(gp+1),gp+1);
        }
            if(ch=='K'&&g!=0)
        admin_user_pnl(search_index(gp-1),gp-1);
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
	print(' ',10, x + 1, y + 1);
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
				print("Confirm your password",15, x + 20, y + 5);
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
			print("Passwords not matched.",12, x + 20, y + 5);
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
			print("between 3 and 10",15, x + 8, y + 7);
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

	allaccountinformation<<"\n" << "2" + user.account << "\t" << user.username << "\t" << user.password;
	usersinformation <<"\n" << "2" + user.account << "\t" << user.name << "\t" << user.family << "\t" << user.phone<<"\t"<<user.vehicle;

	allaccountinformation.close();
	usersinformation.close();
	background(160, screen);
    print("Driver added successfuly :D", 160, (screen.X - 40) / 2, screen.Y / 2);
    Sleep(1000);
	admin_pnl();

}



void admin_driver_pnl(long long int g,int gp){
      cursor(false);
system("cls");
background(10,screen);
char ch;
border(screen.X-11,screen.Y-10,screen);
ifstream travel;
travel.open("Drivers information.txt",ios::in);
if(g==0){
  gotoxy(5,screen.Y-2);
  cout<<"Next Page: ->";
}
else{
        gotoxy(5,screen.Y-2);
        cout<<"Next Page: ->   Previous Page: <-";

}
travel.seekg(g);
	int i=0;
	int j=0;
	string sh;
	while(8+i<screen.Y-4&&getline(travel,sh)){

        gotoxy(10,screen.Y-60+i);
        print(sh,9);
        i=i+2;
	}
	if(sh==""&&gp!=0){
            gotoxy(5,screen.Y-2);
        cout<<"                                     ";
         gotoxy(5,screen.Y-2);
        print("Previous Page: <-",10);
	}
	while(1){
	ch=getch();
	if(ch==26)admin_pnl();
	if(ch==-32){
        ch=getch();
        if(ch=='M'&&sh!=""){
            insert(gp,travel.tellg()-43);
            admin_driver_pnl(search_index(gp+1),gp+1);
        }
            if(ch=='K'&&g!=0)
        admin_driver_pnl(search_index(gp-1),gp-1);
	}

	else continue;
	}

}




int price,capacity,velocity;
inline void vp_b_price(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 102, 28, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    price=stoi(i);
}
inline void vp_b_capacity(){
    cursor(true);
    string i;
    do{
    do
    {
            i = input(1, 5, 130, 28, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_b_price();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    capacity=stoi(i);
    }while(capacity>60||capacity%4);
}
inline void vp_b_velocity(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 154, 28, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_b_capacity();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    velocity=stoi(i);
}
inline void vp_t_price(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 102, 34, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    price=stoi(i);
}
inline void vp_t_capacity(){
    cursor(true);
    string i;
    do{
    do
    {
            i = input(1, 5, 130, 34, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_t_price();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    capacity=stoi(i);
    }while(capacity>160||capacity%4);
}
inline void vp_t_velocity(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 154, 34, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_t_capacity();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    velocity=stoi(i);
}
inline void vp_p_price(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 102, 40, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p" || i == "~z") admin_pnl();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    price=stoi(i);
}
inline void vp_p_capacity(){
    cursor(true);
    string i;
    do
    {

    do
    {
            i = input(1, 5, 130, 40, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_p_price();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    capacity=stoi(i);
    }while(capacity>350 || capacity%8);
}
inline void vp_p_velocity(){
    cursor(true);
    string i;
    do
    {
            i = input(1, 5, 154, 40, 0, 0,9 , DRV_errorcolor, "bpzEn");
			if (i == "~b" || i == "~p") admin_pnl();
			else if (i=="~z")vp_p_capacity();
			else if (i == "~E") exit(0);
    }while(i[0]=='~');
    velocity=stoi(i);
}
void admin_vehicles_pnl(){
    string s,temp;
    char ch;
    ifstream v;
    v.open("Vehicle information.txt",ios::in|ios::out);
    system("cls");
    background(10,screen);
    border(screen.X-150,screen.Y-50,screen);
	gotoxy(5,screen.Y-6);
	cout<<"Home: Ctrl+P";
	gotoxy(30,screen.Y-10);
	cout<<"Bus: B";
	gotoxy(30,screen.Y-8);
	cout<<"Train: T";
	gotoxy(30,screen.Y-6);
	cout<<"Airplane: A";
	gotoxy(screen.X-12,screen.Y-6);
	cout<<"Help: H";





    gotoxy(screen.X/2-13,26);
    print("----------     ----------",9);
    getline(v,s);
    stringstream st,st2;
    st<<s;
    st>>temp;
    gotoxy(76,28);
    cout<<"     Price per kilometer: "<<temp;
    st>>temp;
    cout<<"\t\tCapacity: "<<temp;
    st>>temp;
    cout<<"\t\tVelocity: "<<temp;
    gotoxy(screen.X/2-13,32);
    cout<<"----------       ----------";
    getline(v,s);
    st.clear();
    st<<s;
    st>>temp;
    gotoxy(76,34);
    cout<<"     Price per kilometer: "<<temp;
    st>>temp;
    cout<<"\t\tCapacity: "<<temp;
    st>>temp;
    cout<<"\t\tVelocity: "<<temp;
     gotoxy(screen.X/2-13,38);
    cout<<"----------          ----------";
    getline(v,s);
    st.clear();
    st<<s;
    st>>temp;
    gotoxy(76,40);
    cout<<"     Price per kilometer: "<<temp;
    st>>temp;
    cout<<"\t\tCapacity: "<<temp;
    st>>temp;
    cout<<"\t\tVelocity: "<<temp;
    while(1){
            if(kbhit()){
                ch=getch();
                if(ch==16)break;
                if (ch=='b'){
                        vp_b_price();vp_b_capacity();vp_b_velocity();edit(int_to_str(bus.price)+'\t'+int_to_str(bus.capacity)+'\t'+int_to_str(bus.velocity),int_to_str(price)+'\t'+int_to_str(capacity)+'\t'+int_to_str(velocity),"Vehicle information.txt");vehicles();
                }
                if(ch=='t'){
                        vp_t_price();vp_t_capacity();vp_t_velocity();edit(int_to_str(train.price)+'\t'+int_to_str(train.capacity)+'\t'+int_to_str(train.velocity),int_to_str(price)+'\t'+int_to_str(capacity)+'\t'+int_to_str(velocity),"Vehicle information.txt");vehicles();
                }
                if(ch=='a'){
                     vp_p_price();vp_p_capacity();vp_p_velocity();edit(int_to_str(airplane.price)+'\t'+int_to_str(airplane.capacity)+'\t'+int_to_str(airplane.velocity),int_to_str(price)+'\t'+int_to_str(capacity)+'\t'+int_to_str(velocity),"Vehicle information.txt");vehicles();
                }
                if(ch==26)break;
            }
        cursor(false);
        Sleep(500);
       gotoxy(screen.X/2-2,26);
       print("BUS",13);
       gotoxy(screen.X/2-2,32);
       print("TRAIN",13);
       gotoxy(screen.X/2-2,38);
       print("AIRPLANE",13);
       Sleep(500);
       gotoxy(screen.X/2-2,26);
       print("BUS",14);
       gotoxy(screen.X/2-2,32);
       print("TRAIN",14);
       gotoxy(screen.X/2-2,38);
       print("AIRPLANE",14);
    }
    switch (ch){
        case 16:admin_pnl();break;
        case 26:admin_pnl();break;

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
		new_name = input(3, 10, x + 4, y + 8, x + 8, y + 7,9, 12, "bpzElu");
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
	print("Name: ",10, x + 2, y + 7);
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







string id_driver,driver,i, f, year, month, day, hour, minute;
inline void AD_NT_driver(int x,int y){
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
    string sh,temp;
    int c=0;
    stringstream sht;
    getline(check,sh);
    while(sh!=""){
        getline(check,sh);
        sht<<sh;
        sht>>temp;
        if(temp[0]=='2'){
            id_driver=temp;
            temp="";
            sht>>temp;
            if(temp==driver){
                c=1;
                break;
            }
        }
    }
    if(c==1)break;
    else print("This driver doesn't exists!",12, x + 4, y + 2);


	} while (1);

	print(char(-5),10, x + 1, y + 1);
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
				print(int_to_str(timer->tm_year + 1900, 2),10, x + 14, y + 9);
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
			hour = input(2, 2, x + 8, y + 9, x + 4, y + 10, 9,12, "bpzEn");
			if (hour == "~b" || month == "~p") admin_pnl();
			else if (hour == "~z")
			{
				print(' ', 10, x + 1, y + 9);
				print(' ', 10, x + 4, y + 10, 30);
				print(int_to_str(timer->tm_hour, 2), 10, x + 14, y +11);
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
	print("",10);
	border(length, width, screen);
	cursor(false);
	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	print("", 10, 7, screen.Y - 2);
	int x = (screen.X - length) / 2, y = (screen.Y - width) / 2;
	print("Driver's username: ",10, x + 2, y + 1);
	print("From: ", 10, x + 2, y + 3);
	print("To: ",10, x + 2, y + 5);
	print("Date: ", 10, x + 2, y + 7);
	print(int_to_str(timer->tm_mday, 2) + "/" + int_to_str(timer->tm_mon + 1, 2) + "/" + int_to_str(timer->tm_year + 1900), 10, x + 8, y + 7);
	print("Time: ", 10, x + 2, y + 9);
	print(int_to_str(timer->tm_hour, 2) + ":" + int_to_str(timer->tm_min, 2), 10, x + 8, y + 9);

	print(' ', 10, 5, screen.Y - 2, screen.X - 2 * 5 - 1);
	//print("E: Edit information", DRV_captioncolor, 7, screen.Y - 2);
	cursor(true);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Input ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	AD_NT_driver(x,y);
	AD_NT_i(x, y);
	AD_NT_f(x, y);
    AD_NT_day(x, y);
	AD_NT_month(x, y);
	AD_NT_year(x, y);
	AD_NT_hour(x, y);
	AD_NT_minute(x, y);
	//=============================== Write in file ===============================
	ifstream d;
	string l,temp,v;
	stringstream lt;
	d.open("Drivers information.txt");
	while(getline(d,l)){
        lt<<l;
        lt>>temp;
        if(temp==id_driver){
            for(int i=0;i<4;i++){
                temp="";
                lt>>temp;
            }
            v=temp;
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
	fstream chairs("Chairs.txt",ios::app);
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
	return ;
}


void AD_help()
{
	background(10, screen);
	system("cls");
	border(110, 25, screen);
	print("Travel Color Meaning:",15,screen.X / 2-5 ,screen.Y / 2 -10);
	print(" Past or Canceled", 4, screen.X / 2-15 , screen.Y / 2 - 8);
	print(" Today",9,screen.X / 2 +2,screen.Y / 2 - 8);
	print(" days after Today",10, screen.X / 2 +8 , screen.Y / 2 - 8);
	print("Travel page order:", 15, screen.X / 2-5 , screen.Y / 2 -6);
	print("Number   /   First City  /   Second City /   Date & Time /   Vehicle /   Driver ID", 15, screen.X / 2 - 40, screen.Y / 2 -4);
	print("Users page order:",15,screen.X/2-5,screen.Y/2-1);
	print("User ID  /   Name    /   Family  /   Phone",15,screen.X/2-18,screen.Y/2+1);
	print("Driver page order:",15,screen.X/2-5,screen.Y/2+4);
	print("Driver ID    /   Name    /   Family  /   phone   /   vehicle",15,screen.X/2-25,screen.Y/2+6);
	print("Transactions order:", 15, screen.X / 2-5, screen.Y / 2 + 9);
	print("+: --> increasing your account balance", 9, screen.X / 2 - 14, screen.Y / 2 + 11);
	print("-: --> decreasing your account balance", 12, screen.X / 2 - 14, screen.Y / 2 + 12);
	print("Press a key to exit", 15, screen.X / 2 - 10, screen.Y - 2);
	cursor(false);
	getch();
	admin_pnl();
}




void admin_pnl(){
vehicles();
cursor(false);
system("cls");
background(10,screen);
  head=(struct page*)malloc(sizeof(page));
  head->num=0;
	char ch;
	border(screen.X-10,screen.Y-30,screen);
fstream travel;
travel.open("travels.txt",ios::in|ios::out|ios::app);
	time_t rawtime;
   struct tm *info;
   time( &rawtime );
   info = localtime( &rawtime );
   //travel<<info->tm_mday<<'/'<<info->tm_mon+1<<'/'<<info->tm_year+1900<<' '<<info->tm_hour<<':'<<info->tm_min;
   // travel.close();
	//=======================showing info=============================
	gotoxy(5,5);
	cout<<"Hi Admin";
    gotoxy(5,screen.Y-10);
	cout<<"Home: Ctrl+P";
	gotoxy(5,screen.Y-8);
	cout<<"New Travel: T";
	gotoxy(5,screen.Y-6);
	cout<<"Drivers: D";
	gotoxy(30,screen.Y-10);
	cout<<"Users: U";
	gotoxy(30,screen.Y-8);
	cout<<"New Driver: N";
	gotoxy(30,screen.Y-6);
	cout<<"Transactions: M";
	gotoxy(60,screen.Y-10);
	cout<<"Discounts: P";
	gotoxy(60,screen.Y-8);
	cout<<"Vehicles: V";
	gotoxy(60,screen.Y-6);
	cout<<"Edit Admin's Info: E";
	gotoxy(screen.X-12,screen.Y-6);
	cout<<"Help: H";






	int i=0;
	int j=0;
	string sh;
	string temp;
	while(screen.Y-50+i<screen.Y-15 && getline(travel,sh)){
        date(sh);
        if(diff(date(sh))<0&&diff(date(sh))>-24){
        gotoxy(10,screen.Y-50+i);
        stringstream sht;
        sht<<sh;
        for(int i=0;i<10;i++){
                if(i==4||i==5)cout<<'/';
                if(i==7)cout<<':';
            sht>>temp;
            if(i!=3&&i!=4&&i!=6)temp+='\t';
        print(temp,9);
        }

        i=i+2;
        j++;
        }
	}
	 if(j==0){
            gotoxy(screen.X/2-10,screen.Y/2);
            print("  There aren't any travels for today",9);
            gotoxy(screen.X/2-10,screen.Y/2+1);
            cout<<"For showing all travels history press C.";

        }
        else{
     gotoxy(screen.X/2+50,screen.Y/2);
     cout<<"  For editing travels Or showing all travels history";
     gotoxy(screen.X/2+50,screen.Y/2+1);
     cout<<"                      Press C";
        }
    while(1){
            if(kbhit()){
                ch=getch();
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

    switch (ch){
        case 'c':admin_travel_pnl(0,0);break;
//        case 16:welcome(10,500);break;
//        case 26:login(30,20,10,12);break;
        case 'v':admin_vehicles_pnl();break;
        case 'e':edit_admin(50,12);break;
        case 't':ad_new_travel(60,10);break;
        case 'u':admin_user_pnl(0,0);break;
        case 'd':admin_driver_pnl(0,0);break;
        case 'n':driver_signup(100,18);break;
        case 'm':admin_transaction(0,0);break;
        case 'p':admin_discount(0,0);break;
        case 'h':AD_help();
    }
            }
    cursor(false);
    i=0;
    while(i/2<j){
        gotoxy(19,screen.Y-50+i);
        cout<<" ";
        gotoxy(19,screen.Y-50+i);
        cout<<"-";
        i=i+2;
	}
	Sleep(400);
	i=0;
    while(i/2<j){
        gotoxy(19,screen.Y-50+i);
        cout<<" ";
        gotoxy(20,screen.Y-50+i);
        cout<<"-";
        i=i+2;
	}
	Sleep(400);
	i=0;
    while(i/2<j){
        gotoxy(20,screen.Y-50+i);
        cout<<" ";
        gotoxy(21,screen.Y-50+i);
        cout<<"-";
        i=i+2;
	}
	Sleep(400);
	i=0;

    while(i/2<j){
        gotoxy(21,screen.Y-50+i);
        cout<<" ";
        gotoxy(22,screen.Y-50+i);
        cout<<">";
        i=i+2;
	}
	Sleep(400);
	i=0;
	 while(i/2<j){
	gotoxy(22,screen.Y-50+i);
        cout<<" ";
        i=i+2;
    }
    }
}