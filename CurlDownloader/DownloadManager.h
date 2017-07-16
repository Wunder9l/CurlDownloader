#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>

using namespace std;

class DownloadManager
{
private:
    queue<string>  asyncQueue;
    mutex queueMutex;
    condition_variable conditionVar;
    thread workingThread;
    bool active;

#pragma region __ Constructor and desc=tructor __
public:
    DownloadManager();
    ~DownloadManager();
#pragma endregion

#pragma region __ Private methods __
private:
    void Push(const string& value);
    string Pop();
    void WorkingThreadFunction();
    bool IsSymbolAllowed(char symbol);
    string GetFilename(string url);
#pragma endregion

#pragma region __ Public methods __
public:
    void Finish();
    bool AddUrl(string url);
    bool AddUrlFromFile(string filename);
#pragma endregion

};

