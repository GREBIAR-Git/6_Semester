gcc -c Asc2un.c -o dll.o -lgdi32
gcc -shared -o dll.dll dll.o

tasklist /fi "ImageName eq a.exe" /fo csv 2>NUL | find /I "a.exe">NUL
if "%ERRORLEVEL%"=="0" taskkill /IM a.exe
IF EXIST "a.exe" (
del "a.exe"
)

gcc 1.c -L./ -ldll -w -lgdi32

.\a.exe test1.txt test2.txt
PAUSE