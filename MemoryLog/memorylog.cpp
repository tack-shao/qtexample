#include "memorylog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MUTEX_P(mutex) pthread_mutex_lock   (&mutex)
#define MUTEX_V(mutex) pthread_mutex_unlock (&mutex)


MemoryLog *MemoryLog::pInstance = NULL;

/*============================================
* FuncName    : MemoryLog::MemoryLog
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
MemoryLog::MemoryLog()
{
    mlog.clear();
    pthread_mutex_init (&mutex,NULL);
}

/*============================================
* FuncName    : MemoryLog::GetInstance
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
MemoryLog * MemoryLog::GetInstance()
{
    if(pInstance == NULL)
    {
        pInstance = new MemoryLog();
    }
    return pInstance;
}


/*============================================
* FuncName    : MemoryLog::PushLog
* Description : 推入数据流到内存
* @key        : 索引字
* @fmt        : 字符串格式
* @--         : 变长
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::PushLog(const char *key, char *buf)
{
    MUTEX_P (mutex);

    MLOG_MAP_IT it = mlog.find(string(key));
    if(it != mlog.end())
    {
        MLOG_VEC &vec = it->second;
        if(vec.size() >= get_mlogmaxsize())
        {
            MUTEX_V(mutex);
            return;
        }
        vec.push_back(string(buf));
    }
    else
    {
        MLOG_VEC vec;
        vec.push_back(string(buf));
        mlog.insert(MLOG_MAP_PAIR(string(key), vec));
    }
    MUTEX_V(mutex);
}

/*============================================
* FuncName    : MemoryLog::ShowLogByName
* Description : show key's memory log
* @key        :
* @index      : show tips or not
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::ShowLogByName(const char *key, bool index = true)
{
    MUTEX_P (mutex);
    if(index)
        fprintf(stdout, "show mlog key[%-10s], ", key);
    MLOG_MAP_IT it = mlog.find(string(key));
    if(it != mlog.end())
    {
        MLOG_VEC &vec = it->second;
        fprintf(stdout, "[%s] size:%u\n", key, vec.size());
        for(MLOG_VEC_IT vit = vec.begin(); vit != vec.end(); ++vit)
        {
            fprintf(stdout, "==>%s\n", (*vit).c_str());
        }
        if(index)
            fprintf(stdout, "show mlog key[%s] done!!\n\n", key);
    }
    else
    {
        if(index)
            fprintf(stdout, "no data!!\n\n");
    }
    MUTEX_V (mutex);
}

/*============================================
* FuncName    : MemoryLog::ShowLogAll
* Description : show all key's memory log
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::ShowLogAll()
{
    if(!mlog.size() )
    {
        fprintf(stdout, "show mlog, no data!!\n");
        return;
    }
    fprintf(stdout, "show all mlog data, size:%u\n", mlog.size());
    for(MLOG_MAP_IT it  = mlog.begin(); it != mlog.end(); ++it)
    {
        ShowLogByName(it->first.c_str(), false);
    }

    fprintf(stdout, "show all mlog data, size:%u, done!!\n", mlog.size());
}

/*============================================
* FuncName    : MemoryLog::ShowLogKeys
* Description : show memory log's keys
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::ShowLogKeys()
{
    if(!mlog.size() )
    {
        fprintf(stdout, "show mlog keys, no data!!\n");
        return;
    }
    fprintf(stdout, "show mlog keys, size:%u\n", mlog.size());
    if(mlog.size())
    {
        fprintf(stdout,"[key_____] [count]\n");
    }

    for(MLOG_MAP_IT it  = mlog.begin(); it != mlog.end(); ++it)
    {
        fprintf(stdout,"%-010s %-07u \n" ,
                it->first.c_str(),
                it->second.size() );
    }

    fprintf(stdout, "show mlog keys, size:%u, done!!\n", mlog.size());
}

/*============================================
* FuncName    : MemoryLog::ClearLogByName
* Description :
* @key        :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::ClearLogByName(const char *key, bool tips = true)
{
    MUTEX_P (mutex);
    if(tips)
        fprintf(stdout, "clear mlog key[%s], ", key);
    MLOG_MAP_IT it = mlog.find(string(key));
    if(it != mlog.end())
    {
        MLOG_VEC &vec = it->second;
        vec.clear();
        mlog.erase(it);
        if(tips)
            fprintf(stdout, "\nclear mlog key[%s] done!!\n", key);
    }
    else
    {
        if(tips)
            fprintf(stdout, "no data!!\n");
    }
    MUTEX_V (mutex);
}

/*============================================
* FuncName    : MemoryLog::ClearLogAll
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::ClearLogAll()
{
    if(!mlog.size() )
    {
        fprintf(stdout, "no data!!\n");
        return;
    }
    fprintf(stdout, "clear all mlog, size:%u\n", mlog.size());
    for(MLOG_MAP_IT it  = mlog.begin(); it != mlog.end(); ++it)
    {
        ClearLogByName(it->first.c_str(),false);
    }
    mlog.clear();

    fprintf(stdout, "clear all mlog, size:%u, done!!\n", mlog.size());
}

/*============================================
* FuncName    : MemoryLog::SaveLog2FileByName
* Description :
* @key        :
* @tips       :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::SaveLog2FileByName(const char *key, bool tips = true, FILE *fother = NULL)
{
    string name(key);
    FILE *fp = NULL;
    if(NULL == fother)
    {
        fp = fopen(name.c_str(), "w");
        if(!fp)
        {
            fprintf(stderr, "open file err![%s]\n", name);
            return;
        }
    }
    else
    {
        fp = fother;
    }

    timeval now;
    gettimeofday(&now, NULL);

    MUTEX_P (mutex);
    if(tips){
        fprintf(fp, "time:s-us:%u-%u\n", now.tv_sec, now.tv_usec);
        fprintf(stdout, "save mlog to file[%s], ", key);
        fprintf(fp, "save mlog to file[%s], ", key);
    }
    MLOG_MAP_IT it = mlog.find(string(key));
    if(it != mlog.end())
    {
        MLOG_VEC &vec = it->second;
        fprintf(fp, "[%s] size:%u\n", key, vec.size());
        for(MLOG_VEC_IT vit = vec.begin(); vit != vec.end(); ++vit)
        {
            fprintf(fp, "==>%s\n", (*vit).c_str());
        }
        if(tips){
            fprintf(stdout, "save mlog to file[%s] done!!\n\n", key);
            fprintf(fp, "save mlog to file[%s] done!!\n\n", key);
        }
    }
    else
    {
        if(tips)
            fprintf(fp, "no data!!\n\n");
    }
    fflush(fp);
    if(NULL == fother)
    {
        fclose(fp);
    }
    MUTEX_V (mutex);
}

/*============================================
* FuncName    : MemoryLog::SaveLog2FileAll
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void MemoryLog::SaveLog2FileAll()
{

    if(!mlog.size() )
    {
        fprintf(stdout, "save mlog to file, no data!!\n");
        return;
    }

    const char *name = "./savemlogs.txt";
    FILE *fp = fopen(name, "w");
    if(!fp)
    {
        fprintf(stderr, "open file err![%s]\n", name);
        return;
    }

    SaveLog2FileKeys(fp);

    fprintf(stdout, "save mlog to file, size:%u\n", mlog.size());
    fprintf(fp, "save mlog to file, size:%u\n", mlog.size());
    for(MLOG_MAP_IT it  = mlog.begin(); it != mlog.end(); ++it)
    {
        SaveLog2FileByName(it->first.c_str(), true, fp);
    }

    fprintf(fp, "save mlog to file, size:%u, done!!\n", mlog.size());
    fprintf(stdout, "save mlog to file, size:%u, done!!\n", mlog.size());

    fclose(fp);
}

void MemoryLog::SaveLog2FileKeys(FILE *felse = NULL)
{
    FILE *fp = NULL;
    if(NULL == felse)
    {
        const char *name = "./mlog_keys.txt";
        fp = fopen(name, "w");
        if(!fp)
        {
            fprintf(stderr, "open file err![%s]\n", name);
            return;
        }
    }
    else
    {
        fp = felse;
    }
    if(!mlog.size() )
    {
        fprintf(stdout, "show mlog keys, no data!!\n");
        fprintf(fp, "show mlog keys, no data!!\n");
        return;
    }
    fprintf(stdout, "show mlog keys, size:%u\n", mlog.size());
    fprintf(fp, "show mlog keys, size:%u\n", mlog.size());
    for(MLOG_MAP_IT it  = mlog.begin(); it != mlog.end(); ++it)
    {
        fprintf(stdout, "[key]: %s\n", it->first.c_str());
        fprintf(fp, "[key]: %s\n", it->first.c_str());
    }

    fprintf(stdout, "show mlog keys, size:%u, done!!\n", mlog.size());
    fprintf(fp, "show mlog keys, size:%u, done!!\n", mlog.size());

    if(NULL == felse)
    {
        fclose(fp);
    }
}




#ifdef __cplusplus
extern "C" {
#endif

/* func_declare_begin */
void showmlogbyname( const char *key);
void showmlogall();
void clearmlogbyname( const char *key);
void clearmlogall();
/* func_declare_end */


