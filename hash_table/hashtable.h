#ifndef HASHTABLE_H
#define HASHTABLE_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INT_PTR int

//���У�Сд��ĸת�ɴ�д��ĸ
#define toupper(c) (((c) >= 'a' && (c) <= 'z') ? (c) ^ 0x20 : (c))



template <typename T>
class CCustomHashTable;

//�ַ���Ϊ�����Զ����ϣ��(��ѩ�ַ�����ϣ�㷨)
//2014-07-12 00:19 943���Ķ� ����(0) �ղ� �ٱ�
// ���ࣺ �Զ���c++������13��   �㷨��16��
//��Ȩ����������Ϊ����ԭ�����£�δ������������ת�ء�
//Ŀ¼(?)[+]
//���Ǹ��ڱ�ѩ�ַ�����ϣ�㷨������ʵ�ֵĹ�ϣ���ڴ���ʵ������һ���Ż���
//����ϣ�
//1�����ܱ����㹻����(unsigned long)�޷��������顣�����ֵ�����㷨����Ĺ̶���һЩֵ�����ܱ������������ַ�������ĳ���ӵ�����£��Ĺ�ϣֵ��
//2����ϣֵ���ַ�������д�������е��ַ���ascii����صġ�ʹ�õ���ɢ�к������Ӹ�������Ϊ����ͬ�ַ�����3�ֲ�ͬ�����ӵ�3����ϣֵ�����Ƕ�����ͬ�ġ�(�������10��22.3�η���֮һ�ĸ���)
//3��ÿ���ڵ���3��hashֵ��hash1��hash2��hash3����hash1 ��Ѱλ�Ļ�׼��hash2��hash3 ���жϽڵ��Ƿ���ͬ�ı�׼��
//4��hash1ֵ��ͻ�Ľ����ʽ�ǣ���hash1��ʼ��������ȡ��λ��˳�ӷ�ʽ��
//5���ѱ�����ַ������Ż�Ϊ�Ƚ��������μ�ֵ����ʹ���۰뷽ʽ��Ȼ��˳�ӷ�ʽ���ҡ���Ϊ���ڴ治��ʱ�ǻ���չһ���ڴ�ģ�
//6��������2�Ĵ��ݣ���С��16�����ڴ治��ʱ������չһ�����ɿ���λ�ü��������ж�

//�ص㣺
//(1)����
//ʹ��˳�ӷ�ʽ���ҿ�λ��û��ʹ��������ʡ�ڴ�ռ䡣
//(2)����
//1)��ʹ���۰뷽ʽ��Ȼ��˳�ӷ�ʽ���ҡ�
//��Ϊ���ڴ治��ʱ�ǻ���չһ���ڴ�� ����ͨ��hash1����ȥ����λ�ķ�ʽ���������Ӧ���ڴ���չ��ʽ�͹�ϣȡ�෽ʽ
//2)����ϣֵ�ȽϷ�ʽ�����:
//�Ƚϼ�ֵ�ǱȽ�3�����������������ַ�����������߲��ұȽ�Ч��
//(3)�Ƴ�
//���ҵ��ڵ�����øýڵ�Ĺ�ϣֵΪ0������ʽ���ýڵ��ֵ�������������
//1��hash�㷨����
//1)hashֵ
//���ַ��������в���ƥ����ַ�������ʵ��㷨��Ȼ��ʹ�ù�ϣ����νHash��һ����һ��������ͨ��ĳ���㷨�����԰�һ���ַ���"ѹ��" ��һ���������������ΪHash����Ȼ��������Σ�һ��32λ�������޷���Ӧ��һ���ַ����ģ�������к��ʵ�У�鷽ʽ�������ַ����������Hashֵ��ȵĿ��ܷǳ�С��
//2��hash����������ɢ�к�����
//Blizzard�Ĺ�ϣ�㷨�Ƿǳ���Ч��(����ʵ�ֿɲο� �½� 1-2 �ɼ��ܱ��������(bzhashstr))��ʹ�õ��ǵ���ɢ�к���(One-Way Hash)���ٸ����ӣ��ַ���"unitneutralacritter.grp"ͨ������㷨�õ��Ľ����0xA26067F3��
//ͨ���ǹ���һ����������Ϊ��ϣ�����������������ݳ����Ҫ�������壨��1024����ÿһ��Hashֵͨ��λ�������Ӧ�������е�һ��λ�ã�ֻҪ�������ַ����Ĺ�ϣֵ�Ե�λ����û�б�ռ�á����ĸ��Ӷ��� O(1)���㷨�������ʵ�ֲο��½� 3-2 ��ϣ���� ������ T* put(const char* sKey)�����ַ�������ϣ����
//3����ͻ�����˳�ӷ�ʽ��
//���������ַ����ڹ�ϣ���ж�Ӧ��λ����ͬ��ô�죿����һ���������������޵ģ����ֿ����Ժܴ󡣽��������ķ����ܶ࣬�ܶ��㷨������ת���������������ֻҪ�ڹ�ϣ���ÿ����ڹ�һ�������������ж�Ӧ���ַ�����
//Ȼ��Blizzard�Ĺ�ϣ��û��ʹ������������"˳��"�ķ�ʽ��������⡣�����㷨�������ʵ�֣��ο������½� 2-2 ��ϣ��ʵ�� ������ INT_PTR getIndex(const char* sKey) const����
//4��У�鷽ʽ��������ϣֵ��
//�ڹ�ϣ���в�����һ����ϣֵ������������ϣֵ��У���ַ���������˵������ͬ���ַ�������һ����ϣ�㷨�õ�����ڵ�һ���п��ܣ�����������ͬ�Ĺ�ϣ�㷨�������ڵ㶼һ�£�������1:18889465931478580854784�������10�� 22.3�η���֮һ(ʹ��3�ε���ɢ�к�������)����һ����Ϸ������˵�㹻��ȫ�ˡ�

