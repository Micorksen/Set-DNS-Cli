/******************************************************
 * Copyright (c) 2022 Micorksen.
 * 
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 ******************************************************/

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include "vendor/INIReader/INIReader.h"
#include "vendor/http/httplib.h"
#include "vendor/rapidjson/document.h"
#include "os-functions.h"

void help() {
    std::cout << "Syntax : [custom|dns-preset|dhcp]"
              << std::endl;

    std::cout << "Examples : "
              << std::endl;

    std::cout << "- custom 8.8.8.8 8.8.4.4"
              << std::endl;

    std::cout << "- dns-preset cloudflare"
              << std::endl;
}

int main(int argc, char * argv[]) {
    INIReader config = OS::readConfig();
    std::string version = "1.1";
    std::string vendor = config.GetString("Updater", "Vendor", "");
    std::string owner = config.GetString("Updater", "Owner", "Micorksen");
    std::string repository = config.GetString("Updater", "Repository", "Set-DNS-CLI");

    std::cout << "Set-DNS-Cli [version "
              << version << "]"
              << std::endl;

    std::cout << "(c) " << (vendor != "" ? vendor + " (original version by Micorksen)" : "Micorksen") << ". All rights reserved."
              << std::endl
              << "\n";

    if (config.GetBoolean("Updater", "CheckUpdates", true)) {
        httplib::Client ghAPI("https://api.github.com");
        httplib::Result response = ghAPI.Get(
                "/repos/"
                + owner + "/" + repository
                + "/releases"
        );

        if (response->status != 200) {
            std::cerr << "Cannot fetch the releases..."
                      << "\n"
                      << std::endl;
        } else {
            rapidjson::Document releases;
            releases.Parse(response->body.c_str());

            std::string ghLatestVersion = ((std::string) releases[0]["tag_name"].GetString()).replace(0, 1, "");
            if (std::stod(ghLatestVersion) > std::stod(version)) {
                std::cout << "A newer version is available."
                          << "\nYou can download it at https://github.com/"
                          << owner + "/" + repository
                          << "/releases/tag/v" << ghLatestVersion
                          << "\n"
                          << std::endl;
            }
        }
    }

    if (!isAdministrator()) {
        std::cout << "You need administrator privileges to run this program."
                  << std::endl;

        return 1;
    }

    if (argc >= 2) {
        std::string command(argv[1]);
        if (command == "custom") {
            if (!argv[1]) {
                std::cout << "Syntax : custom [primary] (secondary)"
                          << std::endl;

                return 0;
            }

            if (argv[2]) {
                int result = setCustomDNS(std::string(argv[1]), std::string(argv[2]));
                if (!result) {
                    std::cerr << "An error has occurred when running this command."
                              << std::endl;

                    return 1;
                }
            }

            int result = setCustomDNS(std::string(argv[1]));
            if (!result) {
                std::cerr << "An error has occurred when running this command."
                          << std::endl;

                return 1;
            }
        } else if (command == "dns-preset") {
            if (!argv[1]) {
                std::cout << "Syntax : dns-preset [name]"
                          << std::endl;

                return 0;
            }

            int result = OS::setDNSPreset(argv[1]);
            if (!result) {
                std::cerr << "An error has occurred when running this command."
                          << std::endl;

                return 1;
            }
        } else if (command == "dhcp") {
            int result = useDHCP();
            if (!result) {
                std::cerr << "An error has occurred when running this command."
                          << std::endl;

                return 1;
            }
        } else {
            help();
            return 0;
        }
    } else {
        help();
    }

    return 0;
}
