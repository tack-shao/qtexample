#ifndef HASHTABLE_H
#define HASHTABLE_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define INT_PTR int

//其中：小写字母转成大写字母
#define toupper(c) (((c) >= 'a' && (c) <= 'z') ? (c) ^ 0x20 : (c))



template <typename T>
class CCustomHashTable;

//字符串为键的自定义哈希表(暴雪字符串哈希算法)
//2014-07-12 00:19 943人阅读 评论(0) 收藏 举报
// 分类： 自定义c++容器（13）   算法（16）
//版权声明：本文为博主原创文章，未经博主允许不得转载。
//目录(?)[+]
//这是个在暴雪字符串哈希算法基础上实现的哈希表。在代码实现上有一定优化。
//设计上：
//1）加密表是足够长的(unsigned long)无符号型数组。数组的值是由算法计算的固定的一些值。加密表是用来计算字符串（在某种子的情况下）的哈希值。
//2）哈希值是字符串（大写）的所有的字符的ascii码相关的。使用单向散列函数，从概率上认为，不同字符串的3种不同的种子的3个哈希值不会是都是相同的。(计算的是10的22.3次方分之一的概率)
//3）每个节点有3个hash值（hash1，hash2，hash3），hash1 是寻位的基准，hash2，hash3 是判断节点是否相同的标准。
//4）hash1值冲突的解决方式是，从hash1开始遍历表并获取空位（顺延方式）
//5）把表查找字符串键优化为比较三个整形键值（先使用折半方式，然后顺延方式查找。因为表内存不够时是会拓展一倍内存的）
//6）表长度是2的次幂，最小是16。表内存不够时可以拓展一倍，由空闲位置计数器来判断

//特点：
//(1)插入
//使用顺延方式查找空位，没有使用链表。节省内存空间。
//(2)查找
//1)先使用折半方式，然后顺延方式查找。
//因为表内存不够时是会拓展一倍内存的 。先通过hash1不断去掉高位的方式来检查能适应表内存拓展方式和哈希取余方式
//2)三哈希值比较方式来检查:
//比较键值是比较3个整形数，而不是字符串，可以提高查找比较效率
//(3)移除
//查找到节点后，设置该节点的哈希值为0，并显式调用节点的值对象的析构函数
//1、hash算法理论
//1)hash值
//从字符串数组中查找匹配的字符串最合适的算法自然是使用哈希表。所谓Hash，一般是一个整数，通过某种算法，可以把一个字符串"压缩" 成一个整数，这个数称为Hash，当然，无论如何，一个32位整数是无法对应回一个字符串的，但如果有合适的校验方式，两个字符串计算出的Hash值相等的可能非常小。
//2）hash函数（单向散列函数）
//Blizzard的哈希算法是非常高效的(代码实现可参考 章节 1-2 由加密表随机种子(bzhashstr))，使用的是单向散列函数(One-Way Hash)，举个例子，字符串"unitneutralacritter.grp"通过这个算法得到的结果是0xA26067F3。
//通常是构造一个数组来作为哈希表，这个数组的容量根据程序的要求来定义（如1024），每一个Hash值通过位与运算对应到数组中的一个位置，只要检查这个字符串的哈希值对的位置有没有被占用。最快的复杂度是 O(1)。算法计算代码实现参考章节 3-2 哈希表定义 （函数 T* put(const char* sKey)加入字符串到哈希表）。
//3）冲突解决（顺延方式）
//假如两个字符串在哈希表中对应的位置相同怎么办？究竟一个数组容量是有限的，这种可能性很大。解决该问题的方法很多，很多算法都可以转化成链表来解决，只要在哈希表的每个入口挂一个链表，保存所有对应的字符串。
//然而Blizzard的哈希表没有使用链表，而采用"顺延"的方式来解决问题。具体算法计算代码实现，参考本文章节 2-2 哈希表实现 （函数 INT_PTR getIndex(const char* sKey) const）。
//4）校验方式（三个哈希值）
//在哈希表中不是用一个哈希值而是用三个哈希值来校验字符串。假如说两个不同的字符串经过一个哈希算法得到的入口点一致有可能，但用三个不同的哈希算法算出的入口点都一致，几率是1:18889465931478580854784，大概是10的 22.3次方分之一(使用3次单向散列函数运算)，对一个游戏程序来说足够安全了。

//2、哈希值计算
//（1）加密表
//哈希运算种子表是用来计算字符串对应的哈希整数的。
//加密表
static unsigned long cryptTable[0x500];
//哈希种子表是否初始化
static int cryptTableInited = 0;

//初始化加密表
//[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
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
            cryptTable[index2] = ( temp1 | temp2 );    //初始化加密表
        }
    }
}


