/******************************************************
 * Copyright (c) 2022 Micorksen.
 * 
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 ******************************************************/

#include <iostream>
#include "../os-functions.h"

int isAdministrator() {
    return !system("cat /etc/resolv.conf > /dev/null 2>&1");
}

std::string getAdapter() {
    std::string interface = OS::execute("route get one.one.one.one | grep interface");
    return interface.substr(interface.find(":") + 1);
}

int setCustomDNS(std::string primary_ip, std::string secondary_ip) {
    std::string adapter = getAdapter();
    int primary_ip_setted = !system("networksetup -setdnsservers " + adapter + " " + primary_ip);
    int secondary_ip_setted = -1;

    if (secondary_ip != "") {
        int secondary_ip_setted = !system("networksetup -setdnsservers " + adapter + " " + primary_ip + " " + secondary_ip);
    }

    if (!primary_ip_setted || secondary_ip_setted == 0) {
        return 0;
    }

    return 1;
}

int useDHCP() {
    return !system("networksetup -setdnsservers " + getAdapter());
}