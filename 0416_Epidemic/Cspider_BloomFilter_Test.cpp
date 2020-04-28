#include <Cspider.h>

//在布隆过滤器中判断一个字符串是否存在
int Cspider_BloomFilter_Test(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return 0;
    }
    //首先根据字符串哈希算法计算字符串对应的数字
    //在根据该数字计算根据除留余数法计算比特位所在的下标
    uint64_t bloomnum[FUNCMAXSIZE];
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)
    {
        bloomnum[i] = bf->bloomfunc[i](str)%MAXSIZE; 
    }
    //然后在布隆过滤器中的位图结构中判断这两个比特位的状态
    //如果均为1，则表示该字符串存在
    //只要有一个为0，则表示该字符串不存在
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        if(Cspider_BitMap_Test(&bf->bm,bloomnum[i]) == 0)
        {                                                                                                       
            return 0;
        }
    }
    return 1;
}