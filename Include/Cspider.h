#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <sys/types.h>
#include <Wincrypt.h>
#include <stdint.h>      //uint64_t�����ø�ͷ�ļ�
#include <hash_map>
#include <iostream>
#include <mysql.h>
#include <regex.h>
#include <queue>
#include <stack>
#include <map>
#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#include <list>
// MD5�Ŀ�
//#pragma comment(lib, "libeay32.lib")
//#pragma comment(lib, "ssleay32.lib") 
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace std;

 // ���岼¡�������е�λͼ�����1000������λ����ʹ��
#define MAXSIZE 1000  
//������Ҫ�����ַ�����ϣ�㷨����ʾһ���ַ���
#define FUNCMAXSIZE 2

 //�����ַ�����ϣ�㷨
typedef size_t (*BloomFunc)(const char* str);

// ����HASH ���� func1  func2

//λͼ��uint64_tΪ��λ�����ڴ������                                                                            
typedef uint64_t BitMapType;


//λͼ�Ľṹ����
typedef struct BitMap
{
    BitMapType* data;
    uint64_t capacity;//λͼ������ܱ�ʾ�ı���λ����
}BitMap;

// ��¡�������Ķ���
typedef struct BloomFilter
{
	BitMap bm;
	BloomFunc bloomfunc[FUNCMAXSIZE];  
}BloomFilter;


// openssl ��
typedef struct
{
    SSL *sslsocket;
	SSL_CTX *sslctx;
}ssl_t;

// url ���ӽṹ��
typedef struct
{
	char surl[4096];
	char domain[1024];
	char file[8192];
	char path[1024];
	char ip[16];
	int httptype;
	int port;
}url_t;

// ѭ������
typedef struct
{
	url_t* urlarr;
	int front;
	int rear;
	int size;
	int max;
}queue_t;

int Cspider_Analytic_Url(url_t *,map<char*,char*> *);                   // ����URL���ӽ���
int Cspider_Socket_Create();                          // �����ʼ��socket����
int Cspider_Connect_Webserver(url_t*,int);            // ����WEB������
int Cspider_Create_Requesthead(url_t *,char *);       // ����HTTP����ͷ
int Cspider_Download(url_t*, const char*,int,ssl_t*); // ��WEB���������� �־û�����
int Cspider_Get_StatusCode(const char*);              // ��ȡ��������Ӧ״̬��
ssl_t* Cspider_Create_Openssl(int);                   //  ʹ��openssl��webserver���а�ȫ��֤
int Cspider_Analytic_Html(url_t * u, queue_t *q,BloomFilter* bf);     //  ������ҳԴ��
char* Cspider_File_mmap(char* filename);

// ����λͼ�Ĳ���
void Cspider_BitMap_Init(BitMap* bm,uint64_t capacity);                      // λͼ�ĳ�ʼ��
void Cspider_BitMap_GetOffest(uint64_t index,uint64_t* n,uint64_t* offset);  // ��ȡƫ����
int  Cspider_BitMap_Test(BitMap* bm,uint64_t index);                         // λͼ����ĳһλ�Ƿ�Ϊ1
void Cspider_BitMap_Set(BitMap* bm,uint64_t index);                          // λͼĳһλ����Ϊ1
void Cspider_BitMap_Destroy(BitMap* bm);                                     // λͼ������

// ���ڲ�¡�������Ĳ���
void Cspider_BloomFilter_Init(BloomFilter* bf,BloomFunc func1,BloomFunc func2);  // ��¡�������ĳ�ʼ��    
void Cspider_BloomFilter_Insert(BloomFilter* bf,const char* str);                // ��¡�������Ĳ���
int  Cspider_BloomFilter_Test(BloomFilter* bf,const char* str);                  // ��¡������ TEST
void Cspider_BloomFilter_Destroy(BloomFilter* bf);                               // ��¡������������

// �������ݿ�Ĳ���
bool Cspider_Mysql_Connect(char* host,char* user,char* pass,char* db,MYSQL* sock);    // ���ݿ������
bool Cspider_Mysql_Update(char* szSql,MYSQL* sock);  

// ����URL����
queue_t *Cspider_Queue_Create(int max);           // ѭ�����еĴ���
int Cspider_Queue_Add(queue_t* q,url_t node);     // ѭ���������Ԫ��
int Cspider_Queue_Del(queue_t * q,url_t* node);    // ѭ������ɾ��


