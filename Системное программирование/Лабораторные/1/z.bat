IF EXIST "a.exe" (
del "a.exe"
)
copy /y NUL 2.txt
g++ 1.cpp
.\a
PAUSE