#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include "StrUtils.h"
#include "ConsoleUtils.h"
#include "NaturalLangToGit.h"
#include "HardCodedToGit.h"
#include "OllamaToGit.h"
#include "HttpClientUtils.h"

using namespace std;

void showMenu();

void showChatOptions();

int main(int argc, char* argv[]) 
{

    if (argc < 2) {
        cerr << "Usage: rgit \"your plain english git command\" or rgit -h for additional help\n";
        return 1;
    }

    bool runCommands = false;
    bool requestHelp = false;
    bool chatMode = false;
    string command = "";

    cout << endl;
    for (int i = 0; i < argc; i++) {        
        string arg = argv[i];

        if (arg == "run") {
            runCommands = true;
        } else if (arg == "-help" || arg == "-h") {
            requestHelp = true;
        } else if (arg == "chat") {
            chatMode = true;
        } else {
            command = arg;
        }
    }

    if (requestHelp) {
        showMenu();
        return 0;
    }

    Init();
    
    OllamaToGit processorImp;
    NaturalLangToGit *processor = &processorImp;

    if (!chatMode) {
        cout << "Processing Request..." << endl;
        vector<string> commands = processor->extractCommands(command);
        processor->runCommands(commands, !runCommands);
    } else {
        cout << endl << "Entering Chat Mode" << endl;
        bool showOptions = true;
        while (chatMode) {
            if (showOptions) showChatOptions();
            showOptions = false;
            string request;
            getline(cin, request);
            if (request == "exit") {
                chatMode = false;                
            } else {
                if (request == "clear") {
                    system("cls");
                    showOptions = true;
                } else if (request == "new") {
                    processor->clearMemory();
                } else if (request == "run") {
                    vector<string> commands = processor->getPreviousCommands();
                    processor->runCommands(commands, false);
                } else if (isStringInQuotes(request)) {
                    vector<string> commands = processor->extractCommands(request);
                    processor->runCommands(commands, true);
                } else {
                    cout << "Input could not be processed." << endl;
                }
            }
        }
    }

    CleanUp();

    return 0;
}

void showMenu() {
    cout << endl;
    cout << R"(usage: rgit [-h | -help] [<commands>] ["Your Natural Language Command"])";
    cout << endl << endl;
    cout << "These are common rgit commands used in various situations: ";
    cout << endl << endl;
    cout << "To receive commands based on a natural language input:" << endl;
    cout << "\trgit \"Your request\"";
    cout << endl << endl;
    cout << "To enter chat mode with extended context" << endl;
    cout << "\trgit chat";
    cout << endl << endl;
    cout << "To request rgit to run generated commands based on a natural language input:" << endl;
    cout << "\trgit run \"Your request\"";
    cout << endl << endl;
}

void showChatOptions() {
    cout << "Enter a command or request:" << endl;
    cout << "Commands: " << endl;
    cout << "\texit\tExits the program" << endl;
    cout << "\tclear\tClears the console output" << endl;
    cout << "\tnew\tClears the chat context" << endl;
    cout << "\trun\tRuns the last set of generated commands" << endl;
    cout << "Request syntax: " << endl;
    cout << "\t\"Your natural language request\"" << endl;
}