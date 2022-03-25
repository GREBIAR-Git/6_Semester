#include "EvryThng.h" 
_declspec (dllimport) 
BOOL Asc2Un(LPCTSTR, LPСTSTR, BOOL); 
int _tmain (int argc, LPTSTR argv []) 
{ 
37 
BOOL Output; 
/* Вызываем функцию. */ 
Output=Asc2Un(argv [1], argv [2], FALSE); 
return 0; 
} 