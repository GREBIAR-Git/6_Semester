#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <psapi.h>
#include <locale.h>
#include <tchar.h>

#define DIV (1024*1024)

MEMORYSTATUSEX MemoryInfo()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return status;
}

char * GetState(DWORD state)
{
    switch (state)
    {
        case MEM_COMMIT:
            return "COMMIT";
            break;
        case MEM_FREE:
            return "FREE";
            break;
        case MEM_RESERVE:
            return "RESERVE";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

char * GetType(DWORD type)
{
    switch (type)
    {
        case MEM_IMAGE:
            return "IMAGE";
            break;
        case MEM_MAPPED:
            return "MAPPED";
            break;
        case MEM_PRIVATE:
            return "PRIVATE";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

char * GetProtect(DWORD protect)
{
    switch (protect)
    {
        case PAGE_NOACCESS:
            return "NOACCESS";
            break;
        case PAGE_READONLY :
            return "READONLY";
            break;
        case PAGE_READWRITE:
            return "READWRITE";
            break;
        case PAGE_EXECUTE:
            return "EXECUTE";
            break;
        case PAGE_EXECUTE_READ:
            return "EXECUTE_READ";
            break;
        case PAGE_EXECUTE_READWRITE:
            return "EXECUTE_READWRITE";
            break;
        case PAGE_GUARD:
            return "GUARD";
            break;
        case PAGE_NOCACHE:
            return "NOCACHE";
            break;
        case PAGE_WRITECOPY:
            return "WRITECOPY";
            break;
        case PAGE_EXECUTE_WRITECOPY:
            return "EXECUTE_WRITECOPY";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

void PrintGeneralInfo(MEMORYSTATUSEX status)
{
    wprintf (L"Процент используемой памяти %d%% \n",status.dwMemoryLoad);
	wprintf (L"Объем физической памяти %lu Мбайт\n",status.ullTotalPhys/DIV);
    wprintf (L"Объем свободный физической памяти %lu Мбайт\n",status.ullAvailPhys/DIV);
	wprintf (L"Объем физической памяти %lu Мбайт(С файлами подкачки)\n",status.ullTotalPageFile/DIV);
	wprintf (L"Объем свободный физической памяти %lu Мбайт(С файлами подкачки)\n",status.ullAvailPageFile/DIV);
	wprintf (L"Объем виртуальной памяти %lu Мбайт \n",status.ullAvailVirtual/DIV);
	wprintf (L"Объем виртуальной памяти %lu Мбайт \n",status.ullAvailVirtual/DIV);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
    PrintGeneralInfo(MemoryInfo());

    MEMORY_BASIC_INFORMATION mbi;
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    LPCVOID offset=0;

    unsigned short columnWidth = 20;

    printf("%*s\t", columnWidth, "Base Address (0x)");
    printf("%*s\t", columnWidth, "Type");
    printf("%*s\t", columnWidth, "State");
    printf("%*s\t", columnWidth, "Protect");
    printf("\n\n");

    while(offset< si.lpMaximumApplicationAddress)
    {
        VirtualQuery((LPCVOID)(0 + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));

        //printf("Base Address - 0x%lx;\n Type - %s;\n State - %s;\n Protect - %s;\n\n",mbi.BaseAddress,GetType(mbi.Type),GetState(mbi.State),GetProtect(mbi.Protect));
        printf("%*lx\t", columnWidth, mbi.BaseAddress);
        printf("%*s\t", columnWidth, GetType(mbi.Type));
        printf("%*s\t", columnWidth, GetState(mbi.State));
        printf("%*s\t", columnWidth, GetProtect(mbi.Protect));

        printf("\n");
        
        offset+=mbi.RegionSize;
    }
	system("PAUSE");
	return 0;
}


