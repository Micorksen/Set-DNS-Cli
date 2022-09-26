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
	return !system("net session > nul 2>&1");
}

std::string getAdapter() {
    std::string local_ip = OS::execute("powershell -command \"Get-NetIPAddress -AddressFamily IPv4 -InterfaceIndex (Get-NetRoute -DestinationPrefix 0.0.0.0/0 | Sort-Object -Property RouteMetric | Select-Object -ExpandProperty ifIndex) | Select-Object -ExpandProperty IPAddress\"");
    return OS::execute("powershell -command \"foreach($int in (gwmi Win32_NetworkAdapter)) {gwmi Win32_NetworkAdapterConfiguration -Filter \"\"\"Index = $($int.index)\"\"\" | ? {$_.IPAddress -contains '" + local_ip + "'} | % {$int.NetConnectionID} }\"");
}

int setCustomDNS(std::string primary_ip, std::string secondary_ip) {
    std::string adapter = getAdapter();
    int primary_ip_setted = !system("netsh interface ipv4 add dnsservers " + adapter + " " + primary_ip + " index=1 > nul 2>&1");
    int secondary_ip_setted = -1;

    if (secondary_ip != "") {
        int secondary_ip_setted = !system("netsh interface ipv4 add dnsservers " + adapter + " " + secondary_ip + " index=2 > nul 2>&1");
    }

    if (!primary_ip_setted || secondary_ip_setted == 0) {
        return 0;
    }

    return 1;
}

int useDHCP() {
    return !system("netsh interface ipv4 set dnsserver " + getAdapter() + " dhcp > nul 2>&1");
}