//2����ϣֵ����
//��1�����ܱ�
//��ϣ�������ӱ������������ַ�����Ӧ�Ĺ�ϣ�����ġ�
//���ܱ�
static unsigned long cryptTable[0x500];
//��ϣ���ӱ��Ƿ��ʼ��
static int cryptTableInited = 0;

//��ʼ�����ܱ�
//[cpp] view plain copy ��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
static void initCryptrTable()
{
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for( index1 = 0; index1 < 0x100; index1++ )
    {
        for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )
        {
            unsigned long temp1, temp2;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);
            cryptTable[index2] = ( temp1 | temp2 );    //��ʼ�����ܱ�
        }
    }
}


//��2���ַ������ɹ�ϣֵ
//�����ַ������ع�ϣֵ(�ַ�����ַ���������)��
//�ɼ��ܱ���ݹ�ϣ�㷨����������������ϣֵ����������㷨�ǰ���ѩ�ַ�����ϣ�㷨�����㣩
//[cpp] view plain copy ��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
unsigned long bzhashstr(const char *str, unsigned long seed)   //�ַ������������
{
    unsigned char *key = (unsigned char *)str;
    unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;//����1,2
    int ch;

    if (!cryptTableInited)
    {
        initCryptrTable();
        cryptTableInited = 1;
    }

    while(*key != 0)
    {
        ch = *key++;
        ch = toupper(ch);

        seed1 = cryptTable[(seed << 8) + ch] ^ (seed1 + seed2);//�ɼ��ܱ���������
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; //�޸�����2
    }
    return seed1;
}




//3����ϣ��
//��1����ϣ�����������
//�������ṩ��ȡ��ͷ�ͱ����Ľӿڡ������������������Ԫ�࣬������ʡ�
//[cpp] view plain copy ��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
template <typename T>
class CHashTableIterator
{
public:
    CHashTableIterator()
    {
        m_pTable = NULL;
        m_nIndex = 0;
    }
    CHashTableIterator(const CCustomHashTable<T> &table)
    {
        setTable(table);
    }
    inline void setTable(const CCustomHashTable<T> &table)
    {
        m_pTable = &table;
        m_nIndex = 0;
    }
    inline T* first() //���ص�һ����Ч��ϣ�ڵ��ֵ�ĵ�ַ
    {
        INT_PTR nLen = m_pTable->m_nLen;
        typename CCustomHashTable<T>::template HashNode<T> *pNode;

        m_nIndex = 0;
        while (m_nIndex < nLen)
        {
            pNode = &m_pTable->m_pTable[m_nIndex];
            m_nIndex++;
            if (pNode->hash1)//����Ƿ�����Ч�ڵ�
                return &pNode->value;
        }
        return NULL;
    }
    inline T* next()//������һ����Ч��ϣ�ڵ��ֵ�ĵ�ַ
    {
        INT_PTR nLen = m_pTable->m_nLen;
        typename CCustomHashTable<T>::template HashNode<T> *pNode;

        while (m_nIndex < nLen)
        {
            pNode = &m_pTable->m_pTable[m_nIndex];
            m_nIndex++;
            if (pNode->hash1)//����Ƿ�����Ч�ڵ�
                return &pNode->value;
        }
        return NULL;
    }
private:
    const CCustomHashTable<T>*m_pTable;
    INT_PTR             m_nIndex;
};


