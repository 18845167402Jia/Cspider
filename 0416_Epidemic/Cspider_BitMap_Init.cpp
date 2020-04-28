#include <Cspider.h>

void Cspider_BitMap_Init(BitMap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {                                                                                                           
        //非法输入
        return;
    }
 
    bm->capacity = capacity;
    //如果位图最大表示100个数字，则需要2个64位的内存
    //如果位图最大表示200个数字，则需要4个64位的内存
    //如果位图最大表示300个数字，则需要5个64位的内存
    //malloc以字节为单位进行内存申请
 
    //需要申请多少的64位内存
    uint64_t size = bm->capacity/(sizeof(BitMapType)*8) + 1;
 
    bm->data = (BitMapType*)malloc(size * sizeof(BitMapType));
    //初始化时要将位图中的各个位均置为0，以便后续的操作
    memset(bm->data,0,size*sizeof(BitMapType));
    return;
}