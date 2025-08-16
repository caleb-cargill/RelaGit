#pragma once
#include <string>
#include <vector>
#include "ConsoleUtils.h"
using namespace std;

class NaturalLangToGit {
    public:
        virtual vector<string> extractCommands(const string& input) = 0;
        virtual bool isRequestPreview(const string& input) = 0;
        void runCommands(vector<string> commands, bool isPreview) {
            for (const string& cmd : commands)
            {
                if (!isPreview)
                {
                    runCommand(cmd);
                }
                else 
                {
                    cout << cmd << endl;
                }
            }
        }
        void processCommand(const string& command) {
            vector<string> commands = extractCommands(command);
            bool isPreview = isRequestPreview(command);
            runCommands(commands, isPreview);
        }
};