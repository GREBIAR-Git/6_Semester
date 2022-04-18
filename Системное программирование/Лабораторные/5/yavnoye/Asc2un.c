#include "EvryThng.h"

#define BUF_SIZE 256

_declspec (dllexport)

BOOL Asc2Un (LPCTSTR, LPCTSTR, BOOL);

BOOL Asc2Un (LPCTSTR fin, LPCTSTR fOut, BOOL bFaillfExists)
{
    /* Функция копирования файла ASCII в Unicode на базе CopyFile. */
    HANDLE hIn, hOut;
    DWORD fdwOut, nIn, nOut, iCopy;
    CHAR aBuffer[BUF_SIZE];
    WCHAR uBuffer[BUF_SIZE];
    BOOL WriteOK = TRUE;
    hIn = CreateFile(fin, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /* Определяем действие CreateFile, если выходной файл уже существует.*/
    fdwOut = CREATE_NEW||CREATE_ALWAYS;
    hOut = CreateFile(fOut, GENERIC_WRITE, 0, NULL, fdwOut, FILE_ATTRIBUTE_NORMAL, NULL);
    while (ReadFile (hIn, aBuffer, BUF_SIZE, &nIn, NULL) && nIn > 0 && WriteOK)
    {
        for (iCopy = 0; iCopy < nIn; iCopy++)
        {
            /* Преобразование каждого символа. */
            printf("\n%c\t", aBuffer [iCopy]);
            uBuffer [iCopy] = (WCHAR) aBuffer [iCopy];
            wprintf(L"%lc\n", uBuffer [iCopy]);
        }
        WriteOK = WriteFile(hOut, uBuffer, 2 * nIn, &nOut, NULL);
        CloseHandle(hIn);
        CloseHandle(hOut);
        printf("%d", 23);
        return WriteOK;
    }
}