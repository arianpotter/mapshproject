#include <cstdlib>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	int n, i = 1;
	system("color 24");
	while (i++)
	{
		cin >> n;
		cout << n*n << endl;
		if (i == 2) system("color 25");
		if (i == 3) system("color 26");
		if (i == 4) system("color 16");
		if (i == 5) system("color 26");
		if (i == 6) system("color 35");
		if (i == 7) system("color 24");

	}
	return 0;
}