/* func_implement */

/*============================================
* FuncName    : pushlogbyname
* Description :
* @key        :
* @fmt        :
* @--         :
* Author      :
* Time        : 2017-06-06
============================================*/
void pushlogbyname(const char *key, char *fmt, ...)
{
    va_list ap;
    char buf[1024];
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);

    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->PushLog(key, buf);
}

/*============================================
* FuncName    : pushmsgbyname
* Description :
* @key        :
* @fmt        :
* @--         :
* Author      :
* Time        : 2017-06-06
============================================*/
void pushmsgbyname(const char *key, void *msg, unsigned int msglen, char *fmt, ...)
{
    va_list ap;
    char buf[1024];
    char *pmsg = NULL;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);

    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->PushLog(key, buf);
    if(NULL != msg || 0!= msglen) // record msg
    {
        pmsg = (char *)malloc(msglen * 3 + (msglen/ 16) *4);
        if(!pmsg)
            return;
        memset(pmsg, 0, msglen);
        unsigned int i = 0;
        unsigned int j = 0;
        unsigned int tnum = 0;
        unsigned int cpos = 0;
        char *rmsg = (char *)msg;
        sprintf(buf, "msg:%p, len:%u", msg, msglen);
        pInstance->PushLog(key, buf);

        tnum = sprintf(pmsg + cpos, "\n");
        for(i = 0; i < msglen; i++)
        {
            j = i + 1;
            if(0 == i)
            {
                tnum = sprintf(pmsg + cpos, "\n");
                cpos += tnum;
            }
            if(0 == j % 8 && 0 != j % 16)
                tnum = sprintf(pmsg + cpos, "%02X  ", (unsigned char)rmsg[i]);
            else if( 0 == j % 16)
                tnum = sprintf(pmsg + cpos, "%02X", (unsigned char)rmsg[i]);
            else
                tnum = sprintf(pmsg + cpos, "%02X ", (unsigned char)rmsg[i]);

            cpos += tnum;
            if( 0 == (j) % 16)
            {
                tnum = sprintf(pmsg + cpos, "\n");
                cpos += tnum;
            }
        }
        fprintf(stdout, "cpos :%u\n", cpos);
        pInstance->PushLog(key, pmsg);
        free(pmsg);
    }


}




