//Директивы препроцессора
#include "EvryThng.h"
BOOL TraverseDirectory (LPCTSTR, DWORD, LPBOOL);
DWORD FileType (LPWIN32_FIND_DATA);
BOOL ProcessItem (LPWIN32_FIND_DATA, DWORD, LPBOOL);
DWORD Options (int argc, LPCTSTR argv [], LPCTSTR OptStr, ...) 
/* argv - командная строка. Опции, начинающиеся с '-', если они есть, 
помещаются в argv [1], argv [2], .... 
OptStr - текстовая строка, содержащая все возможные опции во взаимно-однозначном соответствии с адресами булевых переменных в списке
параметров-переменных (...). 
Эти флаги устанавливаются тогда и только тогда, когда символ соответствующей опции встречается в argv [I], argv [2], ... Возвращаемое
значение - индекс в argv первого параметра, не принадлежащего к опциям. */ 
{ 
    va_list pFlagList;
    LPBOOL pFlag;
    int iFlag = 0, iArg;
    va_start (pFlagList, OptStr) ;
    while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL && iFlag < (int)_tcslen (OptStr))
    {
        *pFlag = FALSE;
        for (iArg = 1; !(*pFlag) && iArg < argc && argv [iArg] [0] == '-';iArg++)
            *pFlag = memchr (argv [iArg], OptStr [iFlag],_tcslen (argv [iArg])) != NULL;
        iFlag++;
    }
    va_end (pFlagList);
    for (iArg = 1; iArg < argc && argv [iArg] [0] == '-'; iArg++);
    return iArg;
} 

int _tmain (int argc, LPCSTR argv [])
{
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    BOOL Flags [MAX_OPTIONS], ok = TRUE;
    TCHAR PathName [MAX_PATH + 1], CurrPath [MAX_PATH + 1];
    LPCTSTR pFileName;
    int i;
    int FileIndex;
    FileIndex = Options(argc, (argv), _T ("R1"), &Flags[0], &Flags[1],&Flags[2], NULL);
    GetCurrentDirectory(MAX_PATH, CurrPath);
    printf("argc=%d Index=%d\n",argc, FileIndex);
    printf("STR=%s \n",CurrPath); 
    /* Сохраняем текущий путь. */ 
    if (argc < FileIndex +1) 
    /* Путь не указан. Текущий каталог. */ 
        ok = TraverseDirectory (_T ("*"), MAX_OPTIONS, Flags);
    else 
        for (i = FileIndex; i < argc; i++) 
        { 
            /* Обрабатываем все пути в командной строке. */ 
            pFileName=argv[i];
            ok = TraverseDirectory (pFileName, MAX_OPTIONS, Flags) && ok;
            SetCurrentDirectory (pFileName);
            /* Восстанавливаем каталог. */ 
        } 
    return ok ? 0 : 1; 
} 

BOOL TraverseDirectory (LPCTSTR PathName, DWORD NumFlags,LPBOOL Flags)
/* Обход каталога; выполняем Processltem для каждого найденного
соответствия. */ 
/* PathName: относительный или абсолютный путь для обхода. */ 
{ 
    HANDLE SearchHandle;
    WIN32_FIND_DATA FindData;
    BOOL Recursive = Flags [0];
    DWORD FType, iPass;
    TCHAR CurrPath [MAX_PATH +1];
    SetCurrentDirectory (PathName) ;
    for (iPass = 1; iPass <= 2; iPass++)
    {
        /* 1-й проход: список файлов. */ 
        /* 2-й проход: обход каталогов (если указана опция -R). */ 
        SearchHandle = FindFirstFile (PathName, &FindData);
        do
        {
            FType = FileType (&FindData); /* Файл или каталог? */ 
            if (iPass ==1)  /* Выводим имя и атрибуты. */ 
                ProcessItem(&FindData, MAX_OPTIONS, Flags);
            if (FType == TYPE_DIR && iPass == 2 && Recursive)
            {
                /* Обрабатываем подкаталог. */ 
               _tprintf (_T ("\n\n%s:"), FindData.cFileName);
                /* Подготовка к обходу каталога. */ 
                SetCurrentDirectory (FindData.cFileName);
                TraverseDirectory (_T("*"), NumFlags, Flags);
                /* Рекурсивный вызов. */ 
                SetCurrentDirectory (_T("."));
            } 
        } 
        while (FindNextFile(SearchHandle, &FindData));
        FindClose (SearchHandle);
    } 
    return TRUE; 
} 

BOOL ProcessItem (LPWIN32_FIND_DATA pFileData, DWORD NumFlags, LPBOOL Flags)
/* Вывод атрибутов файла или каталога. */ 
{ 
    const TCHAR FileTypeChar [] = {' ','d'};
    DWORD FType = FileType (pFileData);
    BOOL Long = Flags [1];
    SYSTEMTIME LastWrite;
    if (FType != TYPE_FILE && FType != TYPE_DIR) return FALSE;
    _tprintf (_T ("\n"));
    if (Long)
    {
        /* Указана ли в командной строке опция "-1"? */ 
        _tprintf (_T ("%c"), FileTypeChar [FType - 1]);
        _tprintf (_T ("%d"), pFileData->nFileSizeLow) ;
        FileTimeToSystemTime (&(pFileData->ftLastWriteTime),&LastWrite);
        _tprintf (_T (" %d/%02d/%04d %02d:%02d:%02d "),
        LastWrite.wMonth, LastWrite.wDay,
        LastWrite.wYear, LastWrite.wHour,
        LastWrite.wMinute, LastWrite.wSecond);
    } 
    _tprintf (_T ("%s"), pFileData->cFileName);
    return TRUE; 
} 

DWORD FileType (LPWIN32_FIND_DATA pFileData)
 /* Поддерживаемые типы: TYPE_FILE (файл); 
TYPE_DIR (каталог); TYPE DOT (каталог . или .. */ 
{ 
    BOOL IsDir;
    DWORD FType;
    FType = TYPE_FILE;
    IsDir = (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    if (IsDir)
        if (lstrcmp (pFileData->cFileName, _T (".")) == 0 || lstrcmp (pFileData->cFileName, _T ("..")) == 0)
            FType = TYPE_DOT;
        else 
            FType = TYPE_DIR;
    return FType;
} 