#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "DownloadManager.h"
#include "curl_downloader.h"


using namespace std;
class InputHandler
{
private:
    bool active;
    DownloadManager downloadManager;


#pragma region __ Constructor and destructor __
public:
    InputHandler();
    ~InputHandler();
#pragma endregion

#pragma region __ Public methods __
public:
    bool ProcessLine(string line, bool verbose = true);
    void Finish();
    void WorkCycle();
#pragma endregion


#pragma region __ Private methods __
private:
#pragma endregion

};

