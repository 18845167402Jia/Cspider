#include <Cspider.h>

//给某一位设置为1                                                                                               
void Cspider_BitMap_Set(BitMap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //非法输入
        return;
    }
 
    //首先计算该位所在的数组下标及偏移量
    uint64_t n;
    uint64_t offset;
    Cspider_BitMap_GetOffest(index,&n,&offset);
 
    //再将该位设置为1
    //将该位置为1时要保证其他其他位不变，此时就要使其他位与0进行按位或
    //因此，该位要与1进行按位或，才能保证将该位置为1，而其他位也能保持不变
 
    //按位操作后的结果不会改变原来的值，所以要对其进行赋值
    bm->data[n] = bm->data[n] | (0x1ul << offset);
    return;
 
}