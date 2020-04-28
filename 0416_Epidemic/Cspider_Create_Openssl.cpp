#include<Cspider.h>
 
 
 ssl_t* Cspider_Create_Openssl(int webfd)
 {
      ssl_t* ssl = (ssl_t*)malloc(sizeof(ssl_t));
      SSL_load_error_strings();  // ���ش�����ӿ�
      SSL_library_init();   // ��ʼ��SSL��
      OpenSSL_add_ssl_algorithms(); // ��ʼ������ɢ�нӿ�
      ssl->sslctx = SSL_CTX_new(SSLv23_method());
      ssl->sslsocket = SSL_new(ssl->sslctx);
      SSL_set_fd(ssl->sslsocket,webfd);
      SSL_connect(ssl->sslsocket);    // ��webserver���а�ȫ��֤������
      printf("[*] SSL connect successfully..\n");
      return ssl;                    // �����֤������ʹ��sslsocket��webserver���м��ܵİ�ȫ����
 }