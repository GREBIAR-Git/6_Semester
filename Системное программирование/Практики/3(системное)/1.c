#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>
#include "MemoryAllProcessInfo.c"
#include "MemoryGeneralInfo.c"
#include "ChangeProcessProtect.c"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
	while(1)
	{
		PrintGeneralInfo();
		PrintAllProcess();
		ChangeProcessProtect(InputProtect(),InputIdProcess());//Пока не работает
		system("PAUSE");
	}
	
	return 0;
}