//��2����ϣ����
//�ṩ�����ķ��ʽӿڡ�
//������ڶ�����ڴ档�Ƴ������ʱ���������ڶ���
//[cpp] view plain copy ��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ
template <typename T>
class CCustomHashTable
{
    friend class CHashTableIterator<T>;
public:
    typedef CCustomHashTable<T> ClassType;

public:
    CCustomHashTable(size_t len = 0)
    {
        m_pTable = NULL;
        m_nLen = m_nFree = 0;
        m_nInitSize = len;
        if (len > MiniSize)
        {
            //��ĳ��ȱ�����2�Ĵη����������ϣ�±��㷨�޷�����
            size_t val;
            for (int i=0; i<32; ++i)
            {
                val = size_t(1 << i);
                if (len <= val)
                {
                    m_nInitSize = val;//��ʼ������Ϊ2�Ĵη������Ҵ��ڵ�������ĳ���len
                    break;
                }
            }
        }
        else m_nInitSize = MiniSize;//���Ƴ��ȱ�����2�Ĵη����������ϣ�±��㷨�޷�����
    }
    virtual ~CCustomHashTable()
    {
        clear();
    }
    //��չ�ϣ������ӿڻ���ñ��еĶ��������������
    void clear()
    {
        //ѭ��������������
        for (INT_PTR i=m_nLen-1; i>-1; --i)
        {
            if (m_pTable[i].hash1)
            {
                m_pTable[i].value.~T();//������ϣ���е����еĽڵ��ж�����ڴ�
            }
        }
        //�ͷ��ڴ�
        if (m_pTable) realloc(m_pTable, 0);
        m_pTable = NULL;
        m_nLen = m_nFree = 0;
    }
    //��ʾ��ϣ����
    void show()
    {
        printf("No hash1    hash2     hash3    valueaddr\n");
        //ѭ��������������
        for (INT_PTR i=m_nLen-1; i>-1; --i)
        {
            if (m_pTable[i].hash1)
            {
                printf("%-03u 0x%-08x 0x%-08x 0x%-08x 0x%-08x (data)\n",
                       i, m_pTable[i].hash1,m_pTable[i].hash2,m_pTable[i].hash3, &m_pTable[i].value);
            }
            else
            {
                printf("%-03u 0x%-08x 0x%-08x 0x%-08x 0x%-08x \n",
                       i, m_pTable[i].hash1,m_pTable[i].hash2,m_pTable[i].hash3, &m_pTable[i].value);
            }
        }
    }
    //��ȡ��Ч��������
    inline size_t count() const { return m_nLen - m_nFree; }
protected:
    /** �����ڲ�ʹ�õĹ�ϣ�ڵ����ݽṹ **/
    template <typename T1>
    class HashNode
    {
    public:
        unsigned int hash1; //��ϣֵ1
        unsigned int hash2; //��ϣֵ2
        unsigned int hash3; //��ϣֵ3
        T1 value;       //����ֵ
    };

    typedef HashNode<T> NodeType;
public:
    //ͨ��������ֵ
    inline T* get(const char* sKey)
    {
        INT_PTR idx = getIndex(sKey);//���ݼ���ȡ��ϣ���±�
        return (idx >= 0) ? &m_pTable[idx].value : NULL;
    }
    //ͨ��������ֵ
    inline const T* get(const char* sKey) const
    {
        INT_PTR idx = getIndex(sKey);
        return (idx >= 0) ? &m_pTable[idx].value : NULL;
    }


