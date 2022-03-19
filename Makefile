# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

.PHONY: apple linux windows test

PROGRAM=Set-DNS-Cli
CC=g++
CPPFLAGS=-s -static -static-libstdc++ -static-libgcc -I.

apple: src/os/apple.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM).apple.sh \
		src/os/apple.cpp \
		src/main.cpp && \
	chmod +x $(PROGRAM).apple.sh
	
linux: src/os/linux.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM).linux.sh \
		src/os/linux.cpp \
		src/main.cpp && \
	chmod +x $(PROGRAM).linux.sh
	
windows: src/os/windows.cpp src/main.cpp
	$(CC) $(CPPFLAGS) -o $(PROGRAM).exe \
		src/os/windows.cpp \
		src/main.cpp

test: $(PROGRAM).apple.sh $(PROGRAM).linux.sh $(PROGRAM).exe
	./$(PROGRAM).apple.sh > /dev/null 2>&1
	./$(PROGRAM).linux.sh > /dev/null 2>&1
	./$(PROGRAM).exe > /dev/null 2>&1
