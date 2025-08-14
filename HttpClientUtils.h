#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

size_t ProcessResponse(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void Init() {
    curl_global_init(CURL_GLOBAL_ALL);
}

void CleanUp() {
    curl_global_cleanup();
}

string SendRequest(const string& prompt) {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    string jsonData = R"({
        "model": "llama3",
        "stream": false,
        "prompt": 
    )";
    jsonData += prompt;
    jsonData += "\n}";

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:11434/api/generate");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ProcessResponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;            
        } else {
            cout << "Ollama response: " << readBuffer << endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return readBuffer;
}