# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

build: src/main.cpp src/ini.cpp
	gcc -o Set-DNS-Cli src/main.cpp src/ini.cpp -s -static -static-libstdc++ -static-libgcc -I. && \
	chmod +x Set-DNS-Cli && \
	./Set-DNS-Cli
