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
        getline(stream, line);
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

template <>
vector<long long> read_csv_input(const string& path)
{
    ifstream stream { path };

    vector<long long> result;

    string token;
    while (getline(stream, token, ','))
        result.push_back(stol(token));

    stream.close();
    return result;
}

string read_file(const string& path)
{
    ifstream stream { path };
    string result;

    while (stream)
    {
        string line;
        getline(stream, line);
        result += line;
        result += "\n";
    }
    return result;
}