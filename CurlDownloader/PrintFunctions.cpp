#include "curl_downloader.h"

void PrintInteractiveModeHelp() {
    cout << "\nIn the interactive mode you can input the following commands\n\t"
        << "-a <http://example.com/filename> (to add an url to download\n\t"
        << "-f <filename> (to add a filename that contains a list of urls to download\n"
        << "finish (to say that there is no additional url, the program will finish existing downloads and exit)\n\t"
        << endl;
}

void PrintHelp(const char* programName) {
    cout << "Usage:\n\t"
        << programName << " (to start a program without any argument and input urls from console\n\t"
        << programName << " -a <http://example.com/filename> (to start a program with initial url to download\n\t"
        << programName << " -f <filename> (to start a program with initial filename that contains a list of urls to download\n" << endl;
}