#include <iostream>
#include "config_reader.h"
#include "colors.h"
#include <string>

#ifdef _WIN32
#include <windows.h>
#include "windows.cpp"
#elif __APPLE__
#include <TargetConditionals.h>
#include "macos.cpp"
#elif linux
#include "linux.cpp"
#endif

using namespace std;
string adapter;

string execute(string command){
    char buffer[128];
    string result = "";

    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe){
        cerr << background("red", "Cannot execute the command ! Exiting the program...") << endl;
        exit(1);
    }

    while(fgets(buffer, sizeof buffer, pipe) != NULL){ result += buffer; }
    pclose(pipe);

    return result;
};

void help(){
    cout << "\n" << "Syntax : [dns-preset|dhcp|custom]" << endl;
    cout << "Examples : " << endl;
    cout << "- dns-preset cloudflare" << endl;
    cout << "- custom 8.8.8.8 8.8.4.4" << endl;
};

void removeStringTrailingNewLine(char *str){
    if(str == NULL) return;
    int length = strlen(str);
    if(str[length - 1] == '\n') str[length - 1] = '\0';
}

int main(int argc, char * argv[]){
    bool is_beta = (get_property("beta") == "true" ? true : false);
    cout << "Set-DNS-CLI [version " << get_property("version") << (is_beta ? "-BETA" : "") << "]" << endl;
    cout << "(c) Matteo C. Licensed with MIT license.\n" << endl;
    if(is_beta) cout << background("yellow", "You are running in beta version. If you find a bug / problem, open an issue on GitHub.") << endl;

    #ifdef _WIN32
    int permission = system("net session > nul 2>&1");
    if(permission){
        cout << background("light-red", "Sorry, you need to run the program with administrator privileges ! Exiting the program...") << endl;
        exit(1);
    }

    char ptr[100];
    strcpy(ptr, execute("powershell -command \"Get-NetIPAddress -AddressFamily IPv4 -InterfaceIndex (Get-NetRoute -DestinationPrefix 0.0.0.0/0 | Sort-Object -Property RouteMetric | Select-Object -ExpandProperty ifIndex) | Select-Object -ExpandProperty IPAddress\"").c_str());
    removeStringTrailingNewLine(ptr);
    string local_ip = string{ptr};

    strcpy(ptr, execute("powershell -command \"foreach($int in (gwmi Win32_NetworkAdapter)) {gwmi Win32_NetworkAdapterConfiguration -Filter \"\"\"Index = $($int.index)\"\"\" | ? {$_.IPAddress -contains '" + local_ip + "'} | % {$int.NetConnectionID} }\"").c_str());
    removeStringTrailingNewLine(ptr);
    adapter = string(ptr);

    DWORD consoleMode;
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &consoleMode);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), consoleMode | 0x0004);
    #elif TARGET_OS_MAC
    int permission = system("cat /etc/resolv.conf > /dev/null 2>&1");
    if(permission){
        cout << background("light-red", "Sorry, you need to run the program with administrator privileges ! Exiting the program...") << endl;
        exit(1);
    }

    string interface = execute("route get one.one.one.one | grep interface > /dev/null 2>&1");
    adapter = interface.substr(interface.find(":") + 1);
    #elif linux
    int permission = system("cat /etc/resolv.conf > /dev/null 2>&1");
    if(permission){
        cout << background("light-red", "Sorry, you need to run the program with administrator privileges ! Exiting the program...") << endl;
        exit(1);
    }

    adapter = execute("route -n | awk '$1 == "0.0.0.0" {print $8}'");
    #endif

    open_config("config.cfg");

    if(argc >= 2){
        if(string(argv[1]) == "dns-preset") dns_preset(adapter, (argv[2] ?: ""));
        else if(string(argv[1]) == "dhcp") dhcp(adapter);
        else if(string(argv[1]) == "custom") custom(adapter, (argv[2] ?: ""), (argv[3] ?: ""));
        else help();
    } else help();

    return 0;
}
