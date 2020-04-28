#include <Cspider.h>

int Cspider_Create_Requesthead(url_t *u,char *head)
{
     memset(head,0,4096);
     sprintf(head,"GET %s HTTP/1.1\r\n"\
             "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
             "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"\
             "Host: %s \r\n"\
             "Connection:close\r\n\r\n",u->surl,u->domain);
     printf("[4] create_requesthead success,%s\n",head);
     return 0;
 }
 
