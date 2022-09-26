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
	return OS::execute("id -u") == "0";
}

std::string getAdapter() {
    return OS::execute("ip r | awk '$1 == \"default\" {print $5}'");
}

int setCustomDNS(std::string primary_ip, std::string secondary_ip) {
    std::string current_primary = OS::execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n1 | tail -1 | cut -d ' ' -f2");
    std::string current_secondary = OS::execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n2 | tail -1 | cut -d ' ' -f2");

    int primary_ip_setted = !system(("sed -i 's/" + current_primary + "/" + primary_ip + "/g' /etc/resolv.conf").c_str());
    int secondary_ip_setted = -1;
    if (secondary_ip != "") {
        secondary_ip_setted = !system(("sed -i 's/" + current_secondary + "/" + secondary_ip + "/g' /etc/resolv.conf").c_str());
    }

    if (!primary_ip_setted || secondary_ip_setted == 0) {
        return 0;
    }

    return 1;
}

int useDHCP() {
    // Not supported on Linux, return a 0.
    return 0;
}