#pragma once
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

string toLower(const string& str)
{
    string out = str;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        return ""; // string is all whitespace
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, last - first + 1);
}