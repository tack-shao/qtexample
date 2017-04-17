#include <iostream>
#include "hashtable.h"

using namespace std;

#pragma pack(1)
typedef struct T_HashInfo{
    int dwaddr   ;    /*  */
    int seq      ;    /*  */
    char buf[108];    /*  */
    float tax     ;    /*  */
    char bigdata[900*1024];
    char test;
    unsigned int samplenum;
    unsigned int sampleport[123];
}T_HashInfo, *P_HashInfo;

#pragma pack()


CCustomHashTable<T_HashInfo> hash_test(10);
void print_hashinfo();


template<typename T>
T* GetHashItem(CCustomHashTable<T> &hash, int dwaddr)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%u", dwaddr);
    T *ptmp = hash.get(sKey);
    if(ptmp)
    {
        return ptmp;
    }
    else
    {
//        printf("put hash value error!!!\n");
    }
    return NULL;
}

template<typename T>
void UpdateHashItem(CCustomHashTable<T> &hash, T * val)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%u", val->dwaddr);
    T *ptmp = hash.put(sKey);
    if(ptmp)
    {
        *ptmp = *val;
    }
    else
    {
        printf("put hash value error!!!\n");
    }

}

template<typename T>
void RemoveHashItem(CCustomHashTable<T> &hash, T * val)
{
    char sKey[32] = {0};
    snprintf(sKey, sizeof(sKey), "%d", val->dwaddr);
    int ret = hash.remove(sKey);
    if(-1 != ret)
    {
        printf("remove ok, hash remove item!!!\n");
    }
    else
    {
        printf("no data, hash remove item!!!,key:%#x\n", val->dwaddr);
    }

}



void hash_test1(void)
{
    printf("hash_test1 , beging hash size:%u\n", hash_test.count());
    int i  =  0;
    int LoopNum = 100;
    T_HashInfo tInfo = {0};
    P_HashInfo pInfo = NULL;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "0x%d", i);
        UpdateHashItem(hash_test, &tInfo);
    }
    print_hashinfo();
    printf("after update, hash size:%u\n", hash_test.count());

    LoopNum = 50;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "%d", i);
        RemoveHashItem(hash_test, &tInfo);
    }
    print_hashinfo();
    printf("after delete, hash size:%u\n", hash_test.count());


    printf("get data testing......., hash size:%u\n", hash_test.count());
    LoopNum = 50;
    for( i  =  0 ; i < LoopNum; i++ )
    {
        memset(&tInfo, 0, sizeof(tInfo));
        tInfo.dwaddr = 0x101 + i;
        tInfo.seq = 1 + i;
        tInfo.tax = 0.0 + i;
        sprintf(tInfo.buf, "%d", i);
        pInfo = GetHashItem(hash_test, tInfo.dwaddr);
        if(pInfo)
        {
//            *pInfo = tInfo;
            printf("got data, key:%#x\n", pInfo->dwaddr);
        }
        else
        {
            printf("no data, key:%#x\n", tInfo.dwaddr);
        }
//        UpdateHashItem(hash_test, &tInfo);
    }

    print_hashinfo();
    printf("after get method again, hash size:%u\n", hash_test.count());



//    set_integer(&hash_test, "1", 1);
//    set_integer(&hash_test, "2", 2);
//    set_integer(&hash_test, "2", 2);


//    printf("after delete, hash size:%u\n", hash_test.count());

//    CHashTableIterator<CCustomHashTable<int>> it;

}


void print_hashinfo()
{
    CHashTableIterator<T_HashInfo> tobj(hash_test);
    T_HashInfo *pIt = NULL;
    T_HashInfo *pInfo = NULL;
    printf("hash key!!\n");
    int dNo = 1;
    printf("No pInfo  dwaddr seq  tax  buf (iter)\n");
    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
    {
        pInfo = pIt;
        if(!pInfo)
        {
            printf("got no data (iter)\n");
            continue;
        }
        printf("%-03u 0x%-08x 0x%-04x %-03u %-06.2f %-3s\n",
               dNo, pInfo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
    }
    dNo = 1;
    printf("\nNo pInfo  dwaddr seq  tax  buf (by GetHashItem)\n");
    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
    {
        pInfo = GetHashItem(hash_test, pIt->dwaddr);
        if(!pInfo)
        {
            printf("got no data (by GetHashItem)\n");
            continue;
        }
        printf("%-03u 0x%-08x 0x%-04x %-03u %-06.2f %-3s\n",
               dNo, pInfo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
    }
    printf("hash show\n");
    hash_test.show();
    printf("hash size:%u\n", hash_test.count());
}


void clear_hashinfo()
{
//    CHashTableIterator<T_HashInfo> tobj(hash_test);
//    T_HashInfo *pIt = NULL;
//    T_HashInfo *pInfo = NULL;
//    printf("hash key!!\n");
//    int dNo = 1;
//    printf("No  dwaddr seq  tax  buf (iter)\n");
//    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
//    {
//        pInfo = pIt;
//        if(!pInfo)
//        {
//            printf("got no data (iter)\n");
//            continue;
//        }
//        printf("%-03u 0x%-04x %-03u %-06.2f %-3s\n",
//               dNo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
//    }
//    dNo = 1;
//    printf("\nNo  dwaddr seq  tax  buf (by GetHashItem)\n");
//    for(pIt = tobj.first(); pIt != NULL; pIt = tobj.next(), dNo++)
//    {
//        pInfo = GetHashItem(hash_test, pIt->dwaddr);
//        if(!pInfo)
//        {
//            printf("got no data (by GetHashItem)\n");
//            continue;
//        }
//        printf("%-03u 0x%-04x %-03u %-06.2f %-3s\n",
//               dNo, pInfo->dwaddr, pInfo->seq, pInfo->tax, pInfo->buf);
//    }
    printf("hash clear\n");
    hash_test.clear();
    printf("hash show\n");
    hash_test.show();
    printf("hash size:%u\n", hash_test.count());
}

void print_hash_userdatasize()
{
    printf("sizeof(T_HashInfo):%u\n", sizeof(T_HashInfo));
}

int main()
{
    hash_test1();;
    print_hashinfo();
    print_hash_userdatasize();
    clear_hashinfo();
    cout << "Hello World!" << endl;
    return 0;
}



/*
>>> 0x245e1b0 - 0x2447534
93308
>>> 0x245e1b0 - 0x2447534 - 93296
12
>>> 0x1738ca8 - 0x172202c
93308
>>>

*/





/*
>>> 0x16f4cac - 0x16de02c - 93300
12
>>>

*/



/*


*/







