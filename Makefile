# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

.PHONY: build-apple build-linux build-windows

PROGRAM=Set-DNS-Cli
CC=g++
CPPFLAGS=-s -static -static-libstdc++ -static-libgcc -I.

build-apple: src/os/apple.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM) \
		src/os/apple.cpp
		src/main.cpp && \
	chmod +x Set-DNS-Cli && \
	./Set-DNS-Cli
	
build-linux: src/os/linux.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM) \
		src/os/linux.cpp \
		src/main.cpp && \
	chmod +x Set-DNS-Cli && \
	./Set-DNS-Cli
	
build-windows: src/os/windows.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM).exe \
		src/os/windows.cpp \
		src/main.cpp && \
	./Set-DNS-Cli.exe
