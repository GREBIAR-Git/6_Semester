#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tchar.h>
#include <psapi.h>
#include <locale.h>
#include <conio.h>
#include <wchar.h>

#define DIV (1024*1024)
#define WIDTH 7

/*void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Print the process name and identifier.

    _tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );

    // Release the handle to the process.

    CloseHandle( hProcess );
}*/

int main()
{
	 	
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); //установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); //установка кодовой страницы win-cp 1251 в поток вывода
	/*DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }


    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }*/










	MEMORYSTATUSEX state;
	GlobalMemoryStatusEx (&state);
	
	//state.
	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
        WIDTH, state.dwMemoryLoad);
    _tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
        WIDTH, state.ullTotalPhys / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
        WIDTH, state.ullAvailPhys / DIV);
    _tprintf(TEXT("There are %*I64d total KB of paging file.\n"),
        WIDTH, state.ullTotalPageFile / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of paging file.\n"),
        WIDTH, state.ullAvailPageFile / DIV);
    _tprintf(TEXT("There are %*I64d total KB of virtual memory.\n"),
        WIDTH, state.ullTotalVirtual / DIV);
    _tprintf(TEXT("There are %*I64d free  KB of virtual memory.\n"),
        WIDTH, state.ullAvailVirtual / DIV);
 
    _tprintf(TEXT("There are %*I64d free  KB of extended memory.\n"),
        WIDTH, state.ullAvailExtendedVirtual / DIV);

	wprintf (L"Процент используемой памяти %d%% \n",state.dwMemoryLoad);
	wprintf (L"Объем фактической физической памяти %lu Мбайт\n",state.ullTotalPhys/DIV);
	wprintf (L"%lu Мбайт dwTotalPageFile \n",state.ullTotalPageFile/DIV);
	wprintf (L"%lu Мбайт dwAvailPageFile  \n",state.ullAvailPageFile/DIV);
	wprintf (L"%lu Мбайт dwTotalVirtual \n",state.ullAvailVirtual/DIV);
	wprintf (L"%lu Мбайт dwAvailVirtual \n",state.ullAvailVirtual/DIV);
	
	system("PAUSE");
	return 0;

}


