# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

build: src/os/windows.cpp src/os/apple.cpp src/os/linux.cpp src/os-functions.h src/main.cpp
	g++ -o Set-DNS-Cli -s -static -static-libstdc++ -static-libgcc -I. \
		src/os/windows.cpp \
		src/os/apple.cpp \
		src/os/linux.cpp \
		src/main.cpp && \
	chmod +x Set-DNS-Cli && \
	./Set-DNS-Cli
