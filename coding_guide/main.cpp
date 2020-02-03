#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void Func(char str[100])
{
    cout << "sizeof(str)" << sizeof(str) << endl;
    //此处是一个指针
}

/**
float，double分别遵循R32-24,R64-53的标准。
所以float的精度误差在1e-6；double精度误差在1e-15
所以要判断一个单精度浮点数：则是if( abs(f) <= 1e-6)；
要判断一个双精度浮点数：则是if( abs(f) <= 1e-15 )；

若小于，为0，
大于，不为0 。
————————————————
版权声明：本文为CSDN博主「戎·马一生」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/gogokongyin/article/details/51105745

**/

//判断float变量是否为0
int JudgeFloatEqual0(float f)
{
//    float f = 0.0001;
    const float EPSINON = 1e-6;
    if((f > - EPSINON) && (f < EPSINON))
    {
        cout << "float euqals to 0" << endl;
    }
    else
    {
        cout << "!!!float no euqal to 0" << endl;
    }


    return 0;
}

//判断double变量是否为0
int JudgeDoubleEqual0(double d)
{
//    float f = 0.0001;
    const double EPSINON = 1e-15;
    if((d > - EPSINON) && (d < EPSINON))
    {
        cout << "double euqals to 0" << endl;
    }
    else
    {
        cout << "!!!double no euqal to 0" << endl;
    }


    return 0;
}


//自定义strcpy的实现
//带返回值是为了生成链式表达式
//int length = strlen(StrCpy(pdest, psrc));
char *StrCpy(char *pStrDest, const char *pStrSrc)
{
    assert((NULL != pStrDest) && (NULL != pStrSrc));
    char *address = pStrDest;
//    while((*pStrDest++ = *pStrSrc++) != '\0')
//        (void)NULL;

    while(*pStrSrc)
    {
        *pStrDest++ = *pStrSrc++;
    }

    return address;
}


//String构造函数
class String
{
public:
    String(const char *pStr = NULL);
    String(const String &other);
    ~String(void);
    String & operator = (const String &other);

private:
    char *m_data;
};

String::String(const char *pStr)
{
    if(NULL == pStr)
    {
        m_data = new char[1];
        m_data = '\0';
    }
    else
    {
        int length = strlen(pStr);
        m_data = new char[length + 1];
        strcpy(m_data, pStr);
    }
}

String::~String(void)
{
    delete [] m_data;
}


/**
拷贝构造函数
**/
String::String(const String &other)
{
//拷贝构造函数说明不是同一个对象，所以此处不加判断
//    if(this == &other)
//    {
//        return *this;
//    }
    int length = strlen(other.m_data);
    m_data = new char[length + 1]; //此处要加1
    strcpy(m_data, other.m_data);
}

/**
赋值函数
**/
String & String::operator =(const String &other)
{
    if(this == &other)
    {
        return *this;
    }

    delete []m_data; //原先的内存必须释放掉。

    int length = strlen(other.m_data);
    m_data = new char[length+1]; //此处要加1
    strcpy(m_data, other.m_data);

    return *this; //返回本对象的引用
}



int main()
{
    char strtest[100] = {0};
    char strtest2[1000] = {0};

    Func(strtest);
    Func(strtest2);

    JudgeFloatEqual0(0.1);//1e-1
    JudgeFloatEqual0(0.01);//1e-2
    JudgeFloatEqual0(0.001);//1e-3
    JudgeFloatEqual0(0.0001);//1e-4
    JudgeFloatEqual0(0.00001);//1e-5
    JudgeFloatEqual0(0.000001);//1e-6, this coming to equal for  judge equal 0
    JudgeFloatEqual0(0.0000001);//1e-7
    JudgeFloatEqual0(0.0);//1e-0
    JudgeFloatEqual0(-0.0001);
    JudgeFloatEqual0(-0.00001);
    JudgeFloatEqual0(-0.000001);
    JudgeFloatEqual0(-0.0000001);



    JudgeDoubleEqual0(0.0);//1e-0
    JudgeDoubleEqual0(0.1);//1e-1
    JudgeDoubleEqual0(0.01);//1e-2
    JudgeDoubleEqual0(0.001);//1e-3
    JudgeDoubleEqual0(0.0001);//1e-4
    JudgeDoubleEqual0(0.00001);//1e-5
    JudgeDoubleEqual0(0.000001);//1e-6
    JudgeDoubleEqual0(0.0000001);//1e-7
    JudgeDoubleEqual0(0.00000001);//1e-8
    JudgeDoubleEqual0(0.000000001);//1e-9
    JudgeDoubleEqual0(0.0000000001);//1e-10
    JudgeDoubleEqual0(0.00000000001);//1e-11
    JudgeDoubleEqual0(0.000000000001);//1e-12
    JudgeDoubleEqual0(0.0000000000001);//1e-13
    JudgeDoubleEqual0(0.00000000000001);//1e-14
    JudgeDoubleEqual0(0.000000000000001);//1e-15, this coming to judge the equal
    JudgeDoubleEqual0(0.0000000000000001);//1e-16, judge the equal
//    JudgeDoubleEqual0(0.00000000000000001);
//    JudgeDoubleEqual0(0.000000000000000001);
//    JudgeDoubleEqual0(0.0000000000000000001);

    JudgeDoubleEqual0(0.0);

    //BOOL，float,指针变量与0判断
/**
BOOL
if(!bFlag)
if(bFlag)

FLOAT
const float

**/



/**
头文件中的ifndef /define /endif
解决头文件重复引用的问题

#include <filename.h> 和 #include "filename.h" 区别
<filename.h>查找顺序是从标准库路径查找
"filename.h"查找顺序是从用户工作路径开始搜索

const哪些用途
1.定义常量
2.修改函数的参数，返回值，或函数定义体，受强制保护

extern "C"作用
C++支持函数重载,C不支持函数重载，为了使生成的符号表进行名字匹配问题




**/
    char pdest[100] = {0};
    char psrc[] = "hello, world!!!";

    StrCpy(pdest, psrc);
    cout << "pdest:" << pdest << endl;
    cout << "strlen(pdest):" << strlen(StrCpy(pdest, psrc)) << endl;




    cout << "Hello World!" << endl;
    return 0;
}

/**
 运行结果




 **/
