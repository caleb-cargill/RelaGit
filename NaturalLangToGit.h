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
            if (isPreview) {
                cout << "Here are the requested commands: " << endl;
            } else {
                cout << "Running the commands..." << endl;
            }

            for (const string& cmd : commands)
            {
                if (!isPreview)
                {
                    runCommand(cmd);
                }
                else 
                {
                    cout << "\t" << cmd << endl;
                }
            }
        }

        void processCommand(const string& command) {
            vector<string> commands = extractCommands(command);
            bool isPreview = isRequestPreview(command);
            runCommands(commands, isPreview);
        }
};