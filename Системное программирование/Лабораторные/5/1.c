#include "EvryThng.h"

_declspec (dllimport)

BOOL Asc2Un(LPCTSTR, LPCTSTR, BOOL);

int _tmain (int argc, LPTSTR argv [])
{
    BOOL Output;
    /* Вызываем функцию. */
    Output=Asc2Un(argv [1], argv [2], FALSE);
    return 0;
}