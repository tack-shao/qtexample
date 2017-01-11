#include <iostream>
#include <map>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct T_timerecord
{
    uint32_t firsttime;
    vector<string> vecTime;
}T_timerecord;

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




int main()
{
    inserttimerecord2(1, 1, "CPH");
    inserttimerecord2(1, 2, "CPL");
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
   cout << "Hello World!" << endl;
    printtimerecord2();
    return 0;
}

