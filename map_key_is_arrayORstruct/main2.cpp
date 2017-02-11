///******************************************************************
//      map的基本操作函数：
//      C++ Maps是一种关联式容器，包含“关键字/值”对
//      begin()          返回指向map头部的迭代器
//      clear(）         删除所有元素
//      count()          返回指定元素出现的次数
//      empty()          如果map为空则返回true
//      end()            返回指向map末尾的迭代器
//      equal_range()    返回特殊条目的迭代器对
//      erase()          删除一个元素
//      find()           查找一个元素
//      get_allocator()  返回map的配置器
//      insert()         插入元素
//      key_comp()       返回比较元素key的函数
//      lower_bound()    返回键值>=给定元素的第一个位置
//      max_size()       返回可以容纳的最大元素个数
//      rbegin()         返回一个指向map尾部的逆向迭代器
//      rend()           返回一个指向map头部的逆向迭代器
//      size()           返回map中元素的个数
//      swap()            交换两个map
//      upper_bound()     返回键值>给定元素的第一个位置
//      value_comp()      返回比较元素value的函数
//====================================================================
//1、map构造
//    map<int, string> mapStudent;

//2、map添加数据
//    mapStudent.insert(pair<int, string>(1, "student_one"));
//    mapStudent.insert(map<int, string>::value_type(2, "student_two"));
//    mapStudent[3] = "student_three";

//********************************************************************/
//#pragma warning (disable:4786)
//#include <map>
//#include <string>
//#include <iostream>

//using namespace std;

//int main()
//{
//    map<int, string> mapStudent;
//    cout<<"三种插入方式："<<endl;

//    mapStudent.insert(pair<int, string>(1, "student_one"));
//    mapStudent.insert(map<int, string>::value_type(2, "student_two"));
//    mapStudent[3] = "student_three";
//    mapStudent.insert(map<int, string>::value_type(4, "student_four"));

//    pair<map<int,string>::iterator,bool> InsertPair;   //判断是否插入成功
//    InsertPair = mapStudent.insert(map<int,string>::value_type(5,"student_five"));
//    if(InsertPair.second == true)
//    {
//        //cout<<InsertPair.first.operator++<<endl;  //求解？？不知道怎么应用第一个数据
//    }

//    cout<<"三种遍历方式："<<endl;

//    map<int, string>::iterator  iter;
//    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
//    {
//        cout<<iter->first<<" "<<iter->second<<endl;
//    }

//    map<int, string>::reverse_iterator  iters;
//    for(iters = mapStudent.rbegin(); iters != mapStudent.rend(); iters++)
//    {
//        cout<<iters->first<<" "<<iters->second<<endl;
//    }  //逆序输出
//    cout<<"数组的输出形式:"<<endl;
//    for(unsigned int iIndex=0;iIndex < mapStudent.size();iIndex++) //size()返回成员的个数
//    {
//        cout<<mapStudent[iIndex]<<endl;
//    }
//    cout<<mapStudent.count(1)<<endl;  //count()判断关键字是否存在，返回1表示存在，0
//    iter = mapStudent.find(1);        //find()关键字存在时，返回数据所在位置的迭代器，否则返回end()返回的迭代器
//    if( iter != mapStudent.end() )
//    {
//        cout<<"数据存在："<<iter->first<<" "<<iter->second<<endl;
//        mapStudent.erase(iter);        //用迭代删除数据
//    }
//    else
//    {
//        cout<<"数据不存在！"<<endl;
//    }
//    int n = mapStudent.erase(3);        //用关键字删除，如果删除了会返回1，否则返回0

//    iter = mapStudent.lower_bound(2);   //返回2的迭代器
//    cout<<iter->second<<endl;
//    iter = mapStudent.upper_bound(2);   //返回3的迭代器
//    cout<<iter->second<<endl;

//    /*Equal_range函数返回一个pair，pair里面第一个变量是Lower_bound返回的迭代器，pair里面第二个迭代器是Upper_bound返回的迭代器，如果这两个迭代器相等的话，则说明map中不出现这个关键字*/
//    pair<map<int,string>::iterator,map<int,string>::iterator> MapPair;
//    MapPair = mapStudent.equal_range(2);
//    if( MapPair.first == MapPair.second )
//    {
//        cout<<"Do not find"<<endl;
//    }
//    else
//    {
//        cout<<"Find"<<endl;
//    }

//    MapPair = mapStudent.equal_range(3);
//    if( MapPair.first == MapPair.second )
//    {
//        cout<<"Do not find"<<endl;
//    }
//    else
//    {
//        cout<<"Find"<<endl;
//    }

//    //删除一个前闭后开的集合，这是STL的特性
//    mapStudent.erase(mapStudent.begin(), mapStudent.end());

//    return 0;

//}
