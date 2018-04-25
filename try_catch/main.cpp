#include <iostream>
#include <exception>

using namespace std;

//可以自己定义Exception
class myexception: public exception
{
    virtual const char* what() const throw()
    {
        return "My exception happened";
    }
}myex;


void try_catch()
{
    try
    {

        char *p = new char[100000000000000000000000000000];
        if(p == NULL)
        {
            if(true)    //如果，则抛出异常；
                throw myex;
        }
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

//    catch(char *str){
//        cout << "mem failed" << endl;
//    }

//    try
//    {
//        if(true)    //如果，则抛出异常；
//            throw myex;
//    }
//    catch (exception& e)
//    {
//        cout << e.what() << endl;
//    }




}


int main()
{
    try_catch();
    cout << "Hello World!" << endl;
    return 0;
}

