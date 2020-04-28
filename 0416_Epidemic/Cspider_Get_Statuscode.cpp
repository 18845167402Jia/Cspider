#include<Cspider.h>


int Cspider_Get_StatusCode(const char* reshead)
{
	char sstat[1024];
	int stat;
	memset(&sstat,0,sizeof(sstat));
	regex_t sreg;
	regmatch_t smatch[2];
	regcomp(&sreg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n",0);
	if((regexec(&sreg,reshead,2,smatch,0))==0)
	{
		_snprintf(sstat,smatch[1].rm_eo - smatch[1].rm_so + 1,"%s",reshead + smatch[1].rm_so);
		sscanf(sstat,"%d",&stat);
		printf("[*] Get statcode success:%d\n",stat);
		return stat;
	}
	regfree(&sreg);
	return -1;
}
          