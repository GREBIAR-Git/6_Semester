/*При наличии в командной строке запуска программы имени одного или
нескольких файлов программа перенаправляет их содержимое на экран.
Если имя файла отсутствует, данные вводятся с клавиатуры и перенаправляются на экран */
#include "EvryThng.h"
#define BUF_SIZE 0x200
VOID CatFile (HANDLE, HANDLE);
DWORD Options (int argc, LPCTSTR argv [], LPCTSTR OptStr, ...)
/* argv - командная строка. Опции, начинающиеся с '-', если они есть,
помещаются в argv [1], argv [2], ....
OptStr - текстовая строка, содержащая все возможные опции во взаимно-однозначном соответствии с адресами булевых переменных в списке параметров-переменных (...). Эти флаги устанавливаются тогда и
только тогда, когда символ соответствующей опции встречается в argv
[1], argv [2], ...
Возвращаемое значение - индекс в argv первого параметра, не принадлежащего к опциям. */
{
    va_list pFlagList;
    LPBOOL pFlag;
    int iFlag = 0, iArg;
    va_start (pFlagList, OptStr) ;
    while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL && iFlag < (int)_tcslen (OptStr))
    {
        *pFlag = FALSE;
        for (iArg = 1; !(*pFlag) && iArg < argc && argv [iArg] [0] == '-';iArg++)
        *pFlag = memchr (argv [iArg], OptStr [iFlag],
        _tcslen (argv [iArg])) != NULL;
        iFlag++;
    }
    va_end (pFlagList);
    for (iArg = 1; iArg < argc && argv [iArg] [0] == '-'; iArg++);
    return iArg;
}

VOID ReportError (LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg)
/*Универсальная функция для сообщения о системных ошибках. */
{
    DWORD eMsgLen, LastErr = GetLastError ();
    LPTSTR lpvSysMsg;
    HANDLE hStdErr = GetStdHandle (STD_ERROR_HANDLE);
    PrintMsg (hStdErr, UserMessage);
    if (PrintErrorMsg)
    {
        eMsgLen = FormatMessage
        (FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM, NULL, LastErr,
        MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpvSysMsg, 0, NULL);
        PrintStrings (hStdErr, _T ("\n"), lpvSysMsg, _T ("\n"), NULL);
        /* Освобождаем блок памяти, содержащий сообщение об ошибке. */
        HeapFree (GetProcessHeap (), 0, lpvSysMsg);
    }
    if (ExitCode > 0)
        ExitProcess (ExitCode);
    else
        return;
}

BOOL PrintStrings (HANDLE hOut,...)
{
    /* Записывает сообщения в дескриптор вывода. */
    DWORD MsgLen, Count;
    LPCTSTR pMsg;
    va_list pMsgList; /* Текущая строка сообщения. */
    va_start (pMsgList, hOut); /* Начало обработки сообщений. */
    while ((pMsg = va_arg (pMsgList, LPCTSTR)) != NULL)
    {
        MsgLen = _tcslen (pMsg);
        /* WriteConsole работает только с дескрипторами консоли. */
        if (!WriteConsole (hOut, pMsg, MsgLen, &Count, NULL)
        /* Вызываем WriteFile только при неудаче WriteConsole */
        && !WriteFile (hOut, pMsg, MsgLen * sizeof (TCHAR), &Count, NULL))
            return FALSE;
    }
    va_end (pMsgList);
    return TRUE;
}

BOOL PrintMsg (HANDLE hOut, LPCTSTR pMsg)
/* Версия PrintStrings для одного сообщения. */
{
    return PrintStrings (hOut, pMsg, NULL);
}

int _tmain (int argc, LPCSTR argv [])
{
    HANDLE hInFile, hStdIn = GetStdHandle (STD_INPUT_HANDLE);
    HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
    BOOL DashS;
    int iArg, iFirstFile;
    /* DashS устанавливается, только если указана опция -s. */
    /* iFirstFile - индекс первого входного файла в argv []. */
    iFirstFile = Options (argc, argv, _T ("s"), &DashS, NULL);
    if (iFirstFile == argc)
    {
        /* В списке аргументов нет файлов. */
        /* Используется стандартный ввод. */
        CatFile (hStdIn, hStdOut);
        return 0;
    }

    /* Обрабатываем каждый входной файл. */
    for (iArg = iFirstFile; iArg < argc; iArg++)
    {
        hInFile = CreateFile (argv [iArg], GENERIC_READ,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hInFile ==INVALID_HANDLE_VALUE && !DashS)
            ReportError (_T ("Cat - ошибка открытия файла"), 1, TRUE);
        CatFile (hInFile, hStdOut);
        CloseHandle (hInFile);
    }
    return 0;
}

/* Функция, которая непосредственно выполняет работу:
читает входные данные и копирует их в стандартный вывод. */
VOID CatFile (HANDLE hInFile, HANDLE hOutFile)
{
    DWORD nIn, nOut;
    BYTE Buffer [BUF_SIZE];
    while (ReadFile (hInFile, Buffer, BUF_SIZE, &nIn, NULL)
    && (nIn != 0)
    && WriteFile (hOutFile, Buffer, nIn, &nOut, NULL)) ;
    return;
}