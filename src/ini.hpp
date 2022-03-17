// Copyright (c) Micorksen and contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
// Based from StackOverflow (question #127819).

#ifndef INI_HPP_
#define INI_HPP_

#include <string>
#include <unordered_map>
#include <list>

using namespace std;
struct section{
    string name;
    unordered_map<string, string> keyValues;
}

class ini{
    public:
        ini(const string& fileName);
        section* get_section(const string& sectionName);
        list<section>& get_sections();
        string get_value(const string& sectionName, const string& keyName);
    private:
        void parse(const string& fileName);
        list<sections> sections;
}
#endif