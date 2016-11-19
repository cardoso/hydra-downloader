#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <curl/curl.h>

#include  "hydra.h"

int main(int argc, char **argv) {

  hydra_init();
  HydraDownload *hd = hydra_download();
  hd->url = "https://curl.haxx.se/libcurl/c/curl_easy_setopt.html";
  hd->filename = "jujuba.html";
  hydra_download_start(hd);

  // curl_global_init(CURL_GLOBAL_ALL);
  // CURL *curl = curl_easy_init();

  // if(curl) {
  //   curl_easy_setopt(curl, CURLOPT_URL, "https://3geauomtsgozd1pbqgcan43btf3tgn4mrqiaggh3qcpzs4.ourdvsss.com/d1.baidupcs.com/file/ee84430bfd8d4c557c463c4ea89e6188?bkt=p3-00007fb855b17cdaf91aa979c1fb56099e44&xcode=02805549f2b49724fc920c0fdb81fa0104c2bec371dd1fe7&fid=2527077195-250528-802372966247380&time=1479561418&sign=FDTAXGERLBH-DCb740ccc5511e5e8fedcff06b081203-JHoSjb%2FeTgiz%2BuUOI4mIP6LpuG0%3D&to=sf&fm=Yan,B,U,ny&sta_dx=1251532489&sta_cs=559&sta_ft=rar&sta_ct=5&sta_mt=2&fm2=Yangquan,B,U,ny&newver=1&newfm=1&secfm=1&flow_ver=3&pkey=00007fb855b17cdaf91aa979c1fb56099e44&sl=76480590&expires=8h&rt=pr&r=797393388&mlogid=7511849147599341962&vuk=2527077195&vbdid=2606474409&fin=241.rar&fn=241.rar&slt=pm&uta=0&rtype=1&iv=0&isw=0&dp-logid=7511849147599341962&dp-callid=0.1.1&hps=1&csl=80&csign=8dK1ihiVCYjN21kqCY6%2BWGAQgr8%3D&wshc_tag=0&wsts_tag=583067c4&wsid_tag=b19ea49a&wsiphost=ipdbm");
  //   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  //
  //   FILE *file = fopen("241.rar", "wb");
  //
  //   /* set pointer to file as the userdata for the write_callback */
  //   curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
  //
  //
  //   /* sets header callback */
  //   curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
  //
  //   /* set header userdata */
  //   curl_easy_setopt(curl, CURLOPT_HEADERDATA, "irrelevant");
  //
  //   /* ask libcurl to show us the verbose output */
  //   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  //
  //   CURLcode res = curl_easy_perform(curl);
  //   curl_easy_cleanup(curl);
  //   fclose(file);
  // }
}
