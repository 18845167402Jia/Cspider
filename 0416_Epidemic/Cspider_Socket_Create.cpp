#include<Cspider.h>



int Cspider_Socket_Create()
{
	WSADATA wsaData = {0};
	int iResult = 0;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		wprintf(L"WSAStartup failed: %d\n", iResult);
		return 1;
	}

	int webfd;
	struct sockaddr_in myaddr;
	memset(&myaddr,0,sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8000);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( (webfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("Socket Create Error..");
		return -1;
	}

	bind(webfd,(struct sockaddr*)&myaddr,sizeof(myaddr));

	printf("[2] Socket Create Success..\n");
	return webfd;
}

