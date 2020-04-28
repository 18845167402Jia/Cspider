#include<Cspider.h>

int Cspider_Connect_Webserver(url_t* u,int webfd)
{
	struct sockaddr_in webaddr;
	memset(&webaddr,0,sizeof(webaddr));
	webaddr.sin_family = AF_INET;
	webaddr.sin_port = htons(u->port);
	inet_pton(AF_INET,u->ip,&webaddr.sin_addr.s_addr);
	if((connect(webfd,(struct sockaddr*)&webaddr,sizeof(webaddr)))!=0)
	{
		perror("Connect Webserver error..");
		return -1;
	}
	printf("[3] Connect Webserver Success..\n");
	return  0;

}