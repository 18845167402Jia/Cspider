#include <Cspider.h>

size_t BKDRHash(const char *str)  
{  
	register size_t hash = 0;  
	while (size_t ch = (size_t)*str++)  
	{         
		hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..         
	}  
	return hash;  
}  

size_t SDBMHash(const char *str)  
{  
	register size_t hash = 0;  
	while (size_t ch = (size_t)*str++)  
	{  
		hash = 65599 * hash + ch;         
		//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
	}  
	return hash;  
} 

map<char*,char*> DNS;
int main()
{
	//setlocale(LC_CTYPE, "chs");
	//  种子URL 
	//char *tmpurl = "http://www.jingyu.com/ranks";
	char* tmpurl = "https://www.qidian.com/all";

	// 自定义host文件
	

	url_t tmp; 
	url_t node;
	int webfd;         // 与服务器交互的socket
	char head[4096];   // 存放请求头
	ssl_t* ssl = NULL;
	strcpy(tmp.surl,tmpurl);

	// 布隆过滤器的初始化
	BitMap bm;
	BloomFilter bf;
	Cspider_BitMap_Init(&bm,10000);
	Cspider_BloomFilter_Init(&bf,BKDRHash,SDBMHash);

	// 创建双向链表存储URL
	queue_t * URL_Queue;
	URL_Queue = Cspider_Queue_Create(10000);

	if( !Cspider_BloomFilter_Test(&bf,tmpurl) )
	{
		Cspider_BloomFilter_Insert(&bf,tmpurl);
		Cspider_Queue_Add(URL_Queue,tmp);
	}
	while( URL_Queue->size > 0 )
	{
		webfd = Cspider_Socket_Create();
		Cspider_Queue_Del(URL_Queue,&node);
		Cspider_Analytic_Url(&node,&DNS);
		Cspider_Connect_Webserver(&node,webfd);
		Cspider_Create_Requesthead(&node,head);
		// 创建HTTP使用的openssl
		if(node.httptype == 1)
		{
			ssl = Cspider_Create_Openssl(webfd);
		}
		if( (Cspider_Download(&node,head,webfd,ssl)) == -1)
		{
			continue;
		}
		Cspider_Analytic_Html(&node,URL_Queue,&bf);
		Sleep(1000);
	}
	closesocket(webfd);
	system("pause");
	return 0;
}