#define PUB_READ_MACRO(x) 1


#if PUB_READ_MACRO ("头文件")
#include <iostream>

using namespace std;

#endif /*头文件*/


#if PUB_READ_MACRO ("函数或类实现")
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}

#endif /*函数或类实现*/

