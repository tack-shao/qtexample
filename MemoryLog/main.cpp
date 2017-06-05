#include <iostream>
#include "memorylog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void* thread_function(void* arg)
{
    arg = arg;
    int *pint = (int *)arg;
    char name[64];
    sprintf(name, "pthread %d", *pint);
//    string name("pthread " + (int)*arg);
    int i = 0;
    while(1){
        pushlogbyname(name, "i am comming!!:%d", i++);
        Sleep(2000);
        showmlogbyname(name);
    }
    return NULL;
}


int main()
{
    cout << "Hello World!" << endl;

    pushlogbyname("init", "haha");
    showmlogbyname("init");
    showmlogall();

    set_mlogmaxsize(3000);

    pushlogbyname("error", "index:%d", 1);
    pushlogbyname("error", "index:%d", 2);
    pushlogbyname("error", "index:%d", 3);
    showmlogbyname("error");


    int i = 0;
    for( i = 0 ; i < 1000000; i++ )
    {
        pushlogbyname("sums", "sum is:%d", i * 1000 );

    }

    showmlogall();
    showmlogkeys();
    savemlog2filebyname("error");
    savemlog2fileall();
    savemlog2filekeys();

    showmlogall();
    clearmlogbyname("error");
    showmlogall();
    clearmlogall();
    clearmlogbyname("init");
    showmlogall();
    showmlogall();

    return 1;

    pthread_t thread_id;
    pthread_t thread_id2;
    pthread_attr_t attr;
    pthread_attr_t attr2;
    pthread_attr_init(&attr);
    pthread_attr_init(&attr2);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    int seq = 1;
    pthread_create(&thread_id,&attr,&thread_function,&seq);
    int seq2 = 2;
    pthread_create(&thread_id2,&attr2,&thread_function,&seq2);
    pthread_attr_destroy(&attr);
    pthread_attr_destroy(&attr2);

    while(1)
        Sleep(1000);

    return 0;
}

