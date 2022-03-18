# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

build: src/main.cpp src/ini.cpp src/os/windows.cpp src/os/apple.cpp src/os/linux.cpp src/os-functions.h
	g++ -o Set-DNS-Cli -s -static -static-libstdc++ -static-libgcc -I. \
		src/main.cpp \
		src/ini.cpp \
		src/os/windows.cpp \
		src/os/apple.cpp \
		src/os/linux.cpp \
		src/os-functions.h && \
	chmod +x Set-DNS-Cli && \
	./Set-DNS-Cli
