#include <Cspider.h>

//����ȡָ��λ���ڵ������±꼰ƫ������װΪ����                                                                  
void Cspider_BitMap_GetOffest(uint64_t index,uint64_t* n,uint64_t* offset)
{
    //���ȼ����λ���ĸ�����Ԫ���ڣ�����Ԫ����64ΪΪһ����Ԫ��
    //������֮���n��ʾ��λ���±�Ϊn������Ԫ���ڣ������±��0��ʼ������
    *n = index/(sizeof(BitMapType)*8);
 
    //�ڼ����λ�ڸ�Ԫ�ص��ĸ�λ��
    //������֮���offset��ʾindex���±�Ϊ������Ԫ�ص���һλ����0��ʼ���㣩
    *offset = index % (sizeof(BitMapType)*8); 
    return;
}