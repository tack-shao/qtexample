//�ṹ�壬�ṹ��ָ��
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct tagDataInfo
{
 int iData;
 string strData;
 vector<string> vecData;
}DataInfo, *pDataInfo;

int main()
{
    cout << "Hello World!" << endl;
    DataInfo dat;
    pDataInfo ppdat = &dat; //���ü�*����
    return 0;
}

