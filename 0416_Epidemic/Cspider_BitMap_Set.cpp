#include <Cspider.h>

//��ĳһλ����Ϊ1                                                                                               
void Cspider_BitMap_Set(BitMap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        //�Ƿ�����
        return;
    }
 
    //���ȼ����λ���ڵ������±꼰ƫ����
    uint64_t n;
    uint64_t offset;
    Cspider_BitMap_GetOffest(index,&n,&offset);
 
    //�ٽ���λ����Ϊ1
    //����λ��Ϊ1ʱҪ��֤��������λ���䣬��ʱ��Ҫʹ����λ��0���а�λ��
    //��ˣ���λҪ��1���а�λ�򣬲��ܱ�֤����λ��Ϊ1��������λҲ�ܱ��ֲ���
 
    //��λ������Ľ������ı�ԭ����ֵ������Ҫ������и�ֵ
    bm->data[n] = bm->data[n] | (0x1ul << offset);
    return;
 
}