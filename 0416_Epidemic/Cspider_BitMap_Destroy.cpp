#include <Cspider.h>

//����λͼ
void Cspider_BitMap_Destroy(BitMap* bm)
{
    if(bm == NULL)
    {
        //�Ƿ�����
        return;
    }
 
    bm->capacity = 0;
    free(bm->data);
    return;
}