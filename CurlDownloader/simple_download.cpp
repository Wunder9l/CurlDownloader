#include "curl_downloader.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

bool download_one_file(const char* url, const char* filename) {
    CURL *curl_handle;
    FILE *file;

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get here */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);

    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

    /* disable progress meter, set to 0L to enable and disable debug output */
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the file */
    errno_t err_open = fopen_s(&file, filename, "wb");
    if (0x00 == err_open) {

        /* write the page body to this file handle */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, file);

        /* get it! */
        curl_easy_perform(curl_handle);

        /* close the header file */
        fclose(file);
    }
    else
    {
        cout << "Could not open file for saving: " << filename << endl;
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    return 0;
}