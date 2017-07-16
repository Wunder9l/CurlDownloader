#include "curl_downloader.h"
#include "InputHandler.h"

int main(int argc, char *argv[])
{
    InputHandler inputHandler;
    if (0x01 < argc) {
        ostringstream stream;
        for (int i = 0x01; i < argc; ++i) {
            stream << argv[i] << ((argc - 1 == i) ? "\n" : " ");
        }
        if (false == inputHandler.ProcessLine(stream.str(), false)) {
            PrintHelp(argv[0x00]);
            inputHandler.Finish();
            return EXIT_FAILURE;
        }
    }

    inputHandler.WorkCycle();
    return EXIT_SUCCESS;
}

