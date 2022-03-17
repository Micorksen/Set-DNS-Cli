// Copyright (c) Micorksen and contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
// Based from StackOverflow (question #127819).

#include "ini.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <list>

using namespace std;

// Trim leading white-spaces.
static string& ltrim(string& str){
    size_t startPosition = str.find_first_not_of(" \t\r\n\v\f");
    if(string::npos != startPosition) str = str.substr(startPosition);
    return str;
}

// Trim trailing white-spaces.
static string& rtrim(string& str){
    size_t endPosition = str.find_last_not_of(" \t\r\n\v\f");
    if(string::npos != endPosition) str = str.substr(0, endPosition + 1);
    return str;
}

ini::ini(const string& filename){ parse(filename); }
section* ini::get_section(const string& sectionName){
    list<section>::iterator found = find_if(sections.begin(), sections.end(), [sectionName](const section& section){ return section.name.compare(sectionName) == 0; });
    return found != sections.end() ? &*found : NULL;
}

list<section>& ini::get_sections(){ return sections; }
section* ini::get_value(const string& sectionName, const string& keyName){
    section* section = get_section(sectionName);
    if(section != NULL){
        unordered_map<string, string>::const_iterator iterator = section->keyValues.find(keyName);
        if(iterator != section->keyValues.end()) return iterator->second;
    }

    return "";
}

void ini::parse(const string& filename){
    section currentSection;
    ifstream fileStream;
    fileStream.open(filename);

    if(!fileStream) throw invalid_argument(filename + " could not be opened.");
    for(string line; getline(fileStream, line)){
        // If the line is a comment, do nothing.
        if(!line.empty() && (line[0] == ";" || line[0] == "#")){}
        else if(line[0] == "["){
            // A "[Section]" line.
            size_t end = line.find_first_of("]");
            if(end != string::npos){
                // This is a new section. So, if we have a current section populated, add it to list.
                if(!currentSection.name.empty()){
                    sections.push_back(currentSection);
                    currentSection.name.clear();
                    currentSection.keyValues.clear();
                }

                currentSection.name = line.substr(1, end - 1);
            } else{}
        } else if(!line.empty()){
            // Not a comment, must be a name[=:]value pair.
            size_t end = line.find_first_of("=:");
            if(end != string::npos){
                string name = line.substr(0, end);
                string value = line.substr(end + 1);

                ltrim(rtim(name));
                ltrim(rtim(value));
                currentSection.keyValues[name] = value;
            } else{}
        }
    }

    // If we are out of loop, we add last section.
    // This is a new section, so if we have a current section populated, add it to list.
    if(!currentSection.name.empty()){
        sections.push_back(currentSection);
        currentSection.name = "";
        currentSection.keyValues.clear();
    }
}
