#include <config_reader.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

ifstream config_file;
map<string, string> config;
int open_config(string config_file_name){
    config_file = ifstream(config_file_name);
    if(!config_file.is_open()){
        cerr << "Couldn't open the config file (" << config_file_name << ") for reading.\n" << endl;
        return false;
    }

    string line;
    while(getline(config_file, line)){
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if(line[0] == '#' || line.empty()) continue;

        auto delimiterPosition = line.find("=");
        auto propertyName = line.substr(0, delimiterPosition);
        auto propertyValue = line.substr(delimiterPosition + 1);

        config[propertyName] = propertyValue;
    }

    return true;
};

int close_config(){
    if(!config_file.is_open()){
        cerr << "Couldn't close the config file for closing.\n" << endl;
        return false;
    }

    config_file.close();
    return true;
};

string get_property(string propertyName){
    if(!config_file.is_open()){
        cerr << "You don't have opened the config file !\n" << endl;
        return NULL;
    }

    if(config.find(propertyName) == config.end()){
        cerr << "This property (" << propertyName << ") don't exist." << endl;
        return NULL;
    }

    return config[propertyName];
};
