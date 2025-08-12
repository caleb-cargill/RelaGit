#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void runCommand(const string& cmd) {
    cout << "> " << cmd << endl;
    int result = system(cmd.c_str());
    if (result != 0) {
        cerr << "Command Failed: " << cmd << endl;
    }
}

string getInput(const string& message) {
    cout << message;
    string input;
    getline(cin, input);
    return input;
}