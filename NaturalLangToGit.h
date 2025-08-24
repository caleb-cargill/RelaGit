#pragma once
#include <string>
#include <vector>
#include "ConsoleUtils.h"
using namespace std;

class NaturalLangToGit {
    protected: 
        vector<string> lastSetOfCommands;
    public:
        virtual vector<string> extractCommands(const string& input) = 0;      
        
        virtual void clearMemory() = 0;

        vector<string> getPreviousCommands() {
            return lastSetOfCommands;
        }

        void runCommands(vector<string> commands, bool isPreview) {
            cout << endl;
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

        void processCommand(const string& command, bool isPreview) {
            vector<string> commands = extractCommands(command);
            runCommands(commands, isPreview);
        }
};