//（2）字符串生成哈希值
//根据字符串返回哈希值(字符串地址，随机种子)。
//由加密表根据哈希算法和随机种子来计算哈希值。（随机数算法是按暴雪字符串哈希算法来计算）
//[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
unsigned long bzhashstr(const char *str, unsigned long seed)   //字符串，随机种子
{
    unsigned char *key = (unsigned char *)str;
    unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;//种子1,2
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

        seed1 = cryptTable[(seed << 8) + ch] ^ (seed1 + seed2);//由加密表计算出的数
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; //修改种子2
    }
    return seed1;
}




//3、哈希表
//（1）哈希表迭代器定义
//迭代器提供获取表头和遍历的接口。迭代器是容器类的友元类，方便访问。
//[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
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
    inline T* first() //返回第一个有效哈希节点的值的地址
    {
        INT_PTR nLen = m_pTable->m_nLen;
        typename CCustomHashTable<T>::template HashNode<T> *pNode;

        m_nIndex = 0;
        while (m_nIndex < nLen)
        {
            pNode = &m_pTable->m_pTable[m_nIndex];
            m_nIndex++;
            if (pNode->hash1)//检查是否是有效节点
                return &pNode->value;
        }
        return NULL;
    }
    inline T* next()//返回下一个有效哈希节点的值的地址
    {
        INT_PTR nLen = m_pTable->m_nLen;
        typename CCustomHashTable<T>::template HashNode<T> *pNode;

        while (m_nIndex < nLen)
        {
            pNode = &m_pTable->m_pTable[m_nIndex];
            m_nIndex++;
            if (pNode->hash1)//检查是否是有效节点
                return &pNode->value;
        }
        return NULL;
    }
private:
    const CCustomHashTable<T>*m_pTable;
    INT_PTR             m_nIndex;
};


