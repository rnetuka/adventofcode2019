//
// Created by rnetuka on 21.12.19.
//

#include "springdroid.h"

using namespace std;


springscript::springscript(const initializer_list<string>& commands)
{
    for (const string& command : commands)
        this->commands.push_back(command + "\n");
}

char springscript::operator()()
{
    string command = commands[i];
    char c = command[j];
    if (c == '\n') {
        i++;
        j = 0;
    }
    else {
        j++;
    }
    return c;
}