//#include<Cspider.h>
//
//
//char* Cspider_File_mmap(char * filename)
//{
//	string filepath;
//	string strpath(filename);
//	filepath = "D://";
//	filepath += strpath;
//
//	char * b = (char*)filepath.c_str();
//	
//	WCHAR wszClassName[256];
//	memset(wszClassName,0,sizeof(wszClassName));
//	MultiByteToWideChar(CP_ACP,0,b,strlen(b)+1,wszClassName,
//		sizeof(wszClassName)/sizeof(wszClassName[0]));
//	// ����1 ���ļ�FILE_FLAG_WRITE_THROUGH
//	HANDLE hFile = CreateFile(
//		wszClassName,
//		GENERIC_WRITE | GENERIC_READ,// ���Ҫӳ���ļ����˴�������Ϊֻ��(GENERIC_READ)���д
//		0, // ����Ϊ���ļ����κγ��Ծ���ʧ��
//		NULL,
//		OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, //|FILE_FLAG_WRITE_THROUGH,����1��
//		NULL);
//	if (hFile != INVALID_HANDLE_VALUE)// �ļ���ʧ�ܷ��ؾ��Ϊ-1
//		// �ⲽ������ԣ���ϸ������2
//	{
//		cout<<"�ļ��򿪳ɹ�~!\n";
//	}
//	else
//	{
//		cout<<"�ļ���ʧ�ܣ�\n";
//		DWORD d = GetLastError();
//		cout<<d<<endl;
//		return NULL;
//	}
//
//
//
//	// ����2 �����ڴ�ӳ���ļ�
//	DWORD dwFileSize = GetFileSize(hFile, NULL);
//	printf("�ļ���СΪ��%d\n", dwFileSize);
//	HANDLE hFileMap = CreateFileMapping(
//		hFile, // �����ֵΪINVALID_HANDLE_VALUE,�ǺϷ��ģ��ϲ�һ�����԰�
//		NULL, // Ĭ�ϰ�ȫ��
//		PAGE_READWRITE, // �ɶ�д
//		0, // 2��32λ��ʾ1��64λ��������ļ��ֽ�����
//		// ���ֽڣ��ļ���СС��4Gʱ�����ֽ���ԶΪ0
//		0,//dwFileSize, // ��Ϊ���ֽڣ�Ҳ��������Ҫ�Ĳ��������Ϊ0��ȡ�ļ���ʵ��С
//		NULL);
//	if (hFileMap != NULL)
//	{
//		cout<<"�ڴ�ӳ���ļ������ɹ�~!\n";
//	}
//	else
//	{
//		cout<<"�ڴ�ӳ���ļ�����ʧ��~��"<<endl;
//	}
//
//
//
//	// ����3�����ļ�����ӳ�䵽���̵ĵ�ַ�ռ�
//	PVOID pvFile = MapViewOfFile( //pvFile���ǵõ���ָ�룬������ֱ�Ӳ����ļ�
//		hFileMap,
//		FILE_MAP_WRITE, // ��д
//		0, // �ļ�ָ��ͷλ�� ���ֽ�
//		0, // �ļ�ָ��ͷλ�� ���ֽ� ��Ϊ�������ȵ�������,windows������Ϊ64K
//		0); // Ҫӳ����ļ�β�����Ϊ0�����ָ��ͷ����ʵ�ļ�β
//	if (pvFile != NULL)
//	{
//		cout<<"�ļ�����ӳ�䵽���̵ĵ�ַ�ɹ�~!\n";
//	}
//	else
//	{
//		cout<<"�ļ�����ӳ�䵽���̵ĵ�ַ�ɹ�~!\n";
//	}
//
//	char *p = (char*)pvFile;
//	//CloseHandle(hFile);
//	//CloseHandle(hFileMap);
//	//UnmapViewOfFile(pvFile);
//	return p;
//}