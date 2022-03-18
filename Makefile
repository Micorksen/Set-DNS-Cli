# /*****************************************************
# * Copyright (c) 2022 Micorksen.
# * 
# * Use of this source code is governed by an MIT-style
# * license that can be found in the LICENSE file or at
# * https://opensource.org/licenses/MIT.
# * 
# ******************************************************/

build: src/main.cpp src/ini.cpp src/ini.hpp
  gcc -o Set-DNS-Cli src/main.cpp src/ini.cpp src/ini.hpp -I. && \
  ./Set-DNS-Cli
