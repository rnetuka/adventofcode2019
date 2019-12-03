//
// Created by rnetuka on 03.12.19.
//

#include <fstream>

#include "utils.h"

using namespace std;


template <>
vector<string> read_csv_input(const string& path)
{
    ifstream stream { path };

    vector<string> result;

    string token;
    while (getline(stream, token, ','))
        result.push_back(token);

    stream.close();
    return result;
}