#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cstdlib>

void runCommand(const std::string& cmd)
{
    std::cout << "> " << cmd << std::endl;
    int result = std::system(cmd.c_str());
    if (result != 0) 
    {
        std::cerr << "Command failed: " << cmd << std::endl;
    }
}

std::string toLower(const std::string& str)
{
    std::string out = str;
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

std::string getCommitMessage() 
{
    std::cout << "Enter a commit message: ";
    std::string message;
    std::getline(std::cin, message);
    return message;
}

std::vector<std::string> parseCommand(const std::string& inputRaw)
{
    std::string input = toLower(inputRaw);
    std::vector<std::string> commands;

    if (input.find("help") != std::string::npos)
    {
        commands.push_back("git help");
    }

    return commands;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        std::cerr << "Usage: relagit \"your plain english git command\"\n";
        return 1;
    }
    
    std::string command = argv[1];
    bool isPreview = false;
    for (int i = 2; i < argc; i++)
    {
        std::string arg = toLower(argv[i]);
        std::cout << arg << std::endl;
        isPreview = (arg.find("-preview") != std::string::npos);
    }


    std::vector<std::string> commands = parseCommand(command);

    for (const std::string& cmd : commands)
    {
        if (!isPreview)
        {
            runCommand(cmd);
        }
        else 
        {
            std::cout << cmd << std::endl;
        }
    }

    return 0;
}