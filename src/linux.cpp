void dns_preset(string adapter, string name){
    if(name == ""){
        cout << "\n" << "Syntax : dns-preset [name]" << endl;
        cout << "Example : dns-preset cloudflare" << endl;
        return;
    }

    string primary_ip = get_property(name + "_primary");
    string secondary_ip = get_property(name + "_secondary");

    string current_primary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n1 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");
    string current_secondary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n2 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");
    if(current_primary_dns == current_secondary_dns){
        int primary_dns = system(("sed 's/" + current_primary_dns + "/" + primary_ip + "/g'"));
        int secondary_dns = primary_dns;
    } else{
        int primary_dns = system(("sed 's/" + current_primary_dns + "/" + primary_ip + "/g'"));
        int secondary_dns = system(("sed 's/" + current_secondary_dns + "/" + secondary_ip + "/g'"));
    }

    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};

void dhcp(string adapter){
    string current_primary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n1 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");
    string current_secondary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n2 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");
    string dhcp_dns = execute("ip r | grep -i '^default' | head -n1 | cut -d ' ' -f3");

    if(current_primary_dns == current_secondary_dns){
        int dhcp = system(("sed 's/" + current_primary_dns + "/" + dhcp_dns + "/g'"));
    } else{
        int dhcp = system(("sed 's/" + current_primary_dns + "/" + dhcp_dns + "/g'"));
        dhcp = system(("sed 's/" + current_secondary_dns + "/" + dhcp_dns + "/g'"));
    }

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

    string current_primary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n1 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");
    string current_secondary_dns = execute("cat /etc/resolv.conf | grep -i '^nameserver' | head -n2 | tail -1 | cut -d ' ' -f2  > /dev/null 2>&1");

    if(current_primary_dns == current_secondary_dns){
        int primary_dns = system(("sed 's/" + current_primary_dns + "/" + primary_ip + "/g'"));
        int secondary_dns = primary_dns;
    } else{
        int primary_dns = system(("sed 's/" + current_primary_dns + "/" + primary_ip + "/g'"));
        int secondary_dns = system(("sed 's/" + current_secondary_dns + "/" + secondary_ip + "/g'"));
    }

    if(!primary_dns || !secondary_dns){
        cout << background("light-green", "Successfully applied the changes ! Exiting the program...") << endl;
        exit(0);
    } else{
        cout << background("light-red", "An error has occured ! Exiting the program...") << endl;
        exit(1);
    }
};
