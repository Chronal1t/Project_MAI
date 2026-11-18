@echo off
setlocal

REM
set SRC=src
set THIRD=third_party
set OUT=taskmanager.exe

REM 
set SOURCES=%SRC%\main.cpp %SRC%\tasks.cpp %SRC%\http.cpp

REM  Компиляция 
cl /nologo /std:c++17 /EHsc /O2 /W3 /wd4996 /wd4267 ^
   /Fe:%OUT% ^
   %SOURCES% ^
   %THIRD%\sqlite3.c ^
   /link ws2_32.lib

if errorlevel 1 (
    echo.
    echo BUILD FAILED
    exit /b 1
)
echo.
echo BUILD OK: %OUT%
endlocal