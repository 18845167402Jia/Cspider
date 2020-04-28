#include <Cspider.h>


//MYSQL_RES *results;   
//MYSQL_ROW record; 



bool Cspider_Mysql_Connect(char *host,char *user,char *pass,char *db,MYSQL* sock)
{
	if (!mysql_real_connect(sock, host, user, pass, db, 3307, NULL, CLIENT_MULTI_STATEMENTS))
	{
        //连接错误
		return false;
	}
    return true;
}
