#include "EvryThng.h"

int _tmain (int argc, LPTSTR argv [])
{
    BOOL Output;

    HINSTANCE hDLL = LoadLibrary("dll.dll");
    BOOL (*dllFunc)();
    dllFunc = (BOOL (*)())GetProcAddress(hDLL, "Asc2Un");

    if (hDLL != NULL)
    {
        if (dllFunc != NULL)
        {
            Output=dllFunc(argv [1], argv [2], FALSE);
        }
        FreeLibrary(hDLL);
    }

    return 0;
}