#include "DownloadManager.h"
#include "curl_downloader.h"


DownloadManager::DownloadManager()
{
    workingThread = thread(&DownloadManager::WorkingThreadFunction, this);
    active = true;
}


DownloadManager::~DownloadManager()
{
}

void DownloadManager::Push(const string& value)
{
    unique_lock<mutex> mlock(queueMutex);
    asyncQueue.push(value);
    mlock.unlock();
    conditionVar.notify_one();
}

string DownloadManager::Pop()
{
    unique_lock<mutex> mlock(queueMutex);
    while (asyncQueue.empty())
    {
        conditionVar.wait(mlock);
    }
    string item = asyncQueue.front();
    asyncQueue.pop();
    return item;
}

void DownloadManager::WorkingThreadFunction()
{
    while (true)
    {
        string nextUrl = Pop();
        if (nextUrl.empty()) {
            active = false;
            break;
        }
        else
        {
            string filename = GetFilename(nextUrl);
            download_one_file(nextUrl.c_str(), filename.c_str());
        }
    }
}

string DownloadManager::GetFilename(string url)
{
    size_t indexOfLastSlash = url.find_last_of('/');

    string filename = (string::npos == indexOfLastSlash) || (url.length() - 1 == indexOfLastSlash) ?
        url :
        url.substr(url.find_last_of('/') + 0x01);
    size_t len = filename.length();
    char* clearName = new char[len + 0x01];
    for (size_t index = 0x00; index < len; ++index) {
        clearName[index] = (IsSymbolAllowed(filename[index])) ? filename[index] : '_';
    }
    clearName[len] = '\0';
    string result(clearName);
    delete[]clearName;
    return result;
}

bool DownloadManager::IsSymbolAllowed(char symbol) {
    if ((('a' <= symbol) && ('z' >= symbol)) ||
        (('A' <= symbol) && ('Z' >= symbol)) ||
        (('0' <= symbol) && ('9' >= symbol)) ||
        ('.' == symbol) || ('_' == symbol) ||
        ('-' == symbol)
        ) {
        return true;
    }
    else
    {
        return false;
    }
}

void DownloadManager::Finish()
{
    if (active) {
        Push(string());
        workingThread.join();
    }
}

bool DownloadManager::AddUrl(string url)
{
    bool result = false;
    if (active)
    {
        if (false == url.empty()) {
            Push(url);
            result = true;
        }
        else
        {
            cout << "Can not add emtry url though AddUrl method, to finish work of DownloadManager use methed Finish" << endl;
        }
    }
    else
    {
        cout << "Working thread is not active, perhaps trying to add new url after Finish" << endl;
    }
    return result;
}

bool DownloadManager::AddUrlFromFile(string filename)
{
    bool result = false;

    if (filename.empty()) {
        cout << "Filename could not be empty" << endl;
    }
    else
    {
        ifstream filestream(filename);

        if (!filestream) {
            cout << "Cannot open input file: " << filename << endl;
        }
        else
        {
            string line;
            while (getline(filestream, line)) {
                cout << line << endl;
                Push(line);
                result = true;
            }
            filestream.close();
            if (false == result) {
                cout << "No line was added from file: " << filename << endl;
            }
        }
    }
    return result;
}
