#include <string>
#include <iostream>
#include <colors.h>
using namespace std;

string foreground(string color, string text){
    if(text.empty()) cerr << "Sorry, you need to provide text to color." << endl;

    if(color == "black") return "\033[30m" + text + "\033[0m";
    else if(color == "red") return "\033[31m" + text + "\033[0m";
    else if(color == "green") return "\033[32m" + text + "\033[0m";
    else if(color == "yellow") return "\033[33m" + text + "\033[0m";
    else if(color == "blue") return "\033[34m" + text + "\033[0m";
    else if(color == "magenta") return "\033[35m" + text + "\033[0m";
    else if(color == "cyan") return "\033[36m" + text + "\033[0m";
    else if(color == "light-gray") return "\033[37m" + text + "\033[0m";
    else if(color == "gray") return "\033[90m" + text + "\033[0m";
    else if(color == "light-red") return "\033[91m" + text + "\033[0m";
    else if(color == "light-green") return "\033[92m" + text + "\033[0m";
    else if(color == "light-yellow") return "\033[93m" + text + "\033[0m";
    else if(color == "light-blue") return "\033[94m" + text + "\033[0m";
    else if(color == "light-magenta") return "\033[95m" + text + "\033[0m";
    else if(color == "light-cyan") return "\033[96m" + text + "\033[0m";
    else if(color == "white") return "\033[97m" + text + "\033[0m";
    else{
        cerr << "Sorry, you need to provide an existing color." << endl;
        return NULL;
    }
};

string background(string color, string text){
    if(text.empty()) cerr << "Sorry, you need to provide text to color." << endl;

    if(color == "black") return "\033[40m" + text + "\033[0m";
    else if(color == "red") return "\033[41m" + text + "\033[0m";
    else if(color == "green") return "\033[42m" + text + "\033[0m";
    else if(color == "yellow") return "\033[43m" + text + "\033[0m";
    else if(color == "blue") return "\033[44m" + text + "\033[0m";
    else if(color == "magenta") return "\033[45m" + text + "\033[0m";
    else if(color =="cyan") return "\033[46m" + text + "\033[0m";
    else if(color == "light-gray") return "\033[47m" + text + "\033[0m";
    else if(color == "gray") return "\033[100m" + text + "\033[0m";
    else if(color == "light-red") return "\033[101m" + text + "\033[0m";
    else if(color == "light-green") return "\033[102m" + text + "\033[0m";
    else if(color == "light-yellow") return "\033[103m" + text + "\033[0m";
    else if(color == "light-blue") return "\033[104m" + text + "\033[0m";
    else if(color == "light-magenta") return "\033[105m" + text + "\033[0m";
    else if(color == "light-cyan") return "\033[106m" + text + "\033[0m";
    else if(color == "white") return "\033[107m" + text + "\033[0m";
    else{
        cerr << "Sorry, you need to provide an existing color." << endl;
        return NULL;
    }
};

string style(string style, string text){
    if(text.empty()) cerr << "Sorry, you need to provide text to style." << endl;

    if(style == "bold") return "\033[1m" + text + "\033[0m";
    else if(style == "underline") return "\033[4m" + text + "\033[0m";
    else{
        cerr << "Sorry, you need to provide an existing style." << endl;
        return NULL;
    }
};
