#pragma once
#include<iostream>
#include<string>
#include<curl\curl.h>

using namespace std;

size_t dl_req_reply(void* buffer, size_t size, size_t nmemb, void* user_p);
CURLcode dl_curl_get_req(const std::string& url, std::string filename);