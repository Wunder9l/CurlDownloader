#include "InputHandler.h"



InputHandler::InputHandler()
{
    active = true;
}


InputHandler::~InputHandler()
{
}

bool InputHandler::ProcessLine(string line, bool verbose)
{
    istringstream stringStream(line);
    vector<string> tokens{ istream_iterator<string>{stringStream},istream_iterator<string>{} };
    ostringstream errorStream;

    if (0x01 == tokens.size()) {
        if (0x00 == tokens.front().compare("finish")) {
            Finish();
        }
        else {
            errorStream << "Invalid command: " << tokens.front() << endl;
        }
    }
    else if (0x02 == tokens.size()) {
        string option = tokens.front();
        if (0x00 == option.compare("-a")) {
            downloadManager.AddUrl(tokens[0x01]);
        }
        else if (0x00 == option.compare("-f"))
        {
            downloadManager.AddUrlFromFile(tokens[0x01]);
        }
        else
        {
            errorStream << "Invalid option: " << tokens.front() << endl;
        }
    }

    if (false == errorStream.str().empty()) {
        cout << errorStream.str();
        if (verbose) {
            PrintInteractiveModeHelp();
        }
        return false;
    }
    return true;
}

void InputHandler::Finish()
{
    downloadManager.Finish();
    active = false;
}

void InputHandler::WorkCycle()
{
    cout << "Interactive mode enabled" << endl;
    PrintInteractiveModeHelp();

    string nextLine;
    while (active) {
        getline(cin, nextLine);
        ProcessLine(nextLine);
    }
}
