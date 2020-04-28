#include <Cspider.h>

void Cspider_BitMap_Init(BitMap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {                                                                                                           
        //�Ƿ�����
        return;
    }
 
    bm->capacity = capacity;
    //���λͼ����ʾ100�����֣�����Ҫ2��64λ���ڴ�
    //���λͼ����ʾ200�����֣�����Ҫ4��64λ���ڴ�
    //���λͼ����ʾ300�����֣�����Ҫ5��64λ���ڴ�
    //malloc���ֽ�Ϊ��λ�����ڴ�����
 
    //��Ҫ������ٵ�64λ�ڴ�
    uint64_t size = bm->capacity/(sizeof(BitMapType)*8) + 1;
 
    bm->data = (BitMapType*)malloc(size * sizeof(BitMapType));
    //��ʼ��ʱҪ��λͼ�еĸ���λ����Ϊ0���Ա�����Ĳ���
    memset(bm->data,0,size*sizeof(BitMapType));
    return;
}