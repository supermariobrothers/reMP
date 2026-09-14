@echo off
setlocal enabledelayedexpansion
call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
cd /d C:\projects\samp_025\client
if not exist obj mkdir obj
if not exist bin mkdir bin
del /q obj\*.obj >nul 2>&1
copy /y "C:\projects\independent_samp\vendor\dxsdk\lib\*.lib" "d3d9\" >nul 2>&1
set INCLUDES=/I"." /I".." /I"..\raknet" /I"..\raknet\samp" /Id3d9\include
set DEFINES=/D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "WIN32_LEAN_AND_MEAN" /D "RAKSAMP_CLIENT" /D "_RAKNET_THREADSAFE" /D "_CRT_SECURE_NO_WARNINGS"
set CFLAGS=/nologo /MD /W3 /GX /O2 %DEFINES% %INCLUDES% /c
cl %CFLAGS% /Fo"obj\game_font.obj" "game\font.cpp"
cl %CFLAGS% /Fo"obj\gui_font.obj" "gui\font.cpp"
cl %CFLAGS% /Fo"obj\\" "..\raknet\AsynchronousFileIO.cpp" "..\raknet\BitStream.cpp" "..\raknet\BitStream_NoTemplate.cpp" "..\raknet\CheckSum.cpp" "..\raknet\DataBlockEncryptor.cpp" "..\raknet\DataCompressor.cpp" "..\raknet\DS_ByteQueue.cpp" "..\raknet\DS_HuffmanEncodingTree.cpp" "..\raknet\DS_Table.cpp" "..\raknet\EncodeClassName.cpp" "..\raknet\GetTime.cpp" "..\raknet\InternalPacketPool.cpp" "..\raknet\LinuxStrings.cpp" "..\raknet\NetworkIDGenerator.cpp" "..\raknet\NetworkTypes.cpp" "..\raknet\PluginInterface.cpp" "..\raknet\RakClient.cpp" "..\raknet\RakNetStatistics.cpp" "..\raknet\RakNetworkFactory.cpp" "..\raknet\RakPeer.cpp"
cl %CFLAGS% /Fo"obj\\" "..\raknet\rakserver.cpp" "..\raknet\RakSleep.cpp" "..\raknet\Rand.cpp" "..\raknet\ReliabilityLayer.cpp" "..\raknet\rijndael.cpp" "..\raknet\RPCMap.cpp" "..\raknet\SAMP\SAMPRPC.cpp" "..\raknet\SAMP\samp_auth.cpp" "..\raknet\SAMP\samp_netencr.cpp" "..\raknet\SHA1.cpp" "..\raknet\SimpleMutex.cpp" "..\raknet\SocketLayer.cpp" "..\raknet\StringCompressor.cpp" "..\raknet\StringTable.cpp" "..\raknet\SystemAddressList.cpp" "..\raknet\TableSerializer.cpp" "..\raknet\_findfirst.cpp" "chatwindow.cpp" "cmdprocs.cpp" "cmdwindow.cpp" "colorembed.cpp"
cl %CFLAGS% /Fo"obj\\" "d3d9\common\dxstdafx.cpp" "d3d9\common\DXUT.cpp" "d3d9\common\DXUTenum.cpp" "d3d9\common\DXUTgui.cpp" "d3d9\common\DXUTMesh.cpp" "d3d9\common\DXUTmisc.cpp" "d3d9\common\DXUTSettingsDlg.cpp" "d3dhook\IDirect3DDevice9Hook.cpp" "deathwindow.cpp" "events.cpp" "exceptions.cpp" "fontrender.cpp" "game\actorped.cpp" "game\aimstuff.cpp" "game\camera.cpp" "game\cheats.cpp" "game\debug.cpp" "game\entity.cpp" "game\game.cpp" "game\hooks.cpp"
cl %CFLAGS% /Fo"obj\\" "game\keystuff.cpp" "game\menu.cpp" "game\object.cpp" "game\patches.cpp" "game\playerped.cpp" "game\scripting.cpp" "game\task.cpp" "game\textdraw.cpp" "game\util.cpp" "game\vehicle.cpp" "gui\fontmanager.cpp" "gui\stateblockmanager.cpp" "gui\textbuffer.cpp" "gui\textbufferbase.cpp" "gui\texture.cpp" "helpdialog.cpp" "label.cpp" "main.cpp" "md5.cpp" "netstats.cpp"
cl %CFLAGS% /Fo"obj\\" "net\actorpool.cpp" "net\gangzonepool.cpp" "net\localplayer.cpp" "net\menupool.cpp" "net\netgame.cpp" "net\netrpc.cpp" "net\objectpool.cpp" "net\pickuppool.cpp" "net\playerpool.cpp" "net\remoteactor.cpp" "net\remoteplayer.cpp" "net\scriptrpc.cpp" "net\textdrawpool.cpp" "net\vehiclepool.cpp" "newplayertags.cpp" "playertags.cpp" "runutil.cpp" "scoreboard.cpp" "spawnscreen.cpp" "subclass.cpp"
cl %CFLAGS% /Fo"obj\\" "svrnetstats.cpp"
echo Linking samp.dll...
link /nologo /DLL /OUT:bin\samp.dll /LIBPATH:d3d9 /LIBPATH:"C:\projects\independent_samp\vendor\dxsdk\lib" obj\*.obj ws2_32.lib comctl32.lib d3d9.lib d3dx9.lib dxguid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib
if errorlevel 1 (
    echo [ERROR] Link failed!
    exit /b 1
)
echo [SUCCESS] samp.dll built successfully!
dir bin\samp.dll
