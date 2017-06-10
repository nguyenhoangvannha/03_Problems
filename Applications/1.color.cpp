#define _CRT_SECURE_NO_WARNINGS
#include  "iostream"
#include "string"
#include "windows.h"
using namespace std;
int main()
{
	char mamau[10] ="color ";
	char ci[4];
	char ngoac[2] = "";
	ngoac[0] = '"';
	int i = 0;
	for (i = 0; i < 10; i++)
	{

		for (char j = 'A'; j < 'G'; j++)
		{
			strcpy(mamau, ngoac);
			strcat(mamau, "color ");
			_itoa(i, ci, 10);
			ci[1] = j;
			ci[2] = '"';
			ci[3] = '\0';
			strcat(mamau, ci);
			system(mamau);
			cout << mamau << "\t";
		}
		cout << endl;
	}
	system("pause");
}