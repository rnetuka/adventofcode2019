//
// Created by rnetuka on 03.12.19.
//

#include <fstream>

#include "utils.h"

using namespace std;

template <>
vector<string> read_lines(const string& path)
{
    ifstream stream { path };

    vector<string> values;

    while (stream)
    {
        string line;
        stream >> line;
        if (! line.empty())
            values.push_back(line);
    }
    stream.close();
    return values;
}

template <>
vector<int> read_lines(const string& path)
{
    ifstream stream { path };

    vector<int> values;

    while (stream)
    {
        string line;
        stream >> line;
        if (! line.empty())
            values.push_back(stoi(line));
    }
    stream.close();
    return values;
}

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

template <>
vector<int> read_csv_input(const string& path)
{
    ifstream stream { path };

    vector<int> result;

    string token;
    while (getline(stream, token, ','))
        result.push_back(stoi(token));

    stream.close();
    return result;
}