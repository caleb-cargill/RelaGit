#pragma once
#include <string>
#include <vector>
#include "StrUtils.h"
#include "NaturalLangToGit.h"

using namespace std;

class HardCodedToGit : public NaturalLangToGit {
    public:
        vector<string> extractCommands(const string& input) {
            string cleanedInput = toLower(input);
            vector<string> commands;

            if (cleanedInput.find("help") != string::npos)
            {
                commands.push_back("git help");
            }

            return commands;
        }
};