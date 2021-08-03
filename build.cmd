@ECHO OFF
set PATH=%PATH%;%CD%\MinGW\x86_64-w64-mingw32\lib;%CD%\MinGW\bin;C:\Program Files\7-Zip
g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\main.cpp -o %CD%\obj\src\main.o
g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\headers\colors.cpp -o obj\src\headers\colors.o
g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\headers\config_reader.cpp -o obj\src\headers\config_reader.o

g++.exe -o %CD%\bin\Set-DNS-CLI.exe %CD%\obj\src\headers\colors.o %CD%\obj\src\headers\config_reader.o %CD%\obj\src\main.o -s -static -static-libstdc++ -static-libgcc
g++.exe -o %CD%\bin\Set-DNS-CLI %CD%\obj\src\headers\colors.o %CD%\obj\src\headers\config_reader.o %CD%\obj\src\main.o -s -static -static-libstdc++ -static-libgcc
copy "%CD%\config.cfg" "%CD%\bin" > nul 2>&1

cd %CD%\bin
7z a %CD%\github\Set-DNS-CLI-windows-x64.zip Set-DNS-CLI.exe config.cfg > nul 2>&1
7z a %CD%\github\Set-DNS-CLI-linux-x64.zip Set-DNS-CLI config.cfg > nul 2>&1
copy "%CD%\github\Set-DNS-CLI-linux-x64.zip" "%CD%\github\Set-DNS-CLI-macos-x64.zip" > nul 2>&1

cd ../
echo Finished !
pause
