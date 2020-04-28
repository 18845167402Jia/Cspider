#include <Cspider.h>

//布隆过滤器的销毁
void Cspider_BloomFilter_Destroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        //非法输入
        return;
    }
 
    //将布隆过滤器中的成员：位图进行销毁即可
    Cspider_BitMap_Destroy(&bf->bm);
 
    bf->bloomfunc[0] = NULL;
    bf->bloomfunc[1] = NULL;
    return;
}