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

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        cerr << "Usage: relagit \"your plain english git command\"\n";
        return 1;
    }
    
    string command = argv[1];

    HardCodedToGit processorImp;
    NaturalLangToGit *processor = &processorImp;

    vector<string> commands = processor->extractCommands(command);
    bool isPreview = processor->isRequestPreview(command);

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

    return 0;
}