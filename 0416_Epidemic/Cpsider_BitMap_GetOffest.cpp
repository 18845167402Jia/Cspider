#include <Cspider.h>

//将获取指定位所在的数组下标及偏移量封装为函数                                                                  
void Cspider_BitMap_GetOffest(uint64_t index,uint64_t* n,uint64_t* offset)
{
    //首先计算该位在哪个数组元素内（数组元素以64为为一个单元）
    //计算完之后的n表示该位在下标为n的数组元素内（数组下标从0开始计数）
    *n = index/(sizeof(BitMapType)*8);
 
    //在计算该位在该元素的哪个位上
    //计算完之后的offset表示index在下标为的数组元素的哪一位（从0开始计算）
    *offset = index % (sizeof(BitMapType)*8); 
    return;
}