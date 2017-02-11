///******************************************************************
//      map�Ļ�������������
//      C++ Maps��һ�ֹ���ʽ�������������ؼ���/ֵ����
//      begin()          ����ָ��mapͷ���ĵ�����
//      clear(��         ɾ������Ԫ��
//      count()          ����ָ��Ԫ�س��ֵĴ���
//      empty()          ���mapΪ���򷵻�true
//      end()            ����ָ��mapĩβ�ĵ�����
//      equal_range()    ����������Ŀ�ĵ�������
//      erase()          ɾ��һ��Ԫ��
//      find()           ����һ��Ԫ��
//      get_allocator()  ����map��������
//      insert()         ����Ԫ��
//      key_comp()       ���رȽ�Ԫ��key�ĺ���
//      lower_bound()    ���ؼ�ֵ>=����Ԫ�صĵ�һ��λ��
//      max_size()       ���ؿ������ɵ����Ԫ�ظ���
//      rbegin()         ����һ��ָ��mapβ�������������
//      rend()           ����һ��ָ��mapͷ�������������
//      size()           ����map��Ԫ�صĸ���
//      swap()            ��������map
//      upper_bound()     ���ؼ�ֵ>����Ԫ�صĵ�һ��λ��
//      value_comp()      ���رȽ�Ԫ��value�ĺ���
//====================================================================
//1��map����
//    map<int, string> mapStudent;

//2��map�������
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
//    cout<<"���ֲ��뷽ʽ��"<<endl;

//    mapStudent.insert(pair<int, string>(1, "student_one"));
//    mapStudent.insert(map<int, string>::value_type(2, "student_two"));
//    mapStudent[3] = "student_three";
//    mapStudent.insert(map<int, string>::value_type(4, "student_four"));

//    pair<map<int,string>::iterator,bool> InsertPair;   //�ж��Ƿ����ɹ�
//    InsertPair = mapStudent.insert(map<int,string>::value_type(5,"student_five"));
//    if(InsertPair.second == true)
//    {
//        //cout<<InsertPair.first.operator++<<endl;  //��⣿����֪����ôӦ�õ�һ������
//    }

//    cout<<"���ֱ�����ʽ��"<<endl;

//    map<int, string>::iterator  iter;
//    for(iter = mapStudent.begin(); iter != mapStudent.end(); iter++)
//    {
//        cout<<iter->first<<" "<<iter->second<<endl;
//    }

//    map<int, string>::reverse_iterator  iters;
//    for(iters = mapStudent.rbegin(); iters != mapStudent.rend(); iters++)
//    {
//        cout<<iters->first<<" "<<iters->second<<endl;
//    }  //�������
//    cout<<"����������ʽ:"<<endl;
//    for(unsigned int iIndex=0;iIndex < mapStudent.size();iIndex++) //size()���س�Ա�ĸ���
//    {
//        cout<<mapStudent[iIndex]<<endl;
//    }
//    cout<<mapStudent.count(1)<<endl;  //count()�жϹؼ����Ƿ���ڣ�����1��ʾ���ڣ�0
//    iter = mapStudent.find(1);        //find()�ؼ��ִ���ʱ��������������λ�õĵ����������򷵻�end()���صĵ�����
//    if( iter != mapStudent.end() )
//    {
//        cout<<"���ݴ��ڣ�"<<iter->first<<" "<<iter->second<<endl;
//        mapStudent.erase(iter);        //�õ���ɾ������
//    }
//    else
//    {
//        cout<<"���ݲ����ڣ�"<<endl;
//    }
//    int n = mapStudent.erase(3);        //�ùؼ���ɾ�������ɾ���˻᷵��1�����򷵻�0

//    iter = mapStudent.lower_bound(2);   //����2�ĵ�����
//    cout<<iter->second<<endl;
//    iter = mapStudent.upper_bound(2);   //����3�ĵ�����
//    cout<<iter->second<<endl;

//    /*Equal_range��������һ��pair��pair�����һ��������Lower_bound���صĵ�������pair����ڶ�����������Upper_bound���صĵ������������������������ȵĻ�����˵��map�в���������ؼ���*/
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

//    //ɾ��һ��ǰ�պ󿪵ļ��ϣ�����STL������
//    mapStudent.erase(mapStudent.begin(), mapStudent.end());

//    return 0;

//}
