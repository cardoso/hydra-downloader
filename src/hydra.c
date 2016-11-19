/* The MIT License (MIT)

Copyright (c) 2016 Matheus M. Cardoso  <matheusmcrds@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE. */

#include "hydra.h"

int hydra_init() {
  curl_global_init(CURL_GLOBAL_ALL);
  return 1;
}

HydraDownload *hydra_download() {
  HydraDownload *hd = malloc(sizeof(HydraDownload));

  hd->curl = curl_easy_init();
  hd->file = NULL;

  if(hd->curl) {
    /* sets curl header callback */
    curl_easy_setopt(hd->curl, CURLOPT_HEADERFUNCTION, header_callback);

    /* sets ptr to hd as userdata for the header callback */
    curl_easy_setopt(hd->curl, CURLOPT_HEADERDATA, hd);

    /* sets curl write callback */
    curl_easy_setopt(hd->curl, CURLOPT_WRITEFUNCTION, write_callback);

    /* set ptr to hd as userdata for the curl write callback */
    curl_easy_setopt(hd->curl, CURLOPT_WRITEDATA, hd);

    /* verbose output from curl */
    // curl_easy_setopt(hd->curl, CURLOPT_VERBOSE, 1L);

    return hd;
  }

  return NULL;
}

int hydra_download_start(HydraDownload* hd) {
  if(hd->curl) {
    curl_easy_setopt(hd->curl, CURLOPT_URL, hd->url);
    CURLcode res = curl_easy_perform(hd->curl);

    return 1;
  } else
    return 0;
}

int hydra_download_close(HydraDownload *hd) {
  free(hd);
  return 1;
}

/*
Callback from CURL when header is available for processing.
Userdata is expected to be pointer to HydraDownload (HydraDownload*).
Figures out file name from HTTP header.
DOC: https://curl.haxx.se/libcurl/c/CURLOPT_HEADERFUNCTION.html
*/
size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
  HydraDownload *hd = (HydraDownload *)userdata;
  // figure out filename from HTTP header if filename is not set.
  if(!(hd->filename)) {
    const char *start = strstr(buffer, "filename=\"");

    // found filename in header
    if(start) {
      start += 10; // place pointer after filename="

      const char *finish = strstr(start, "\"");

      size_t length = finish-start;
      hd->filename = (char*)malloc(sizeof(char)*(length+1));
      strncpy(hd->filename, start, length);
      hd->filename[length] = '\0';
    }
  }

  return nitems*size;
}

/*
Callback from CURL when data is available for processing.
Userdata is expected to be pointer to HydraDownload (HydraDownload*).
Writes data to file.
DOC: https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
*/
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  HydraDownload *hd = (HydraDownload *)userdata;

  if(!hd->file) {

    hd->file = fopen(hd->filename, "wb");
  }

  size_t size_written = fwrite(ptr, size, nmemb, hd->file);
  return size_written;
}
