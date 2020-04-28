#include <Cspider.h>

//��¡�������ĳ�ʼ��������func1,func2�������ַ�����ϣ����
void Cspider_BloomFilter_Init(BloomFilter* bf,BloomFunc func1,BloomFunc func2)
{
    if(bf == NULL || func1 == NULL || func2 == NULL)                                                            
    {
        //�Ƿ�����
        return;
    }
    //�Բ�¡�������е�λͼ���г�ʼ��
	
    Cspider_BitMap_Init(&bf->bm,MAXSIZE);
    bf->bloomfunc[0] = func1;
    bf->bloomfunc[1] = func2;
    return;
}