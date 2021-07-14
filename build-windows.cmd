@ECHO OFF
set PATH=%PATH%;%CD%\MinGW\x86_64-w64-mingw32\lib
%CD%\MinGW\bin\g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\main.cpp -o %CD%\obj\src\main.o
%CD%\MinGW\bin\g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\headers\colors.cpp -o obj\src\headers\colors.o
%CD%\MinGW\bin\g++.exe -Wall -fexceptions -O2 -I%CD%\src\headers -c %CD%\src\headers\config_reader.cpp -o obj\src\headers\config_reader.o

%CD%\MinGW\bin\g++.exe -o %CD%\bin\Set-DNS-CLI-32.exe %CD%\obj\src\headers\colors.o %CD%\obj\src\headers\config_reader.o %CD%\obj\src\main.o -s -static -static-libstdc++ -static-libgcc
%CD%\mt.exe -nologo -manifest "%CD%\Set-DNS-CLI.manifest" -outputresource:"%CD%\bin\Set-DNS-CLI.exe";1
copy "%CD%\config.cfg" "%CD%\bin" > nul

echo Finished !
pause
