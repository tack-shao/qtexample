#include <iostream>
#include <string.h>

using namespace std;

void trim(string &s)
{
    /*
    if( !s.empty() )
    {
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
    */
    int index = 0;
    if( !s.empty())
    {
        while( (index = s.find(' ',index)) != string::npos)
        {
            s.erase(index,1);
        }
    }
}


void trimspaceandenter(string &s)
{
    int index = 0;
    if( !s.empty())
    {
        while( (index = s.find(' ',index)) != string::npos)
        {
            s.erase(index,1);
        }

        index = 0;
        while( (index = s.find('\n',index)) != string::npos)
        {
            s.erase(index,1);
        }
    }

    index = 0;
    while( (index = s.find('\r\n',index)) != string::npos)
    {
        s.erase(index,1);
    }
}

void testtrimprint(string s)
{
    cout << " === before ====" << endl;
    cout << "s1:" << s << endl;
    trimspaceandenter(s);
    cout << " === after  ====" << endl;
    cout << "s1:" << s << endl;
}


/*
*去掉字符串首尾的 \x20 \r \n 字符
*/
void TrimSpace(char* str)
{
    char *start = str - 1;
    char *end = str;
    char *p = str;
    while(*p)
    {
        switch(*p)
        {
        case ' ':
        case '\r':
        case '\n':
        {
            if(start + 1==p)
                start = p;
        }
            break;
        default:
            break;
        }
        ++p;
    }
    //现在来到了字符串的尾部 反向向前
    --p;
    ++start;
    if(*start == 0)
    {
        //已经到字符串的末尾了
        *str = 0 ;
        return;
    }
    end = p + 1;
    while(p > start)
    {
        switch(*p)
        {
        case ' ':
        case '\r':
        case '\n':
        {
            if(end - 1 == p)
                end = p;
        }
            break;
        default:
            break;
        }
        --p;
    }
    memmove(str,start,end-start);
    *(str + (int)end - (int)start) = 0;
}


int main()
{
    testtrimprint("hello world!\n");
    testtrimprint("   0x 12 34 ef af ef a a a a a  a a a a  a a a  a\n bbb \r\n");
    testtrimprint("   0x 12 34 ef af ef a a a a a  a a a a  a a a  a\n bbb \r\n                             ");
    testtrimprint(" val VOTE_AVERAGE_API = \"http://api.themoviedb.org//3/discover/movie?certification_country=US&;certification=R&;sort_by=vote_average.desc&;api_key=7e55a88ece9f03408b895a96c1487979\"  ");

    cout << "Hello World!" << endl;
    return 0;
}

