#include <Cspider.h>

//��¡�������Ĳ���
void Cspider_BloomFilter_Insert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //�Ƿ�����
        return;
    }
    //���ȸ����ַ�����ϣ�㷨�����ַ�����Ӧ������
    //Ȼ�󽫼���������ָ��ݳ���������ת��Ϊʵ�ʶ�Ӧ�ı���λ�±�
    uint64_t bloomnum[FUNCMAXSIZE];//���������ڴ�ż���Ķ���±�ֵ
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)                                                                                   
    {
        bloomnum[i] = bf->bloomfunc[i](str) % MAXSIZE;
    }
    //�ٽ����±���뵽��¡�������е�λͼ�У�ֱ�ӵ���λͼ�Ĳ��뺯������
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        Cspider_BitMap_Set(&bf->bm,bloomnum[i]);
    }
    return;
}