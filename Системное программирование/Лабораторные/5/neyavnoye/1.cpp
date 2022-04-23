#include "EvryThng.h"
#include "dll.h"

int _tmain (int argc, LPTSTR argv [])
{
    BOOL Output;
    /* Вызываем функцию. */
    Output=Asc2Un(argv [1], argv [2], FALSE);
    return 0;
}