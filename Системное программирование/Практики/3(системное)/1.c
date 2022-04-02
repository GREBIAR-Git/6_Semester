#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>

#define DIV (1024*1024)

MEMORYSTATUSEX MemoryInfo()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MEMORYSTATUSEX status = MemoryInfo();
	
	wprintf (L"Процент используемой памяти %d%% \n",status.dwMemoryLoad);
	wprintf (L"Объем физической памяти %lu Мбайт\n",status.ullTotalPhys/DIV);
    wprintf (L"Объем свободный физической памяти %lu Мбайт\n",status.ullAvailPhys/DIV);
	wprintf (L"Объем физической памяти %lu Мбайт(С файлами подкачки)\n",status.ullTotalPageFile/DIV);
	wprintf (L"Объем свободный физической памяти %lu Мбайт(С файлами подкачки)\n",status.ullAvailPageFile/DIV);
	wprintf (L"Объем виртуальной памяти %lu Мбайт \n",status.ullAvailVirtual/DIV);
	wprintf (L"Объем виртуальной памяти %lu Мбайт \n",status.ullAvailVirtual/DIV);
	
	system("PAUSE");
	return 0;
}


