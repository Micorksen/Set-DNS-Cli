/******************************************************
 * Copyright (c) 2022 Micorksen.
 * 
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 ******************************************************/

#include <iostream>
#include <cstring>
#include "vendor/INIReader/INIReader.h"

#ifndef OS_FUNCTIONS_H
#define OS_FUNCTIONS_H

int isAdministrator();
std::string getAdapter();
int setCustomDNS(std::string primary_ip, std::string secondary_ip = "");
int useDHCP();

class OS {
    public:
        static std::string execute(std::string command) {
            char buffer[128];
            std::string result;

            FILE *pipe = popen(command.c_str(), "r");
            if (!pipe) {
                std::cout << "Cannot execute a command." << std::endl;
                exit(1);
            }

            while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                result += buffer;
            }

            pclose(pipe);

            char *resultPtr = (char *) result.c_str();
            int length = std::strlen(resultPtr);
            if (resultPtr[length - 1] == '\n') {
                resultPtr[length - 1] = '\0';
            }

            return std::string(resultPtr);
        }

        static INIReader readConfig() {
            return INIReader("config.ini");
        }

        static int setDNSPreset(std::string name) {
            INIReader config = OS::readConfig();
            std::string preset_primary = config.GetString("DnsPresets", name + ".primary", "");
            std::string preset_secondary = config.GetString("DnsPresets", name + ".secondary", "");

            if (preset_primary == "") {
                std::cout << "Cannot use DNS preset without a primary IP." << std::endl;
                return 0;
            }

            return setCustomDNS(preset_primary, preset_secondary);
        }
};
#endif
