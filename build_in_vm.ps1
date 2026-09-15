$vmrun = 'C:\Program Files\VMware\VMware Workstation\vmrun.exe'
$vmx = 'E:\Virtual Machines\Windows XP Media Center\Windows XP Media Center.vmx'
$hostDir = 'e:\BACKUP CHIAVETTA PRIMA DI METTERE TINY10\SAVING FOR PLEASURE\cleangtasa_samp\samp_025'
$guestDir = 'C:\projects\samp_025'

Write-Host 1. Copying files to guest VM...
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\build_exact.bat $guestDir\build_exact.bat
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\d3dhook\IDirect3DDevice9Hook.cpp $guestDir\client\d3dhook\IDirect3DDevice9Hook.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\game\game.cpp $guestDir\client\game\game.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\game\game.h $guestDir\client\game\game.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\netrpc.cpp $guestDir\client\net\netrpc.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\netgame.cpp $guestDir\client\net\netgame.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\netgame.h $guestDir\client\net\netgame.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\localplayer.cpp $guestDir\client\net\localplayer.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\localplayer.h $guestDir\client\net\localplayer.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\remoteplayer.cpp $guestDir\client\net\remoteplayer.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\remoteplayer.h $guestDir\client\net\remoteplayer.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\chatwindow.cpp $guestDir\client\chatwindow.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\chatwindow.h $guestDir\client\chatwindow.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\scoreboard.cpp $guestDir\client\scoreboard.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\scoreboard.h $guestDir\client\scoreboard.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\vehiclepool.h $guestDir\client\net\vehiclepool.h
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\net\vehiclepool.cpp $guestDir\client\net\vehiclepool.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\game\vehicle.cpp $guestDir\client\game\vehicle.cpp
& $vmrun -T ws -gu yello -gp password CopyFileFromHostToGuest $vmx $hostDir\client\game\vehicle.h $guestDir\client\game\vehicle.h

Write-Host 2. Running build in guest VM...
$cmdArg = '/c cd ' + $guestDir + ' && call build_exact.bat > build_exact.log 2>&1'
& $vmrun -T ws -gu yello -gp password runProgramInGuest $vmx 'C:\WINDOWS\system32\cmd.exe' $cmdArg

Write-Host 3. Retrieving build log...
& $vmrun -T ws -gu yello -gp password CopyFileFromGuestToHost $vmx $guestDir\build_exact.log $hostDir\build_vm.log

Write-Host 4. Retrieving samp.dll...
& $vmrun -T ws -gu yello -gp password CopyFileFromGuestToHost $vmx $guestDir\client\bin\samp.dll $hostDir\client\bin\samp.dll

Write-Host 5. Deploying samp.dll to game directories...
Copy-Item "$hostDir\client\bin\samp.dll" "e:\BACKUP CHIAVETTA PRIMA DI METTERE TINY10\SAVING FOR PLEASURE\cleangtasa_sampc\samp.dll" -Force
Copy-Item "$hostDir\client\bin\samp.dll" "e:\BACKUP CHIAVETTA PRIMA DI METTERE TINY10\SAVING FOR PLEASURE\cleangtasa_samp\samp.dll" -Force

Write-Host Done!
