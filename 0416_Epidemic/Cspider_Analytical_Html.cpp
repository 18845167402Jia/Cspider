#include <Cspider.h>

MYSQL *sock = new MYSQL;

int Cspider_Analytic_Html(url_t * u, queue_t *q,BloomFilter *bf)
{
	url_t node;
	mysql_init(sock);  
	mysql_set_character_set(sock,"utf8");// 数据库增删改查
	// 数据库测试
	if( Cspider_Mysql_Connect("127.0.0.1","root","root","0419cspider",sock) )
	{
		cout << "数据库连接成功" << endl;
	}
	
	//char *p = Cspider_File_mmap(u->file);

	string filepath;
	string strpath(u->file);
	filepath = "D://";
	filepath += strpath;

	char * b = (char*)filepath.c_str();

	WCHAR wszClassName[256];
	memset(wszClassName,0,sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP,0,b,strlen(b)+1,wszClassName,
		sizeof(wszClassName)/sizeof(wszClassName[0]));
	// 步骤1 打开文件FILE_FLAG_WRITE_THROUGH
	HANDLE hFile = CreateFile(
		wszClassName,
		GENERIC_WRITE | GENERIC_READ,// 如果要映射文件：此处必设置为只读(GENERIC_READ)或读写
		0, // 此设为打开文件的任何尝试均将失败
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, //|FILE_FLAG_WRITE_THROUGH,【解1】
		NULL);
	if (hFile != INVALID_HANDLE_VALUE)// 文件打开失败返回句柄为-1
		// 这步必须测试，详细见步骤2
	{
		cout<<"文件打开成功~!\n";
	}
	else
	{
		cout<<"文件打开失败！\n";
		DWORD d = GetLastError();
		cout<<d<<endl;
		return NULL;
	}



	// 步骤2 建立内存映射文件
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	printf("文件大小为：%d\n", dwFileSize);
	HANDLE hFileMap = CreateFileMapping(
		hFile, // 如果这值为INVALID_HANDLE_VALUE,是合法的，上步一定测试啊
		NULL, // 默认安全性
		PAGE_READWRITE, // 可读写
		0, // 2个32位数示1个64位数，最大文件字节数，
		// 高字节，文件大小小于4G时，高字节永远为0
		0,//dwFileSize, // 此为低字节，也就是最主要的参数，如果为0，取文件真实大小
		NULL);
	if (hFileMap != NULL)
	{
		cout<<"内存映射文件创建成功~!\n";
	}
	else
	{
		cout<<"内存映射文件创建失败~！"<<endl;
	}



	// 步骤3：将文件数据映射到进程的地址空间
	PVOID pvFile = MapViewOfFile( //pvFile就是得到的指针，用它来直接操作文件
		hFileMap,
		FILE_MAP_WRITE, // 可写
		0, // 文件指针头位置 高字节
		0, // 文件指针头位置 低字节 必为分配粒度的整倍数,windows的粒度为64K
		0); // 要映射的文件尾，如果为0，则从指针头到真实文件尾
	if (pvFile != NULL)
	{
		cout<<"文件数据映射到进程的地址成功~!\n";
	}
	else
	{
		cout<<"文件数据映射到进程的地址成功~!\n";
	}

	char *p = (char*)pvFile;
	char *pTemp = p;

	char BookName[4096];
	char AuthName[4096];
	char Aurl[4096];
	memset(BookName,0,sizeof(BookName));
	memset(AuthName,0,sizeof(AuthName));
	memset(Aurl,0,sizeof(Aurl));

	// 正则类型  书名  作者名
	regex_t book_reg , auth_reg ,aurl_reg;
	// 正则匹配结果
	regmatch_t book_match[2] , auth_match[2] , aurl_match[2];
	regcomp(&book_reg,"<a href=\"//book.qidian.com/info/[^>]\\+\\?>\\([^<]\\+\\?\\)</a>",0);
	regcomp(&auth_reg,"<a class=\"name\" href=\"//my.qidian.com/author/[^>]\\+\\?>\\([^<]\\+\\?\\)</a>",0);
	regcomp(&aurl_reg,"<a href=\"\\(//www.qidian.com/all[^\"]\\+\\?\\)\"",0);

	// 匹配链接
	while((regexec(&aurl_reg,p,2,aurl_match,0)) == 0)
	{
		_snprintf(Aurl,aurl_match[1].rm_eo - aurl_match[1].rm_so + 6, "https:%s",p + aurl_match[1].rm_so);
		if( !Cspider_BloomFilter_Test(bf,Aurl) )
		{
			strcpy(node.surl,Aurl);
			printf("[*] NEW_URL [%s]\n",Aurl);
			Cspider_Queue_Add(q,node);
			Cspider_BloomFilter_Insert(bf,Aurl);
		}
		p += aurl_match[0].rm_eo;
		memset(Aurl,0,sizeof(Aurl));
		if(q->size == q->max)
		{
			break;
		}
	}
	// p重新偏移
	p = (char*)pvFile;

	while((regexec(&book_reg,p,2,book_match,0)) == 0)
	{
		_snprintf(BookName,book_match[1].rm_eo - book_match[1].rm_so, "%s",p + book_match[1].rm_so);
		printf("[*] BookName [%s]  ",BookName);
		char szsql[3000] = {0};
		p += book_match[0].rm_eo;

		if( regexec(&auth_reg,p,2,auth_match,0) == 0 )
		{
			_snprintf(AuthName,auth_match[1].rm_eo - auth_match[1].rm_so, "%s",p + auth_match[1].rm_so);
			printf("[*] AuthorName [%s]  \n",AuthName);
			p += auth_match[0].rm_eo;
		}
		sprintf_s(szsql,"insert into book values('%s','%s')",BookName,AuthName);
		memset(BookName,0,sizeof(BookName));
		memset(AuthName,0,sizeof(AuthName));
		Cspider_Mysql_Update(szsql,sock);
	}
	regfree(&book_reg);
	regfree(&auth_reg);
	regfree(&aurl_reg);

	CloseHandle(hFile);
	CloseHandle(hFileMap);
	UnmapViewOfFile(pvFile);
	return 0;
}
