//Директивы препроцессора
#include "stdafx.h"
//#include "EvryThng.h"
//Далее приводится текст библиотеки «EvryThng.h»
#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN
#define NOATOM
#define NOCLIPBOARD
#define NOCOMM
#define NOCTLMGR
#define NOCOLOR
#define NODEFERWINDOWPOS
#define NODESKTOP
#define NODRAWTEXT
#define NOEXTAPI
#define NOGDICAPMASKS
#define NOHELP
15
#define NOICONS
#define NOTIME
#define NOIMM
#define NOKANJI
#define NOKERNEL
#define NOKEYSTATES
#define NOMCX
#define NOMEMMGR
#define NOMENUS
#define NOMETAFILE
#define NOMSG
#define NONCMESSAGE
#define NOPROFILER
#define NORASTEROPS
#define NORESOURCE
#define NOSCROLL
#define NOSERVICE
#define NOSHOWWINDOW
#define NOSOUND
#define NOSYSCOMMANDS
#define NOSYSMETRICS
#define NOSYSPARAMS
#define NOTEXTMETRIC
#define NOVIRTUALKEYCODES
#define NOWH
#define NOWINDOWSTATION
#define NOWINMESSAGES
#define NOWINOFFSETS
#define NOWINSTYLES
#define OEMRESOURCE
/* Envirmnt.h - определяются UNICODE _MT. */
/* Лучше и проще определить UNICODE в проекте. */
/* Вызовите команды Project... Settings ... C/C++ и в окне
Project Options внизу добавьте текст /D "UNICODE". */
 /* Сделайте то же для _МТ и _STATIC_LIB. */
