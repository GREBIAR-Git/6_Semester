tasklist /fi "ImageName eq a.exe" /fo csv 2>NUL | find /I "a.exe">NUL
if "%ERRORLEVEL%"=="0" taskkill /IM a.exe
IF EXIST "a.exe" (
del "a.exe"
)
gcc 1.c -lgdi32 -lpsapi -DPSAPI_VERSION=1
IF EXIST "a.exe" (
start a.exe
) ELSE (
PAUSE
)