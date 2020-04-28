#include <Cspider.h>


//测试某一位是否为1
int Cspider_BitMap_Test(BitMap* bm,uint64_t index)                                                                       
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return 0;
    }
    uint64_t n;
    uint64_t offset;
    //获取index所在的数组元素下标及偏移量                                                                       
    Cspider_BitMap_GetOffest(index,&n,&offset);
   
    //用1与之按位与，如果结果为0，则该位为0，否则为1
    //如果该位为1时，按位与完的结果必定只有该位为1，其余位为0，所以对结果进行判断时
    //只能跟0进行比较，不能跟1进行比较
    uint64_t ret = bm->data[n] & (0x1ul << offset);
    if(ret == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }                                                                                                           
}