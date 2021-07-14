#include <iostream>
#include <config_reader.h>
#include <colors.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <TargetConditionals.h>
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

void dns_preset(string name){
    if(name == ""){
        cout << "\n" << "Syntax : dns-preset [name]" << endl;
        cout << "Example : dns-preset cloudflare" << endl;
        return;
    }

    string primary_ip = get_property(name + "_primary");
    string secondary_ip = get_property(name + "_secondary");

    #ifdef _WIN32
    int primary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + primary_ip + " index=1").c_str());
    int secondary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + secondary_ip + " index=2").c_str());
    #elif TARGET_OS_MAC
    int primary_dns = system(("networksetup -setdnsservers \"" + adapter + "\" " + primary_ip + " " + secondary_ip).c_str());
    int secondary_dns = primary_dns;
    #endif

    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void dhcp(){
    #ifdef _WIN32
    int dhcp = system(("netsh interface ipv4 set dnsservers " + adapter + " dhcp").c_str());
    #elif TARGET_OS_MAC
    int dhcp = system(("networksetup -setdhcp \"" + adapter + "\"").c_str());
    #endif

    if(!dhcp){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void custom(string primary_ip, string secondary_ip){
    if(primary_ip == "" || secondary_ip == ""){
        cout << "\n" << "Syntax : custom [primary-ip] [secondary-ip]" << endl;
        cout << "Example : custom 8.8.8.8 8.8.4.4" << endl;
        return;
    }

    #ifdef _WIN32
    int primary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + primary_ip + " index=1").c_str());
    int secondary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + secondary_ip + " index=2").c_str());
    #elif TARGET_OS_MAC
    int primary_dns = system(("networksetup -setdnsservers \"" + adapter + "\" " + primary_ip + " " + secondary_ip).c_str());
    int secondary_dns = primary_dns;
    #endif

    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void removeStringTrailingNewLine(char *str){
    if(str == NULL) return;
    int length = strlen(str);
    if(str[length - 1] == '\n') str[length - 1] = '\0';
}

int main(int argc, char * argv[]){
    #ifdef _WIN32
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
    string interface = execute("route get one.one.one.one | grep interface");
    adapter = interface.substr(interface.find(":") + 1);
    #endif

    open_config("config.cfg");

    bool is_beta = (get_property("beta") == "true" ? true : false);
    cout << "Set-DNS-CLI [version " << get_property("version") << (is_beta ? "-BETA" : "") << "]" << endl;
    cout << "(c) Matteo C. Licensed with MIT license.\n" << endl;
    if(is_beta) cout << background("yellow", "You are running in beta version. If you find a bug / problem, open an issue on GitHub.") << endl;

    if(argc >= 2){
        if(string(argv[1]) == "dns-preset") dns_preset((argv[2] ?: ""));
        else if(string(argv[1]) == "dhcp") dhcp();
        else if(string(argv[1]) == "custom") custom((argv[2] ?: ""), (argv[3] ?: ""));
        else help();
    } else help();

    return 0;
}
