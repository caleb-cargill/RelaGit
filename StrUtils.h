#pragma once
#include <string>
#include <algorithm>
using namespace std;

string toLower(const string& str)
{
    string out = str;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}