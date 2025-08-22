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

        string promptOllama(const string& input) {
            string body = getRequestBody(input);        
            string response = SendRequest(requestUrl, body);

            json j = json::parse(response);
            cout << "Response: " << j["response"] << endl;
            cout << "Context: " << j["context"] << endl;

            return j["response"];
        }

        bool isRequestPreview(const string& input) {
            string args = toLower(input);
            return args.find("preview") != string::npos;
        }

        string getRequestBody(const string& input) {
            string prompt;
            prompt = "Please give me the git commands to accomplish this: ";
            prompt += input;
            string body = R"({
                "model": "llama3",
                "stream": false,
                "system": "You are a Senior Developer and expert on Git. Respond with a semi-colon separated list of Git commands to accomplish the prompt. Provide the commands only, and no other context.",
                "prompt": )";
            body.append('\"' + prompt + '\"' + "\n}");
            return body;
        }
};