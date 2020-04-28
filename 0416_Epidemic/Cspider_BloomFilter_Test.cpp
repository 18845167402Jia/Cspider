#include <Cspider.h>

//�ڲ�¡���������ж�һ���ַ����Ƿ����
int Cspider_BloomFilter_Test(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        //�Ƿ�����
        return 0;
    }
    //���ȸ����ַ�����ϣ�㷨�����ַ�����Ӧ������
    //�ڸ��ݸ����ּ�����ݳ����������������λ���ڵ��±�
    uint64_t bloomnum[FUNCMAXSIZE];
    int i = 0;
    for(;i < FUNCMAXSIZE;i++)
    {
        bloomnum[i] = bf->bloomfunc[i](str)%MAXSIZE; 
    }
    //Ȼ���ڲ�¡�������е�λͼ�ṹ���ж�����������λ��״̬
    //�����Ϊ1�����ʾ���ַ�������
    //ֻҪ��һ��Ϊ0�����ʾ���ַ���������
    for(i = 0;i < FUNCMAXSIZE;i++)
    {
        if(Cspider_BitMap_Test(&bf->bm,bloomnum[i]) == 0)
        {                                                                                                       
            return 0;
        }
    }
    return 1;
}