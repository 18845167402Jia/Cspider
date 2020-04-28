#include <Cspider.h>

//��¡������������
void Cspider_BloomFilter_Destroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        //�Ƿ�����
        return;
    }
 
    //����¡�������еĳ�Ա��λͼ�������ټ���
    Cspider_BitMap_Destroy(&bf->bm);
 
    bf->bloomfunc[0] = NULL;
    bf->bloomfunc[1] = NULL;
    return;
}