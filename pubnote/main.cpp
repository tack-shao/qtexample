#define PUB_READ_MACRO(x) 1


#if PUB_READ_MACRO ("ͷ�ļ�")
#include <iostream>

using namespace std;

#endif /*ͷ�ļ�*/


#if PUB_READ_MACRO ("��������ʵ��")
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

#endif /*��������ʵ��*/

