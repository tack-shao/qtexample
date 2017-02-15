/******************************************************************
      map的基本操作函数：
      C++ Maps是一种关联式容器，包含“关键字/值”对
      begin()          返回指向map头部的迭代器
      clear(）         删除所有元素
      count()          返回指定元素出现的次数
      empty()          如果map为空则返回true
      end()            返回指向map末尾的迭代器
      equal_range()    返回特殊条目的迭代器对
      erase()          删除一个元素
      find()           查找一个元素
      get_allocator()  返回map的配置器
      insert()         插入元素
      key_comp()       返回比较元素key的函数
      lower_bound()    返回键值>=给定元素的第一个位置
      max_size()       返回可以容纳的最大元素个数
      rbegin()         返回一个指向map尾部的逆向迭代器
      rend()           返回一个指向map头部的逆向迭代器
      size()           返回map中元素的个数
      swap()            交换两个map
      upper_bound()     返回键值>给定元素的第一个位置
      value_comp()      返回比较元素value的函数
====================================================================
1、map构造
    map<int, string> mapPort;

2、map添加数据
    mapPort.insert(pair<int, string>(1, "student_one"));
    mapPort.insert(map<int, string>::value_type(2, "student_two"));
    mapPort[3] = "student_three";

********************************************************************/
#pragma warning (disable:4786)
#include <map>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


using namespace std;

#define PORTSIZE_MAX (32L)
#define ARRAYSIZE(A) (unsigned int)(sizeof(A) / sizeof(A[0]))

typedef struct GLOBAL_PORT
{
    int data[PORTSIZE_MAX];
}GLOBAL_PORT;



class sort

{
public:
    bool operator() (GLOBAL_PORT const &_A, GLOBAL_PORT const &_B) const
    {
//        if(memcmp(_A.data, _B.data, sizeof(GLOBAL_PORT)) < 0)
//            return true;
        uint32_t lp = 0;
        for(lp = 0;  lp < ARRAYSIZE(_A.data); lp++)
        {
            if (_A.data[lp] < _B.data[lp])
                return true;
        }
        return false;
    }

};



void print_GLOBAL_PORT(GLOBAL_PORT tport)
{
//    cout << tport.data[0];
    for(int i = 0; i < ARRAYSIZE(tport.data); i++)
    {
        cout << tport.data[i] << " ";
    }
}



int main()
{
    srand(time(NULL));
    map<GLOBAL_PORT, string, sort> mapPort;
    cout<<"三种插入方式："<<endl;

    GLOBAL_PORT tport = {0};
    memset(tport.data, '1', sizeof(tport));
    mapPort.insert(pair<GLOBAL_PORT, string>(tport, "student_one"));
    memset(tport.data, '2', sizeof(tport));
    mapPort.insert(map<GLOBAL_PORT, string>::value_type(tport, "student_two"));
    memset(tport.data, '3', sizeof(tport));
    mapPort[tport] = "student_three";
    memset(tport.data, '4', sizeof(tport));
    mapPort.insert(map<GLOBAL_PORT, string>::value_type(tport, "student_four"));

    cout<<"mapPort size:"<<mapPort.size();


    memset(tport.data, '5', sizeof(tport));
    pair<map<GLOBAL_PORT,string>::iterator,bool> InsertPair;   //判断是否插入成功
    InsertPair = mapPort.insert(map<GLOBAL_PORT,string>::value_type(tport,"student_five"));
    if(InsertPair.second == true)
    {
        //cout<<InsertPair.first.operator++<<endl;  //求解？？不知道怎么应用第一个数据
    }

    cout<<"三种遍历方式："<<endl;

    map<GLOBAL_PORT, string>::iterator  iter;
    for(iter = mapPort.begin(); iter != mapPort.end(); iter++)
    {
        tport = iter->first;
        print_GLOBAL_PORT(tport);
        cout<<" "<<iter->second<<endl;
    }

    map<GLOBAL_PORT, string>::reverse_iterator  iters;
    for(iters = mapPort.rbegin(); iters != mapPort.rend(); iters++)
    {
        tport = iter->first;
        print_GLOBAL_PORT(tport);
        cout<<" "<<iters->second<<endl;
    }  //逆序输出
//    cout<<"数组的输出形式:"<<endl;
//    for(unsigned int iIndex=0;iIndex < mapPort.size();iIndex++) //size()返回成员的个数
//    {
//        cout<<mapPort[iIndex]<<endl;
//    }
    memset(tport.data, '5', sizeof(tport));
    cout<<mapPort.count(tport)<<endl;  //count()判断关键字是否存在，返回1表示存在，0
    iter = mapPort.find(tport);        //find()关键字存在时，返回数据所在位置的迭代器，否则返回end()返回的迭代器
    if( iter != mapPort.end() )
    {
        cout<<"数据存在：";
        tport = iter->first;
        print_GLOBAL_PORT(tport);
        cout<<" "<<iter->second<<endl;
        mapPort.erase(iter);        //用迭代删除数据
    }
    else
    {
        cout<<"数据不存在！"<<endl;
    }
    memset(tport.data, '3', sizeof(tport));
    int n = mapPort.erase(tport);        //用关键字删除，如果删除了会返回1，否则返回0

    memset(tport.data, '2', sizeof(tport));
    iter = mapPort.lower_bound(tport);   //返回2的迭代器
    cout<<iter->second<<endl;
    iter = mapPort.upper_bound(tport);   //返回3的迭代器
    cout<<iter->second<<endl;

    /*Equal_range函数返回一个pair，pair里面第一个变量是Lower_bound返回的迭代器，pair里面第二个迭代器是Upper_bound返回的迭代器，如果这两个迭代器相等的话，则说明map中不出现这个关键字*/
    pair<map<GLOBAL_PORT,string>::iterator,map<GLOBAL_PORT,string>::iterator> MapPair;
    MapPair = mapPort.equal_range(tport);
    if( MapPair.first == MapPair.second )
    {
        cout<<"Do not find"<<endl;
    }
    else
    {
        cout<<"Find"<<endl;
    }

    memset(tport.data, '3', sizeof(tport));
    MapPair = mapPort.equal_range(tport);
    if( MapPair.first == MapPair.second )
    {
        cout<<"Do not find"<<endl;
    }
    else
    {
        cout<<"Find"<<endl;
    }

    //删除一个前闭后开的集合，这是STL的特性
    mapPort.erase(mapPort.begin(), mapPort.end());

    return 0;

}