//（2）哈希表定义
//提供表对象的访问接口。
//管理表内对象的内存。移除和清除时会析构表内对象。
//[cpp] view plain copy 在CODE上查看代码片派生到我的代码片
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
            //表的长度必须是2的次方数，否则哈希下标算法无法工作
            size_t val;
            for (int i=0; i<32; ++i)
            {
                val = size_t(1 << i);
                if (len <= val)
                {
                    m_nInitSize = val;//初始化长度为2的次方数，且大于等于需求的长度len
                    break;
                }
            }
        }
        else m_nInitSize = MiniSize;//限制长度必须是2的次方数，否则哈希下标算法无法工作
    }
    virtual ~CCustomHashTable()
    {
        clear();
    }
    //清空哈希表（这个接口会调用表中的对象的析构函数）
    void clear()
    {
        //循环调用析构函数
        for (INT_PTR i=m_nLen-1; i>-1; --i)
        {
            if (m_pTable[i].hash1)
            {
                m_pTable[i].value.~T();//析构哈希表中的所有的节点中对象的内存
            }
        }
        //释放内存
        if (m_pTable) realloc(m_pTable, 0);
        m_pTable = NULL;
        m_nLen = m_nFree = 0;
    }
    //显示哈希表（）
    void show()
    {
        printf("No hash1    hash2     hash3    valueaddr\n");
        //循环调用析构函数
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
    //获取有效对象数量
    inline size_t count() const { return m_nLen - m_nFree; }
protected:
    /** 定义内部使用的哈希节点数据结构 **/
    template <typename T1>
    class HashNode
    {
    public:
        unsigned int hash1; //哈希值1
        unsigned int hash2; //哈希值2
        unsigned int hash3; //哈希值3
        T1 value;       //数据值
    };

    typedef HashNode<T> NodeType;
public:
    //通过键查找值
    inline T* get(const char* sKey)
    {
        INT_PTR idx = getIndex(sKey);//根据键获取哈希表下标
        return (idx >= 0) ? &m_pTable[idx].value : NULL;
    }
    //通过键查找值
    inline const T* get(const char* sKey) const
    {
        INT_PTR idx = getIndex(sKey);
        return (idx >= 0) ? &m_pTable[idx].value : NULL;
    }


    /* 通过键添加值（返回合适的节点的地址）
    * 如果一个hash索引被使用，则向后递推索引，到达最大索
    * 引则从头开始查找空位，直到找到空位或完成一次表遍历。（顺延方式）
    */
    inline T* put(const char* sKey)
    {
        unsigned int hash1, hash2, hash3, idx, start;
        NodeType *pNode;

        //内存空间不足，增长内存空间（拓展一倍）
        if (m_nFree <= 0)
        {
            size_t oldlen = m_nLen;
            m_nLen = (oldlen <= 0) ? m_nInitSize : m_nLen << 1;//表长度必须是2的次方
            m_nFree = m_nLen - oldlen;
            m_pTable = (NodeType *)realloc(m_pTable, m_nLen * sizeof(m_pTable[0]));//重新分配哈希表（rehash）
            memset(&m_pTable[oldlen], 0, m_nFree * sizeof(m_pTable[0]));
        }

        hash1 = bzhashstr(sKey, 0);//由字符串和随机种子生成3个哈希值（只有3个哈希值都相等的才是相等的字符串）
        hash2 = bzhashstr(sKey, 1);
        hash3 = bzhashstr(sKey, 2);
        start = idx = hash1 & (m_nLen - 1);//从hash1的位置开始检查空位(表的长度是2的次方,所以减一后可以位与运算）
        do
        {
            pNode = &m_pTable[idx];
            //如果该位置没有值，则设置到该位置，否则向后找到一个空位置
            if (!pNode->hash1)//没有hash1值则为空，则把节点对象设置在该空位
            {
                pNode->hash1 = hash1;
                pNode->hash2 = hash2;//设置该点的哈希值2
                pNode->hash3 = hash3;//设置该点的哈希值3
                m_nFree--;
                new (&pNode->value)T();//调用构造函数初始化该节点中的对象
                return &pNode->value;//返回节点地址
            }
    #ifdef _DEBUG
            //从概率上认为,3种哈希值都重复的就是认为是重复添加的
            else if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                //调用者重复添加，或者确实出现错误！
                DebugBreak();
            }
    #endif
            //从下一位继续寻找位置（遍历了整张表来找空位）
            idx = (idx + 1) & (m_nLen - 1);//表长度必须是2的次方才能使用这种遍历方式，并避免超出长度
        }
        while (start != idx);
        return NULL;//遍历了一遍也没有找到合适位置则退出（这里实际上是不会出现的，因为空间不够时会拓展空间）
    }

    //通过键更新值
    inline INT_PTR update(const char* sKey, const T &value)
    {
        INT_PTR idx = getIndex(sKey);
        if (idx >= 0)
            m_pTable[idx].value = value;
        return idx;
    }
    //通过键移除值，没有找到则返回-1
    inline INT_PTR remove(const char* sKey)
    {
        INT_PTR idx = getIndex(sKey);
        NodeType *pNode;
        if (idx >= 0)
        {
            pNode = &m_pTable[idx];
            pNode->hash1 = pNode->hash2 = pNode->hash3 = 0;
            m_nFree++;//空位增加
            pNode->value.~T();//调用析构函数处理该节点中的对象（与初始化时的构造函数相对应）
            return idx;
        }
        return -1;
    }
    //根据哈希键获取在表中的索引（先用折半方式查找，后用顺延方式查找，根据三个哈希值检查）
    INT_PTR getIndex(const char* sKey) const
    {
        unsigned int hash1, hash2, hash3;
        unsigned int idx, start;
        size_t len;
        NodeType *pNode;

        if (m_nLen <= 0)
            return -1;
        //根据键和种子获取哈希值
        hash1 = bzhashstr(sKey, 0);//计算哈希值1
        hash2 = bzhashstr(sKey, 1);//计算哈希值2
        hash3 = bzhashstr(sKey, 2);//计算哈希值3

        //首先开始折半查找（hash1不断去掉高位来查找）
        len = m_nLen;
        while (len >= m_nInitSize)
        {
            idx = hash1 & (len - 1);//表的长度是2的次方
            pNode = &m_pTable[idx];
            if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                return idx;//获取哈希值对应的节点的下标
            }
            len >>= 1;
        }

        //折半查找不到则从hash1位置(hash1)开始遍历整个表（顺延获取）
        start = idx = hash1 & (m_nLen - 1);//表长度必须是2的次方
        do
        {
            pNode = &m_pTable[idx];
            if (pNode->hash1 == hash1 && pNode->hash2 == hash2 && pNode->hash3 == hash3)
            {
                return idx;
            }
            idx = (idx + 1) & (m_nLen - 1);//表长度必须是2的次方
        }
        while (start != idx);
        return -1;
    }

protected:
    //内存申请函数，作用与c函数中的realloc实现相同，实现申请、扩展以及释放内存
    virtual void* realloc(void* p, size_t s)
    {
        return ::realloc(p, s);
    }
protected:
    size_t      m_nInitSize;//表初始长度
    size_t      m_nLen;     //哈希表的长度,必须是2的次方否则哈希下标算法无法工作
    size_t      m_nFree;    //空闲节点数量
    HashNode<T>   *m_pTable;  //哈希表
public:
    static const size_t MiniSize = 16;//哈希表最小长度，必须是2的次方否则哈希下标算法无法工作
};

#endif // HASHTABLE_H
