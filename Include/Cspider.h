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
#include <stdint.h>      //uint64_t需引用该头文件
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
// MD5的库
//#pragma comment(lib, "libeay32.lib")
//#pragma comment(lib, "ssleay32.lib") 
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace std;

 // 定义布隆过滤器中的位图最多有1000个比特位可以使用
#define MAXSIZE 1000  
//定义需要两个字符串哈希算法来表示一个字符串
#define FUNCMAXSIZE 2

 //定义字符串哈希算法
typedef size_t (*BloomFunc)(const char* str);

// 两个HASH 函数 func1  func2

//位图以uint64_t为单位进行内存的申请                                                                            
typedef uint64_t BitMapType;


//位图的结构定义
typedef struct BitMap
{
    BitMapType* data;
    uint64_t capacity;//位图中最大能表示的比特位个数
}BitMap;

// 布隆过滤器的定义
typedef struct BloomFilter
{
	BitMap bm;
	BloomFunc bloomfunc[FUNCMAXSIZE];  
}BloomFilter;


// openssl 库
typedef struct
{
    SSL *sslsocket;
	SSL_CTX *sslctx;
}ssl_t;

// url 链接结构体
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

// 循环队列
typedef struct
{
	url_t* urlarr;
	int front;
	int rear;
	int size;
	int max;
}queue_t;

int Cspider_Analytic_Url(url_t *,map<char*,char*> *);                   // 种子URL链接解析
int Cspider_Socket_Create();                          // 网络初始化socket解析
int Cspider_Connect_Webserver(url_t*,int);            // 连接WEB服务器
int Cspider_Create_Requesthead(url_t *,char *);       // 创建HTTP请求头
int Cspider_Download(url_t*, const char*,int,ssl_t*); // 与WEB服务器交互 持久化数据
int Cspider_Get_StatusCode(const char*);              // 获取服务器响应状态码
ssl_t* Cspider_Create_Openssl(int);                   //  使用openssl与webserver进行安全认证
int Cspider_Analytic_Html(url_t * u, queue_t *q,BloomFilter* bf);     //  解析网页源码
char* Cspider_File_mmap(char* filename);

// 关于位图的操作
void Cspider_BitMap_Init(BitMap* bm,uint64_t capacity);                      // 位图的初始化
void Cspider_BitMap_GetOffest(uint64_t index,uint64_t* n,uint64_t* offset);  // 获取偏移量
int  Cspider_BitMap_Test(BitMap* bm,uint64_t index);                         // 位图测试某一位是否为1
void Cspider_BitMap_Set(BitMap* bm,uint64_t index);                          // 位图某一位设置为1
void Cspider_BitMap_Destroy(BitMap* bm);                                     // 位图的销毁

// 关于布隆过滤器的操作
void Cspider_BloomFilter_Init(BloomFilter* bf,BloomFunc func1,BloomFunc func2);  // 布隆过滤器的初始化    
void Cspider_BloomFilter_Insert(BloomFilter* bf,const char* str);                // 布隆过滤器的插入
int  Cspider_BloomFilter_Test(BloomFilter* bf,const char* str);                  // 布隆过滤器 TEST
void Cspider_BloomFilter_Destroy(BloomFilter* bf);                               // 布隆过滤器的销毁

// 关于数据库的操作
bool Cspider_Mysql_Connect(char* host,char* user,char* pass,char* db,MYSQL* sock);    // 数据库的连接
bool Cspider_Mysql_Update(char* szSql,MYSQL* sock);  

// 关于URL容器
queue_t *Cspider_Queue_Create(int max);           // 循环队列的创建
int Cspider_Queue_Add(queue_t* q,url_t node);     // 循环队列添加元素
int Cspider_Queue_Del(queue_t * q,url_t* node);    // 循环队列删除


