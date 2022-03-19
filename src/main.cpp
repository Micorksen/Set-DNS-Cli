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

/** #ifdef _WIN32
#include <windows.h>
#include "os/windows.cpp"
#elif __APPLE__
#include <TargetConditionals.h>
#include "os/apple.cpp"
#elif linux
#include "os/linux.cpp"
#endif **/

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
