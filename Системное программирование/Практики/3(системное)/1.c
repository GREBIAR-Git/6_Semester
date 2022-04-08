#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>
#include "MemoryAllProcessInfo.c"
#include "MemoryGeneralInfo.c"
#include "ChangeProcessProtect.c"
#include "AllocMemory.c"
#include "Heap.c"

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    int f=1;
	while(f!=0)
	{
		wprintf(L"1-Общая информация\n2-Вывести все процессы\n3-Выделить память\n4-Освободить память\n5-Поменять права защиты процесса\n6-Создать кучу\n7-Удалить кучу\n8-Выделть память под кучу\n9-Освободить память под кучу\n");
		scanf("%d",&f);
		switch (f)
		{
		case 1:
			PrintGeneralInfo();
			break;
		case 2:
			PrintAllProcess();
			break;
		case 3:
			AllocMemory(InputProtect(),InputState(),NULL);
			break;	
		case 4:
			FreeMemory(InputStateFree(),InputIdProcess());
			break;
		case 5:
			ChangeProcessProtect(InputProtect(),InputIdProcess());
			break;
		case 6:
			NewHeap();
			break;
		case 7:
			DelHeap();
			break;
		case 8:
			AllocHeap();
			break;
		case 9:
			FreeHeap();
			break;
		}
	    printf("\nerror - %lu\n", GetLastError());
		system("PAUSE");
	}
	return 0;
}
