#pragma once
#include <iostream>
#include <string>

#define CURL_STATICLIB
#include "curl\curl.h"

#define HELP_MESSAGE 

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

using namespace std;
bool download_one_file(const char* url, const char* filename);
void PrintInteractiveModeHelp();
void PrintHelp(const char* programName);