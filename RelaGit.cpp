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

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        cerr << "Usage: relagit \"your plain english git command\"\n";
        return 1;
    }

    Init();
    
    string command = argv[1];

    OllamaToGit processorImp;
    NaturalLangToGit *processor = &processorImp;

    vector<string> commands = processor->extractCommands(command);
    bool isPreview = processor->isRequestPreview(command);
    processor->runCommands(commands, true);

    CleanUp();

    return 0;
}