#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>
#include "MemoryAllProcessInfo.c"
#include "MemoryGeneralInfo.c"
#include "ChangeProcessProtect.c"
#include "AllocMemory.c"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
	while(1)
	{
		PrintGeneralInfo();
		PrintAllProcess();
		AllocMemory(InputProtect(),InputState(),NULL);//нужно что-то сделать с адресами 
		//FreeMemory(InputStateFree(),InputIdProcess());
		printf("VirtualAlloc failed with status %lu\n", GetLastError());
		//ChangeProcessProtect(InputProtect(),InputIdProcess());//Пока не работает
		system("PAUSE");
	}
	
	return 0;
}
