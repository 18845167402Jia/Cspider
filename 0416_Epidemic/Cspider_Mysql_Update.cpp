#include <Cspider.h>

bool Cspider_Mysql_Update(char* szSql,MYSQL* sock)
{
	if(!szSql)return false;

	if(mysql_query(sock,szSql))return false;

	return true;
}