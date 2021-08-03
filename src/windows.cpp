void dns_preset(string adapter, string name){
    if(name == ""){
        cout << "\n" << "Syntax : dns-preset [name]" << endl;
        cout << "Example : dns-preset cloudflare" << endl;
        return;
    }

    string primary_ip = get_property(name + "_primary");
    string secondary_ip = get_property(name + "_secondary");

    int primary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + primary_ip + " index=1 > nul 2>&1").c_str());
    int secondary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + secondary_ip + " index=2 > nul 2>&1").c_str());
    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void dhcp(string adapter){
    int dhcp = system(("netsh interface ipv4 set dnsservers " + adapter + " dhcp > nul 2>&1").c_str());
    if(!dhcp){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void custom(string adapter, string primary_ip, string secondary_ip){
    if(primary_ip == "" || secondary_ip == ""){
        cout << "\n" << "Syntax : custom [primary-ip] [secondary-ip]" << endl;
        cout << "Example : custom 8.8.8.8 8.8.4.4" << endl;
        return;
    }

    int primary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + primary_ip + " index=1 > nul 2>&1").c_str());
    int secondary_dns = system(("netsh interface ipv4 add dnsserver " + adapter + " " + secondary_ip + " index=2 > nul 2>&1").c_str());
    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};
