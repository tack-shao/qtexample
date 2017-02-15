#include <iostream>
#include <map>
#include <iostream>
#include <vector>
#include <string>

#include <time.h>
#include <sys/time.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <windows.h>

using namespace std;

/**************************************************************
  *宏定义
  ************************************************************/
#define ARRAYSIZE(array)        ((unsigned int)(sizeof(array) / sizeof((array)[0])))

#define TIMEDIFF(FUNC) \
    do{\
    struct  timeval    tv = {0};\
    struct  timezone   tz = {0};\
    gettimeofday(&tv,&tz);\
    tTimeInfo[index_TimeInfo].tbegin = tv;\
    tTimeInfo[index_TimeInfo].funcname = __FUNCTION__;\
    tTimeInfo[index_TimeInfo].linepre = __LINE__;\
    {FUNC};\
    gettimeofday(&tv,&tz);\
    tTimeInfo[index_TimeInfo].tend = tv;\
    tTimeInfo[index_TimeInfo].linesuf = __LINE__;\
    index_TimeInfo++;\
}while(0);


#define TIMEDIFF_MAX (500)


/**************************************************************
  *数据类型定义
  ************************************************************/

typedef struct T_timerecord
{
    uint32_t firsttime;
    vector<string> vecTime;
}T_timerecord;

typedef struct T_save_timeinfo
{
    struct  timeval tbegin;
    struct  timeval tend;
    const char *funcname;
    uint32_t linepre;
    uint32_t linesuf;
}T_save_timeinfo;



/**************************************************************
  *全局变量
  ************************************************************/
static T_save_timeinfo tTimeInfo[TIMEDIFF_MAX] = {0};
static uint32_t index_TimeInfo = 0;

map<uint32_t, T_timerecord> mapTimeRecord2;
map<uint32_t, T_timerecord>::iterator mapTR2It;
vector<string>::iterator vecTimeIt;


void printtimerecord2()
{
    for(mapTR2It = mapTimeRecord2.begin(); mapTR2It != mapTimeRecord2.end();mapTR2It++)
    {
        cout << "ID:" << mapTR2It->first ;
        T_timerecord &tTimeR = mapTR2It->second;
        cout << ", Val:" ;
        for(vecTimeIt = tTimeR.vecTime.begin(); vecTimeIt != tTimeR.vecTime.end(); vecTimeIt++)
        {
            cout  <<  *vecTimeIt << "  ";
        }
        cout << endl;
    }
}


void inserttimerecord2(uint32_t key, uint32_t starttime, char *buffer)
{

    map<uint32_t, T_timerecord>::iterator mapIt;
    mapIt = mapTimeRecord2.find(key);
    if(mapIt == mapTimeRecord2.end())
    {
        T_timerecord timer;
        timer.firsttime = starttime;
        timer.vecTime.push_back(buffer);
        mapTimeRecord2.insert(make_pair(key,timer));
    }
    else
    {
        T_timerecord &timer = mapIt->second;
        //        timer.firsttime = starttime;
        timer.vecTime.push_back(buffer);
    }
}

uint32_t timediff(struct timeval *tv1, struct timeval *tv2)
{
    return abs((tv1->tv_sec - tv2->tv_sec)*1000 + (tv1->tv_usec - tv2->tv_usec));
}


void print_tTimeInfo()
{
    uint32_t lp = 0;
    T_save_timeinfo tmptimeinfo = {0};
    for(lp = 0; lp < ARRAYSIZE(tTimeInfo); lp++)
    {
        if(0 ==  memcmp(&tmptimeinfo, &tTimeInfo[lp], sizeof(T_save_timeinfo)))
            continue;
        fprintf(stdout, "No:%-3u, Fun:%-15s, line:%-4d->%-4d timediff:%d (us)\n",
                lp,
                tTimeInfo[lp].funcname ,
                tTimeInfo[lp].linepre ,
                tTimeInfo[lp].linesuf ,
                timediff(&tTimeInfo[lp].tbegin, &tTimeInfo[lp].tend));
    }
    fprintf(stdout, "=============TimeDiff size:%u =============\n", index_TimeInfo);
}


/**************************************************************
  *函数实现
  ************************************************************/

int main()
{
    TIMEDIFF(
    TIMEDIFF(inserttimerecord2(1, 1, "CPH"););
     TIMEDIFF(inserttimerecord2(1, 2, "CPL");
    inserttimerecord2(1, 2, "2UPP");
    inserttimerecord2(1, 2, "2LM");
    inserttimerecord2(1, 2, "4LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(1, 2, "LM");
    inserttimerecord2(2, 2, "word");
    inserttimerecord2(2, 2, "word");
    inserttimerecord2(2, 2, "word");
    inserttimerecord2(3, 2, "word");
    inserttimerecord2(4, 2, "word");
    inserttimerecord2(5, 2, "word");
    inserttimerecord2(6, 2, "word");
    inserttimerecord2(6, 2, "word");
    inserttimerecord2(6, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    inserttimerecord2(7, 2, "word");
    Sleep(1000););
    cout << "Hello World!" << endl;
    printtimerecord2();


    print_tTimeInfo();
    );

    print_tTimeInfo();
    return 0;
}


/*
No:0  , Fun:main           , line:205 ->205  timediff:0 (us)
No:1  , Fun:main           , line:205 ->205  timediff:11004 (us)
=============TimeDiff size:2 =============
No:0  , Fun:main           , line:205 ->205  timediff:0 (us)
No:1  , Fun:main           , line:205 ->205  timediff:11004 (us)
No:2  , Fun:(null)         , line:0   ->205  timediff:1104005968 (us)
=============TimeDiff size:3 =============


No:0  , Fun:main           , line:205 ->205  timediff:0 (us)
No:1  , Fun:main           , line:205 ->205  timediff:2358 (us)
=============TimeDiff size:2 =============
No:0  , Fun:main           , line:205 ->205  timediff:0 (us)
No:1  , Fun:main           , line:205 ->205  timediff:2358 (us)
No:2  , Fun:(null)         , line:0   ->205  timediff:1103448161 (us)
=============TimeDiff size:3 =============

*/
