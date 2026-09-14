@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo  Building SA-MP 0.2.5 Client DLL with MSVC 7.1 (VS 2003)
echo ========================================================

call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
if errorlevel 1 (
    echo [ERROR] Failed to initialize VS 2003 environment.
    exit /b 1
)

cd /d C:\projects\samp_025\client

if not exist obj mkdir obj
if not exist bin mkdir bin

copy /y "C:\projects\independent_samp\vendor\dxsdk\lib\*.lib" "d3d9\" >nul 2>&1

set INCLUDES=/I"." /I".." /I"..\raknet" /I"..\raknet\samp" /I"d3d9\include"
set DEFINES=/D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "WIN32_LEAN_AND_MEAN" /D "RAKSAMP_CLIENT" /D "_RAKNET_THREADSAFE" /D "_CRT_SECURE_NO_WARNINGS"

set CFLAGS=/nologo /MD /W3 /GX /O2 %DEFINES% %INCLUDES% /c /Fo"obj\\"

echo Compiling RakNet...
cl %CFLAGS% ..\raknet\*.cpp ..\raknet\SAMP\*.cpp

echo Compiling Game...
cl %CFLAGS% game\*.cpp

echo Compiling GUI and Net...
cl %CFLAGS% gui\*.cpp net\*.cpp

echo Compiling D3D...
cl %CFLAGS% d3d9\common\*.cpp d3dhook\*.cpp

echo Compiling Client Main...
cl %CFLAGS% *.cpp

echo Linking samp.dll...
link /nologo /DLL /OUT:bin\samp.dll /LIBPATH:d3d9 /LIBPATH:"C:\projects\independent_samp\vendor\dxsdk\lib" obj\*.obj ws2_32.lib comctl32.lib d3d9.lib d3dx9.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib

if errorlevel 1 (
    echo [ERROR] Link failed!
    exit /b 1
)

echo [SUCCESS] samp.dll built successfully!
dir bin\samp.dll
