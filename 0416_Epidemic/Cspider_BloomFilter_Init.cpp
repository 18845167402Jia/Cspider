#include <Cspider.h>

//布隆过滤器的初始化：参数func1,func2是两个字符串哈希函数
void Cspider_BloomFilter_Init(BloomFilter* bf,BloomFunc func1,BloomFunc func2)
{
    if(bf == NULL || func1 == NULL || func2 == NULL)                                                            
    {
        //非法输入
        return;
    }
    //对布隆过滤器中的位图进行初始化
	
    Cspider_BitMap_Init(&bf->bm,MAXSIZE);
    bf->bloomfunc[0] = func1;
    bf->bloomfunc[1] = func2;
    return;
}