/*============================================
* FuncName    : showmlogbyname
* Description :
* @key        :
* Author      :
* Time        : 2017-06-05
============================================*/
void showmlogbyname( const char *key)
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->ShowLogByName(key);

}

/*============================================
* FuncName    : showmlogall
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void showmlogall()
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->ShowLogAll();
}

/*============================================
* FuncName    : clearmlogbyname
* Description :
* @key        :
* Author      :
* Time        : 2017-06-05
============================================*/
void clearmlogbyname( const char *key)
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->ClearLogByName(key);
}

/*============================================
* FuncName    : clearmlogall
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void clearmlogall()
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->ClearLogAll();
}
/*============================================
* FuncName    : showmlogkeys
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void showmlogkeys()
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->ShowLogKeys();
}

/*============================================
* FuncName    : savemlog2filebyname
* Description :
* @key        :
* Author      :
* Time        : 2017-06-05
============================================*/
void savemlog2filebyname(const char *key)
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->SaveLog2FileByName(key);
}

/*============================================
* FuncName    : savemlog2fileall
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void savemlog2fileall()
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->SaveLog2FileAll();
}

/*============================================
* FuncName    : savemlog2filekeys
* Description :
* @           :
* Author      :
* Time        : 2017-06-05
============================================*/
void savemlog2filekeys()
{
    MemoryLog *pInstance = MemoryLog::GetInstance();
    pInstance->SaveLog2FileKeys();
}




/* variable declare begin */
unsigned int mlogmaxsize = 1000;
/* variable declare end */
/*
Set and Get for mlogmaxsize
*/
/*============================================
* FuncName    : set_mlogmaxsize
* Description :
* @_mlogmaxsize  :
* Author      :
* Time        : 2017-06-05
============================================*/
void set_mlogmaxsize(unsigned int _mlogmaxsize)
{
    mlogmaxsize = _mlogmaxsize;
}

/*============================================
* FuncName    : get_mlogmaxsize
* Description :
* @--         :
* Author      :
* Time        : 2017-06-05
============================================*/
unsigned int get_mlogmaxsize(void)
{
    return mlogmaxsize;
}



#ifdef __cplusplus
}
#endif

