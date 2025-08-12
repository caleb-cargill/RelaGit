#pragma once
#include <string>
#include <vector>
using namespace std;

class NaturalLangToGit {
    public:
        virtual vector<string> extractCommands(const string& input) = 0;
        virtual bool isRequestPreview(const string& input) = 0;
};