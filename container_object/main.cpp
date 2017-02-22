//结构体，结构体指针
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
    pDataInfo ppdat = &dat; //不用加*号了
    return 0;
}

