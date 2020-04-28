#include<Cspider.h>


int Cspider_Download(url_t *u,const char* head,int webfd,ssl_t* ssl)
{
	char buf[8192];
	char reshead[4096];
	int len;
	char* pos;
	FILE* fd;
	//FILE* FD;
	int statcode;
	memset(buf,0,sizeof(buf));
	memset(reshead,0,sizeof(reshead));
	// 发送HTTP请求头
	if(!ssl)
	{
		send(webfd,head,strlen(head),0);
		printf("[5] Send Requesthead to web success..\n");

		len = recv(webfd,buf,sizeof(buf),0);
		if((pos = strstr(buf,"\r\n\r\n")) == NULL)
		{
			printf("strstr find error..\n");
			return -1;
		}
		_snprintf(reshead,pos-buf+4,"%s",buf);
		printf("[6] Get Response head Successfully..\n");
		printf("Response Head%s\n",reshead);

		if((statcode = Cspider_Get_StatusCode(reshead)) == 200)
		{
			string filepath;


			string strpath(u->file);
			filepath = "D://";
			filepath += strpath;
			fopen_s(&fd,filepath.c_str(),"wb+");
			fwrite( pos+4, 1 , len - (pos - buf + 4) , fd);
			while( (len = recv(webfd,buf,sizeof(buf),0)) > 0)
			{
				fwrite(buf,1,len,fd);
			}
			/*char * arr;
			int size =0 ;
			fseek(fd,0,SEEK_END);
			size = ftell(fd);
			rewind(fd);
			string ss;
			arr = (char*)malloc(sizeof(char)*size);
			while(size > 0)
			{
			fread(arr,1,1000,fd);
			cout << arr << endl;
			size -= 1000;
			}*/
			fclose(fd);
			printf("[7] SSL Download Success..\n");
		}
		else
		{
			return -1;
		}
	}
	else
	{
		SSL_write(ssl->sslsocket,head,strlen(head));
		printf("[5]SSL Send Requesthead to web success..\n");

		len = SSL_read(ssl->sslsocket,buf,sizeof(buf));

		if( (pos = strstr(buf,"\r\n\r\n")) == NULL)
		{
			printf("strstr find error..\n");
			return -1;
		}
		_snprintf(reshead,pos-buf+4,"%s",buf);
		printf("[6] SSL Get Response head Successfully..\n");
		printf("Response Head%s\n",reshead);

		if((statcode = Cspider_Get_StatusCode(reshead)) == 200)
		{
			string filepath;

			/*char Name[1096];
			int i = 0 ;
			while( u->file[i] != '\0')
			{
				Name[i] = u->file[i] - '(u->file[i])';
				i++;
			}
			Name[i+1] = '\0';
			unsigned char digest[16] = {0};
			MD5_CTX md;
			MD5_Init(&md);
			MD5_Update(&md,u->file,sizeof(u->file));
			MD5_Final(digest,&md);
			cout << digest << endl;
*/
			/*for (int i = 0;i<32;i++){
				printf("%02X", digest[i]);
			}*/
			
			string strpath(u->file);
			filepath = "D://";
			filepath += strpath;
			fopen_s(&fd,filepath.c_str(),"wb+");

			//fopen_s(&fd,u->file,"wb+");

			fwrite( pos + 4, 1 , len - (pos - buf + 4) , fd);
			while((len = SSL_read(ssl->sslsocket,buf,sizeof(buf))) > 0)
			{

				fwrite(buf,1,len,fd);
			}
			printf("[7] SSL Download Success..\n");
		}
		else
		{
			return -1;
		}
		fclose(fd);
		free(ssl);
		ssl = NULL;
	}
	closesocket(webfd);
	return 0;

}       
