/******************************************************
 * Copyright (c) 2022 Micorksen.
 * 
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 ******************************************************/

#include <iostream>
#include <string>
#include "../os-functions.h"

using namespace std;
void check_permission(){
	
};

string get_adapter(){
	char command[100];
	strcpy(command, execute("powershell -command \"Get-NetIPAddress -AddressFamily IPv4 -InterfaceIndex (Get-NetRoute -DestinationPrefix 0.0.0.0/0 | Sort-Object -Property RouteMetric | Select-Object -ExpandProperty ifIndex) | Select-Object -ExpandProperty IPAddress\"").c_str());
	string local_ip = string{command};
	
	strcpy(command, execute("powershell -command \"foreach($int in (gwmi Win32_NetworkAdapter)) {gwmi Win32_NetworkAdapterConfiguration -Filter \"\"\"Index = $($int.index)\"\"\" | ? {$_.IPAddress -contains '" + local_ip + "'} | % {$int.NetConnectionID} }\"").c_str());
	return string(command);
};
