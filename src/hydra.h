#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <curl/curl.h>

typedef struct {
  CURL *curl;
  FILE *file;
  char *url;
  char *filename;
} HydraDownload;

int hydra_init();

HydraDownload *hydra_download();

int hydra_download_start(HydraDownload* hd);

/*
Callback from CURL when data is available for processing.
Userdata is expected to be pointer to file (FILE*).
Writes data to file.
DOC: https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
*/
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

/*
Callback from CURL when header is available for processing.
Userdata is irrelevant.
Figures out file name from HTTP header.
DOC: https://curl.haxx.se/libcurl/c/CURLOPT_HEADERFUNCTION.html
*/
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata);
