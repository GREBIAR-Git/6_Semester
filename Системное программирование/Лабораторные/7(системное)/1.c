#include <windows.h>
#include <stdio.h>

int main()
{
   	HANDLE hMapFile;
   	LPCTSTR pBuf;
   	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,256,TEXT("kat"));
   	pBuf = (LPTSTR) MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS, 0,0,256);
   	CopyMemory((PVOID)pBuf, TEXT("Message from first process."), strlen("Message from first process.") * sizeof(TCHAR));
	system("pause");
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	return 0;
}