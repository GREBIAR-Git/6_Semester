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
/* Определения всех символьных констант и служебных функций общего применения для всех программ примеров. */ 
/* ЛУЧШЕ ОПРЕДЕЛИТЬ СИМВОЛЫ UTILITY_EXPORTS И
_STATICLIB HE ЗДЕСЬ, А В ПРОЕКТЕ, ОДНАКО ИХ ОПИСАНИЯ
ПРИВОДЯТСЯ ЗДЕСЬ. */ 
/* Символ "UTILITY_EXPORTS" генерируется в Dev Studio при создании проекта DLL с именем "Utility" и определяется в командной строке
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