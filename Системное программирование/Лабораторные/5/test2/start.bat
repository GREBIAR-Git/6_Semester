gcc -c dll.c
gcc -shared -o dll.dll dll.o

tasklist /fi "ImageName eq a.exe" /fo csv 2>NUL | find /I "a.exe">NUL
if "%ERRORLEVEL%"=="0" taskkill /IM a.exe
IF EXIST "a.exe" (
del "a.exe"
)

gcc 1.c -L./ -ldll -w

.\a.exe
PAUSE