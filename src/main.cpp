/******************************************************
 * Copyright (c) 2022 Micorksen.
 * 
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 ******************************************************/

#include <iostream>
#include <string>
#include "os-functions.h"

/*#ifdef _WIN32
#include <windows.h>
#include "os/windows.cpp"
#elif __APPLE__
#include <TargetConditionals.h>
#include "os/apple.cpp"
#elif linux
#include "os/linux.cpp"
#endif*/

// Return result of command and remove trailing new lines.
string execute(string command){
    char buffer[128];
    string result = "";
    
    FILE* pipe = popen(command.c_str(), "r");
    if(!pipe) throw system_error("Cannot execute the command !");
    
    while(fgets(buffer, sizeof buffer, pipe) != NULL){ result += buffer; }
    pclose(pipe);
    
    int commandLength = strlen(command);
    if(command[commandLength - 1] == "\n") command[commandLength - 1] = "\0";
    return command;
}

using namespace std;
int main(int argc, char * argv[]){
    // Version output.
    cout << "Set-DNS-CLI" << endl;
    cout << "Copyright (c) Micorksen. All righnts reserved.\n" << endl;
    
    // Run OS functions.
    check_permission();
    get_adapter();
    
    return 0;
}
