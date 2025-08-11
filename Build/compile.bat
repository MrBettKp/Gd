@echo off
SETLOCAL

:: Configuration
SET BUILD_DIR=..\build
SET SRC_DIR=..\src
SET COMPILER=cl.exe
SET CPP_FLAGS=/EHsc /std:c++17 /I..\include /O2

:: Create build directory if not exists
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

:: Compile main application
echo Compiling main application...
%COMPILER% %CPP_FLAGS% %SRC_DIR%\main.cpp %SRC_DIR%\MemoryReader\*.cpp %SRC_DIR%\DataProcessing\*.cpp /Fe:%BUILD_DIR%\GameDashboard.exe

:: Verify compilation
if %errorlevel% equ 0 (
    echo Build successful! Output: %BUILD_DIR%\GameDashboard.exe
) else (
    echo Build failed with error %errorlevel%
)

ENDLOCAL
