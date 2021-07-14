#ifndef CONFIG_READER_H
#define CONFIG_READER_H
#include <string>
using namespace std;

int open_config(string);
int close_config();
string get_property(string);
#endif
