@echo off
setlocal
cd /d "%~dp0"

if not exist "structures\blackredtree.cpp" (
    echo [ERROR] structures\*.cpp not found.
    echo Put build.bat in the folder with main.cpp, commands.cpp and structures\.
    exit /b 1
)

set SRC=main.cpp commands.cpp structures\array.cpp structures\slist.cpp structures\dlist.cpp structures\stack.cpp structures\queue.cpp structures\blackredtree.cpp

where g++ >nul 2>nul
if not errorlevel 1 (
    g++ -std=c++17 -Wall -Istructures %SRC% -o dbms.exe
    if errorlevel 1 (
        echo [FAIL] g++ build failed.
        exit /b 1
    )
    echo [OK] dbms.exe built with g++
    exit /b 0
)

where cl >nul 2>nul
if not errorlevel 1 (
    cl /nologo /std:c++17 /EHsc /utf-8 /Istructures %SRC% /Fe:dbms.exe
    if errorlevel 1 (
        echo [FAIL] cl build failed.
        exit /b 1
    )
    del /q *.obj 2>nul
    echo [OK] dbms.exe built with cl
    exit /b 0
)

echo [ERROR] No g++ and no cl found in PATH.
echo Install MinGW-w64 (e.g. w64devkit or MSYS2) or Visual Studio Build Tools.
exit /b 1
