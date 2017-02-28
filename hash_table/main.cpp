#include <iostream>
#include "hashtable.h"

using namespace std;

void set_integer(CCustomHashTable<int> *phash, const char* sKey, int val)
{
    int *ptmp = phash->put(sKey);
    if(ptmp)
    {
        *ptmp = val;
    }
    else
    {
        printf("put hash value error!!!\n");
    }

}

void print_integer_hash()
{
}

void hash_test1(void)
{
    CCustomHashTable<int> hash_interger(10);
    set_integer(&hash_interger, "1", 1);
    set_integer(&hash_interger, "2", 2);
//    set_integer(&hash_interger, "2", 2);



    printf("integer hash size:%u\n", hash_interger.count());
//    CHashTableIterator<CCustomHashTable<int>> it;

}


int main()
{
    hash_test1();
    cout << "Hello World!" << endl;
    return 0;
}