//#define UNICODE
#undef UNICODE
#ifdef UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
16
#undef _UNICODE
#endif
//#define _MT
#define _STATICLIB
/* Определяйте _STATICLIB при формировании статической
библиотеки или компоновке с ней. */
//#undef_STATICLIB
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
/* "Support.h" */
/* Определения всех символьных констант и служебных функций общего применения для всех программ примеров. */
/* ЛУЧШЕ ОПРЕДЕЛИТЬ СИМВОЛЫ UTILITY_EXPORTS И
_STATICLIB HE ЗДЕСЬ, А В ПРОЕКТЕ, ОДНАКО ИХ ОПИСАНИЯ
ПРИВОДЯТСЯ ЗДЕСЬ. */
/* Символ "UTILITY_EXPORTS" генерируется в Dev Studio при создании проекта DLL с именем "Utility" и определяется в командной строке
С. */
//#define UTILITY_EXPORTS Закомментировано; определяйте
// этот символ в проекте.
#define UTILITY_EXPORTS
#ifdef UTILITY_EXPORTS
#define LIBSPEC _declspec (dllexport)
#else
#define LIBSPEC _declspec (dllimport)
#endif
#define EMPTY _T ("")
#define YES _T ("y")
#define NO _T ("n")
#define CR OxOD
#define LF OxOA
#define TSIZE sizeof (TCHAR)
/* Пределы и константы. */
#define TYPE_FILE 1 /* Используется в Is, rm и IsFP. */
#define TYPE_DIR 2
#define TYPE_DOT 3
17
#define MAX_OPTIONS 20
/* Максимальное кол-во опций командной строки. */
#define MAX_ARG 1000
/* Максимальное кол-во параметров командной строки. */
#define MAX_COMMAND_LINE MAX_PATH+50
/* Максимальный размер командной строки. */
/* Функции общего применения. */
LIBSPEC BOOL ConsolePrompt (LPCTSTR, LPTSTR, DWORD, BOOL);
LIBSPEC BOOL PrintStrings (HANDLE, ...);
LIBSPEC BOOL PrintMsg (HANDLE, LPCTSTR);
LIBSPEC VOID ReportError (LPCTSTR, DWORD, BOOL);
//Начало программы
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
while ((pFlag = va_arg (pFlagList, LPBOOL)) != NULL && iFlag < (int)
_tcslen (OptStr))
{
*pFlag = FALSE;
for (iArg = 1; !(*pFlag) && iArg < argc && argv [iArg] [0] = = '-';iArg++)
*pFlag = _memtchr (argv [iArg], OptStr [iFlag],
_tcslen (argv [iArg])) != NULL; iFlag++;
}
va_end (pFlagList);
18
for (iArg = 1; iArg < argc && argv [iArg] [0] = = '-'; iArg++);
return iArg;
}
int _tmain (int argc, LPTSTR argv [])
{
BOOL Flags [MAX_OPTIONS], ok = TRUE;
TCHAR PathName [MAX_PATH + 1], CurrPath [MAX_PATH + 1];
LPCTSTR pFileName;
int i, FileIndex;
FileIndex = Options (argc, argv, _T ("R1"), &Flags [0], &Flags[1],
&Flags[2], NULL);
/* "Разбор" образца поиска на "путь" и "имя файла" */
GetCurentDirectory (MAX_PATH, CurrPath);
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
SetCurrentDirectory (CurPath);
 /* Восстанавливаем каталог. */
}
return ok ? 0 : 1;
}
static BOOL TraverseDirectory (LPCTSTR PathName, DWORD NumFlags,
LPBOOL Flags)
/* Обход каталога; выполняем Processltem для каждого найденного
соответствия. */
/* PathName: относительный или абсолютный путь для обхода. */
{
HANDLE SearchHandle;
19
WIN32_FIND_DATA FindData;
BOOL Recursive = Flags [0];
DWORD FType, iPass;
TCHAR CurrPath [MAX_PATH +1];
GetCurrentDirectory (MAX_PATH, CurrPath) ;
for (iPass = 1; iPass <= 2; iPass++)
{
 /* 1-й проход: список файлов. */
 /* 2-й проход: обход каталогов (если указана опция -R). */
 SearchHandle = FindFirstFile (PathName, &FindData);
 do
 {
FType = FileType (&FindData); /* Файл или каталог? */
if (iPass ==1) /* Выводим имя и атрибуты. */
ProcessItem (&FindData, MAX_OPTIONS, Flags);
if (Type == TYPE_DIR && iPass == 2 && Recursive)
{
 /* Обрабатываем подкаталог. */
_tprintf (_T ("\n%s\\%s:"), CurrPath, FindData.cFileName);
 /* Подготовка к обходу каталога. */
SetCurrentDirectory (FindData.cFileName);
TraverseDirectory (_T ("*"), NumFlags, Flags);
/* Рекурсивный вызов. */
SetCurrentDirectory (_T ("."));
}
}
while (FindNextFile (SearchHandle, &FindData));
FindClose (SearchHandle);
}
return TRUE;
}
static BOOL ProcessItem (LPWIN32_FIND_DATA pFileData, DWORD
NumFlags, LPBOOL Flags)
/* Вывод атрибутов файла или каталога. */
{
const TCHAR FileTypeChar [] = {' ','d'};
DWORD FType = FileType (pFileData);
BOOL Long = Flags [1];
SYSTEMTIME LastWrite;
if (FType != TYPE_FILE && FType != TYPE_DIR) return FALSE;
20
_tprintf (_T ("\n"));
if (Long)
{
/* Указана ли в командной строке опция "-1"? */
 _tprintf (_T ("%c"), FileTypeChar [FType - 1]);
 _tprintf (_T ("%10d"), pFileData->nFileSizeLow) ;
FileTimeToSystemTime (&(pFileData->ftLastWriteTime),&LastWrite);
 _tprintf (_T (" %02d/%02d/%04d %02d:%02d:%02d "),
LastWrite.wMonth, LastWritewDay,
LastWrite.wYear, LastWrite.wHour,
LastWrite.wMinute, LastWrite.wSecond);
}
 _tprintf (_T ("%s"), pFileData->cFileName);
 return TRUE;
}
static DWORD FileType (LPWIN32_FIND_DATA pFileDta)
 /* Поддерживаемые типы: TYPE_FILE (файл);
TYPE_DIR (каталог); TYPE DOT (каталог . или .. */
{
BOOL IsDir;
DWORD FType;
FType = TYPE_FILE;
IsDir = (pFileData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
!= 0;
if (IsDir)
if (lstrcmp (pFileData->cFileName, _T (".")) = = 0
|| lstrcmp (pFileData->cFileName, _T ("..")) == 0)
 FType = TYPE_DOT;
else FType = TYPE_DIR;
return FType;
}