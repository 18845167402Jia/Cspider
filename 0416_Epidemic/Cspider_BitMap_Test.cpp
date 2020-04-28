#include <Cspider.h>


//����ĳһλ�Ƿ�Ϊ1
int Cspider_BitMap_Test(BitMap* bm,uint64_t index)                                                                       
{
    if(bm == NULL || index >= bm->capacity)
    {
        //�Ƿ�����
        return 0;
    }
    uint64_t n;
    uint64_t offset;
    //��ȡindex���ڵ�����Ԫ���±꼰ƫ����                                                                       
    Cspider_BitMap_GetOffest(index,&n,&offset);
   
    //��1��֮��λ�룬������Ϊ0�����λΪ0������Ϊ1
    //�����λΪ1ʱ����λ����Ľ���ض�ֻ�и�λΪ1������λΪ0�����ԶԽ�������ж�ʱ
    //ֻ�ܸ�0���бȽϣ����ܸ�1���бȽ�
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