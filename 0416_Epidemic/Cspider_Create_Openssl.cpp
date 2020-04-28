#include<Cspider.h>
 
 
 ssl_t* Cspider_Create_Openssl(int webfd)
 {
      ssl_t* ssl = (ssl_t*)malloc(sizeof(ssl_t));
      SSL_load_error_strings();  // 加载错误处理接口
      SSL_library_init();   // 初始化SSL库
      OpenSSL_add_ssl_algorithms(); // 初始化加密散列接口
      ssl->sslctx = SSL_CTX_new(SSLv23_method());
      ssl->sslsocket = SSL_new(ssl->sslctx);
      SSL_set_fd(ssl->sslsocket,webfd);
      SSL_connect(ssl->sslsocket);    // 与webserver进行安全认证和重连
      printf("[*] SSL connect successfully..\n");
      return ssl;                    // 完成认证重连后使用sslsocket与webserver进行加密的安全传输
 }