#include <stdio.h>
#include <curl/curl.h>

/*
Callback from CURL when data is available for saving.
Userdata is expected to be pointer to file (FILE*).
DOC: https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
*/
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
  size_t size_written = fwrite(ptr, size, nmemb, userdata);
  return size_written;
}

int main(int argc, char **argv) {
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://3geauomtsgozd1pbqgcan43btf3tgn4mrqiaggh3qcpzs4.ourdvsss.com/d1.baidupcs.com/file/ee84430bfd8d4c557c463c4ea89e6188?bkt=p3-00007fb855b17cdaf91aa979c1fb56099e44&xcode=1163fdf8a6bbd127fb7f87bf0dd806a704c2bec371dd1fe7&fid=2527077195-250528-802372966247380&time=1479561418&sign=FDTAXGERLBH-DCb740ccc5511e5e8fedcff06b081203-LoEDeqO%2FTn%2BlT%2FeU4YoWFvKC5wc%3D&to=sf&fm=Yan,B,U,ny&sta_dx=1251532489&sta_cs=556&sta_ft=rar&sta_ct=5&sta_mt=2&fm2=Yangquan,B,U,ny&newver=1&newfm=1&secfm=1&flow_ver=3&pkey=00007fb855b17cdaf91aa979c1fb56099e44&sl=76087374&expires=8h&rt=pr&r=797393388&mlogid=7511849147599341962&vuk=2527077195&vbdid=2606474409&fin=241.rar&fn=241.rar&slt=pm&uta=0&rtype=1&iv=0&isw=0&dp-logid=7511849147599341962&dp-callid=0.1.1&hps=1&csl=86&csign=fVPj8jmwZF0%2BRTa5Lzz9Bjwz%2FJ8%3D&wshc_tag=0&wsts_tag=583050d1&wsid_tag=b19ea49a&wsiphost=ipdbm");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    FILE *file = fopen("241.rar", "wb");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(file);
  }
}
