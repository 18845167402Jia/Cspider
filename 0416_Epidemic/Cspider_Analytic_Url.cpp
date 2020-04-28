#include<Cspider.h>

// 程序内部自定义DNS映射表 ------>尽可能减少本地host缓存和公网服务

int Cspider_Analytic_Url(url_t * u,map<char*,char*> *DNS)
{
	// 加载库 
	WSADATA wsaData;
	int iResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	int i = 0 ; 
	int j = 0 ; 
	int filesize = 0;
	int start = 0 ;
	char* arr[] = {"http://","https://",NULL};

	memset(u->domain,0,sizeof(u->domain));
	memset(u->path,0,sizeof(u->path));
	memset(u->file,0,sizeof(u->file));
	memset(u->ip,0,sizeof(u->ip));
	if( (strncmp(u->surl,arr[0],strlen(arr[0]))) == 0)
	{
		u->httptype = 0;
		u->port = 80;
		start = strlen(arr[0]);
	}
	else
	{
		u->httptype = 1;
		u->port = 443;
		start = strlen(arr[1]);
	}

	// get domain
	for(i = start ; u->surl[i]!='/' && u->surl[i]!='\0' ; i++)
	{
		u->domain[j] = u->surl[i];
		j++;
	}
	//get filename
	j = 0;
	for(i = strlen(u->surl);u->surl[i] != '/';i--,filesize++);
	for(i = strlen(u->surl) - filesize + 1;u->surl[i]!='\0';i ++)
	{
		u->file[j] = u->surl[i];
		j++;
	}

	// get path
	j = 0;
	for(i=start+strlen(u->domain);i<strlen(u->surl) - filesize + 1;i++)
	{
		u->path[j] = u->surl[i];
		j++;
	}
	// get ip

	struct hostent *ent;
	//如果在自定义的DNS中找到了该 domain 和 ip 键值对  
	if( (*DNS)[u->domain] != NULL )
	{
		//将 程序内部的数据 存入  u->ip
		strcpy_s(u->ip,(*DNS)[u->domain]);
	}
	//没找到就去调用 gethostbyname
	else
	{
		if( (ent = gethostbyname(u->domain)) == NULL )
		{
			printf("gethostbyname call failed....");
			return -1;
		}
		else
		{
			// 在inet_ntop 转换后 也存入u->ip
			inet_ntop(AF_INET,ent->h_addr_list[0],u->ip,sizeof(u->ip));
			(*DNS)[u->domain] = u->ip;
		}
	}

	printf(" [1] URL analytical success: \n surl:%s\n domain:%s\n path:%s\n filename:%s\n ip:%s\n type:%d\n port:%d\n",u->surl,u->domain,u->path,u->file,u->ip,u->httptype,u->port);
	return  0;

}