IF EXIST "a.exe" (
del "a.exe"
)
gcc 1.c -lgdi32 -w
.\a
PAUSE