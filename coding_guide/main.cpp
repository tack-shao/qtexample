#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void Func(char str[100])
{
    cout << "sizeof(str)" << sizeof(str) << endl;
    //�˴���һ��ָ��
}

/**
float��double�ֱ���ѭR32-24,R64-53�ı�׼��
����float�ľ��������1e-6��double���������1e-15
����Ҫ�ж�һ�������ȸ�����������if( abs(f) <= 1e-6)��
Ҫ�ж�һ��˫���ȸ�����������if( abs(f) <= 1e-15 )��

��С�ڣ�Ϊ0��
���ڣ���Ϊ0 ��
��������������������������������
��Ȩ����������ΪCSDN�������֡���һ������ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/gogokongyin/article/details/51105745

**/

//�ж�float�����Ƿ�Ϊ0
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

//�ж�double�����Ƿ�Ϊ0
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


//�Զ���strcpy��ʵ��
//������ֵ��Ϊ��������ʽ���ʽ
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


//String���캯��
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
�������캯��
**/
String::String(const String &other)
{
//�������캯��˵������ͬһ���������Դ˴������ж�
//    if(this == &other)
//    {
//        return *this;
//    }
    int length = strlen(other.m_data);
    m_data = new char[length + 1]; //�˴�Ҫ��1
    strcpy(m_data, other.m_data);
}

/**
��ֵ����
**/
String & String::operator =(const String &other)
{
    if(this == &other)
    {
        return *this;
    }

    delete []m_data; //ԭ�ȵ��ڴ�����ͷŵ���

    int length = strlen(other.m_data);
    m_data = new char[length+1]; //�˴�Ҫ��1
    strcpy(m_data, other.m_data);

    return *this; //���ر����������
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

    //BOOL��float,ָ�������0�ж�
/**
BOOL
if(!bFlag)
if(bFlag)

FLOAT
const float

**/



/**
ͷ�ļ��е�ifndef /define /endif
���ͷ�ļ��ظ����õ�����

#include <filename.h> �� #include "filename.h" ����
<filename.h>����˳���Ǵӱ�׼��·������
"filename.h"����˳���Ǵ��û�����·����ʼ����

const��Щ��;
1.���峣��
2.�޸ĺ����Ĳ���������ֵ�����������壬��ǿ�Ʊ���

extern "C"����
C++֧�ֺ�������,C��֧�ֺ������أ�Ϊ��ʹ���ɵķ��ű��������ƥ������




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
 ���н��




 **/
