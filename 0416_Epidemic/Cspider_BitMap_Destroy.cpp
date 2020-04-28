#include <Cspider.h>

//销毁位图
void Cspider_BitMap_Destroy(BitMap* bm)
{
    if(bm == NULL)
    {
        //非法输入
        return;
    }
 
    bm->capacity = 0;
    free(bm->data);
    return;
}