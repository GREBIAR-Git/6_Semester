#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>
#include <tchar.h>
#include "MemoryAllProcessInfo.c"
#include "MemoryGeneralInfo.c"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
    PrintGeneralInfo();
    PrintAllProcess();
    
	system("PAUSE");
	return 0;
}