    /* ͨ�������ֵ�����غ��ʵĽڵ�ĵ�ַ��
    * ���һ��hash������ʹ�ã������������������������
    * �����ͷ��ʼ���ҿ�λ��ֱ���ҵ���λ�����һ�α��������˳�ӷ�ʽ��
    */
    inline T* put(const char* sKey)
    {
        unsigned int hash1, hash2, hash3, idx, start;
        NodeType *pNode;

        //�ڴ�ռ䲻�㣬�����ڴ�ռ䣨��չһ����
        if (m_nFree <= 0)
        {
            size_t oldlen = m_nLen;
            m_nLen = (oldlen <= 0) ? m_nInitSize : m_nLen << 1;//���ȱ�����2�Ĵη�
            m_nFree = m_nLen - oldlen;
            m_pTable = (NodeType *)realloc(m_pTable, m_nLen * sizeof(m_pTable[0]));//���·����ϣ��rehash��
            memset(&m_pTable[oldlen], 0, m_nFree * sizeof(m_pTable[0]));
        }

        hash1 = bzhashstr(sKey, 0);//���ַ����������������3����ϣֵ��ֻ��3����ϣֵ����ȵĲ�����ȵ��ַ�����
        hash2 = bzhashstr(sKey, 1);
        hash3 = bzhashstr(sKey, 2);
        start = idx = hash1 & (m_nLen - 1);//��hash1��λ�ÿ�ʼ����λ(��ĳ�����2�Ĵη�,���Լ�һ�����λ�����㣩
        do
        {
            pNode = &m_pTable[idx];
            //�����λ��û��ֵ�������õ���λ�ã���������ҵ�һ����λ��
            if (!pNode->hash1)//û��hash1ֵ��Ϊ�գ���ѽڵ���������ڸÿ�λ
            {
                pNode->hash1 = hash1;
                pNode->hash2 = hash2;//���øõ�Ĺ�ϣֵ2
                pNode->hash3 = hash3;//���øõ�Ĺ�ϣֵ3
                m_nFree--;
                new (&pNode->value)T();//���ù��캯����ʼ���ýڵ��еĶ���
                return &pNode->value;//���ؽڵ��ַ
            }
    #ifdef _DEBUG
            //�Ӹ�������Ϊ,3�ֹ�ϣֵ���ظ��ľ�����Ϊ���ظ���ӵ�
            else if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                //�������ظ���ӣ�����ȷʵ���ִ���
                DebugBreak();
            }
    #endif
            //����һλ����Ѱ��λ�ã����������ű����ҿ�λ��
            idx = (idx + 1) & (m_nLen - 1);//���ȱ�����2�Ĵη�����ʹ�����ֱ�����ʽ�������ⳬ������
        }
        while (start != idx);
        return NULL;//������һ��Ҳû���ҵ�����λ�����˳�������ʵ�����ǲ�����ֵģ���Ϊ�ռ䲻��ʱ����չ�ռ䣩
    }

    //ͨ��������ֵ
    inline INT_PTR update(const char* sKey, const T &value)
    {
        INT_PTR idx = getIndex(sKey);
        if (idx >= 0)
            m_pTable[idx].value = value;
        return idx;
    }
    //ͨ�����Ƴ�ֵ��û���ҵ��򷵻�-1
    inline INT_PTR remove(const char* sKey)
    {
        INT_PTR idx = getIndex(sKey);
        NodeType *pNode;
        if (idx >= 0)
        {
            pNode = &m_pTable[idx];
            pNode->hash1 = pNode->hash2 = pNode->hash3 = 0;
            m_nFree++;//��λ����
            pNode->value.~T();//����������������ýڵ��еĶ������ʼ��ʱ�Ĺ��캯�����Ӧ��
            return idx;
        }
        return -1;
    }
    //���ݹ�ϣ����ȡ�ڱ��е������������۰뷽ʽ���ң�����˳�ӷ�ʽ���ң�����������ϣֵ��飩
    INT_PTR getIndex(const char* sKey) const
    {
        unsigned int hash1, hash2, hash3;
        unsigned int idx, start;
        size_t len;
        NodeType *pNode;

        if (m_nLen <= 0)
            return -1;
        //���ݼ������ӻ�ȡ��ϣֵ
        hash1 = bzhashstr(sKey, 0);//�����ϣֵ1
        hash2 = bzhashstr(sKey, 1);//�����ϣֵ2
        hash3 = bzhashstr(sKey, 2);//�����ϣֵ3

        //���ȿ�ʼ�۰���ң�hash1����ȥ����λ�����ң�
        len = m_nLen;
        while (len >= m_nInitSize)
        {
            idx = hash1 & (len - 1);//��ĳ�����2�Ĵη�
            pNode = &m_pTable[idx];
            if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                return idx;//��ȡ��ϣֵ��Ӧ�Ľڵ���±�
            }
            len >>= 1;
        }

        //�۰���Ҳ������hash1λ��(hash1)��ʼ����������˳�ӻ�ȡ��
        start = idx = hash1 & (m_nLen - 1);//���ȱ�����2�Ĵη�
        do
        {
            pNode = &m_pTable[idx];
            if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                return idx;
            }
            idx = (idx + 1) & (m_nLen - 1);//���ȱ�����2�Ĵη�
        }
        while (start != idx);
        return -1;
    }

protected:
    //�ڴ����뺯����������c�����е�reallocʵ����ͬ��ʵ�����롢��չ�Լ��ͷ��ڴ�
    virtual void* realloc(void* p, size_t s)
    {
        return ::realloc(p, s);
    }
protected:
    size_t      m_nInitSize;//���ʼ����
    size_t      m_nLen;     //��ϣ��ĳ���,������2�Ĵη������ϣ�±��㷨�޷�����
    size_t      m_nFree;    //���нڵ�����
    HashNode<T>   *m_pTable;  //��ϣ��
public:
    static const size_t MiniSize = 16;//��ϣ����С���ȣ�������2�Ĵη������ϣ�±��㷨�޷�����
};

#endif // HASHTABLE_H
