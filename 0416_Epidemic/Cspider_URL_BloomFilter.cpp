#include<Cspider.h>

unsigned char* Cspider_URL_MD5(url_t u)
{
	char* url =  u.surl;   // ��ȡ�����URL
	unsigned char* tmpUrl = NULL;          // ����ѹ�����URL
	memset(tmpUrl,0,sizeof(tmpUrl));
	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, ()url, sizeof(url));
	MD5_Final(tmpUrl,&ctx);
	return tmpUrl;
}
