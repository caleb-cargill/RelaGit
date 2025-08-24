#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "NaturalLangToGit.h"
#include "HttpClientUtils.h"
#include "StrUtils.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

class OllamaToGit : public NaturalLangToGit {
    private: 
        const string requestUrl = "http://localhost:11434/api/generate";
        vector<int> previousContext;
    public: 
        vector<string> extractCommands(const string& input) {
            string response = promptOllama(input);
            stringstream ss(response);
            string command;
            vector<string> commands;

            while (getline(ss, command, ';')) {
                commands.push_back(trim(command));
            }

            return commands;
        }

        void clearMemory() {
            previousContext.clear();
        }

        string promptOllama(const string& input) {
            string body = getRequestBody(input);        
            string response = SendRequest(requestUrl, body);

            json j = json::parse(response);

            if (j.contains("context")) {
                previousContext = j["context"].get<vector<int>>();                
            }

            return j["response"];
        }

        string getRequestBody(const string& input) {
            string prompt = "Please give me the commands to accomplish this: " + input;
            json j;

            j["model"] = "llama3";
            j["stream"] = false;
            j["system"] = "You are a Senior Developer. You are a keyboard warrior, you can accomplish anything via the command line. Respond with a semi-colon separated list of commands to accomplish the prompt. Provide the commands only, and no other context.";
            j["prompt"] = prompt;

            if (!previousContext.empty()) {
                j["context"] = previousContext;
            }
            
            return j.dump();
        }
};