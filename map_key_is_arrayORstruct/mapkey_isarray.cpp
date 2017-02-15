/******************************************************************
      map�Ļ�������������
      C++ Maps��һ�ֹ���ʽ�������������ؼ���/ֵ����
      begin()          ����ָ��mapͷ���ĵ�����
      clear(��         ɾ������Ԫ��
      count()          ����ָ��Ԫ�س��ֵĴ���
      empty()          ���mapΪ���򷵻�true
      end()            ����ָ��mapĩβ�ĵ�����
      equal_range()    ����������Ŀ�ĵ�������
      erase()          ɾ��һ��Ԫ��
      find()           ����һ��Ԫ��
      get_allocator()  ����map��������
      insert()         ����Ԫ��
      key_comp()       ���رȽ�Ԫ��key�ĺ���
      lower_bound()    ���ؼ�ֵ>=����Ԫ�صĵ�һ��λ��
      max_size()       ���ؿ������ɵ����Ԫ�ظ���
      rbegin()         ����һ��ָ��mapβ�������������
      rend()           ����һ��ָ��mapͷ�������������
      size()           ����map��Ԫ�صĸ���
      swap()            ��������map
      upper_bound()     ���ؼ�ֵ>����Ԫ�صĵ�һ��λ��
      value_comp()      ���رȽ�Ԫ��value�ĺ���
====================================================================
1��map����
    map<int, string> mapPort;

2��map�������
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
    cout<<"���ֲ��뷽ʽ��"<<endl;

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
    pair<map<GLOBAL_PORT,string>::iterator,bool> InsertPair;   //�ж��Ƿ����ɹ�
    InsertPair = mapPort.insert(map<GLOBAL_PORT,string>::value_type(tport,"student_five"));
    if(InsertPair.second == true)
    {
        //cout<<InsertPair.first.operator++<<endl;  //��⣿����֪����ôӦ�õ�һ������
    }

    cout<<"���ֱ�����ʽ��"<<endl;

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
    }  //�������
//    cout<<"����������ʽ:"<<endl;
//    for(unsigned int iIndex=0;iIndex < mapPort.size();iIndex++) //size()���س�Ա�ĸ���
//    {
//        cout<<mapPort[iIndex]<<endl;
//    }
    memset(tport.data, '5', sizeof(tport));
    cout<<mapPort.count(tport)<<endl;  //count()�жϹؼ����Ƿ���ڣ�����1��ʾ���ڣ�0
    iter = mapPort.find(tport);        //find()�ؼ��ִ���ʱ��������������λ�õĵ����������򷵻�end()���صĵ�����
    if( iter != mapPort.end() )
    {
        cout<<"���ݴ��ڣ�";
        tport = iter->first;
        print_GLOBAL_PORT(tport);
        cout<<" "<<iter->second<<endl;
        mapPort.erase(iter);        //�õ���ɾ������
    }
    else
    {
        cout<<"���ݲ����ڣ�"<<endl;
    }
    memset(tport.data, '3', sizeof(tport));
    int n = mapPort.erase(tport);        //�ùؼ���ɾ�������ɾ���˻᷵��1�����򷵻�0

    memset(tport.data, '2', sizeof(tport));
    iter = mapPort.lower_bound(tport);   //����2�ĵ�����
    cout<<iter->second<<endl;
    iter = mapPort.upper_bound(tport);   //����3�ĵ�����
    cout<<iter->second<<endl;

    /*Equal_range��������һ��pair��pair�����һ��������Lower_bound���صĵ�������pair����ڶ�����������Upper_bound���صĵ������������������������ȵĻ�����˵��map�в���������ؼ���*/
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

    //ɾ��һ��ǰ�պ󿪵ļ��ϣ�����STL������
    mapPort.erase(mapPort.begin(), mapPort.end());

    return 0;

}
