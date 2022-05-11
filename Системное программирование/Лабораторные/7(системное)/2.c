#include <windows.h>
#include <stdio.h>

int main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;
    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,TEXT("kat"));
    pBuf = (LPTSTR) MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS, 0,0,256);
    printf("%s\n",pBuf);
    system("PAUSE");
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    return 0;
}