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

#ifndef HYDRA_H
#define HYDRA_H

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
int hydra_download_close(HydraDownload *hd);

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

#endif // HYDRA_H
