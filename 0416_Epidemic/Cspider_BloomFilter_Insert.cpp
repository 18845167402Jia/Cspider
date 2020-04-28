#include <Cspider.h>

//布隆过滤器的插入
void Cspider_BloomFilter_Insert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //非法输入
        return;
    }
    //首先根据字符串哈希算法计算字符串对应的数字
    //然后将计算出的数字根据除留余数法转化为实际对应的比特位下标
    uint64_t bloomnum[FUNCMAXSIZE];//该数组用于存放计算的多个下标值
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)                                                                                   
    {
        bloomnum[i] = bf->bloomfunc[i](str) % MAXSIZE;
    }
    //再将该下标插入到布隆过滤器中的位图中，直接调用位图的插入函数即可
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        Cspider_BitMap_Set(&bf->bm,bloomnum[i]);
    }
    return;
}