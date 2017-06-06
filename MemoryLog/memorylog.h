#ifndef MEMORYLOG_H
#define MEMORYLOG_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdarg.h>
#include <pthread.h>

using namespace std;

class MemoryLog
{
public:
    MemoryLog();
    void PushLog(const char *key, char *buf);
    void ShowLogByName(const char *key, bool index);
    void ShowLogAll();
    void ClearLogByName(const char *key, bool tips);
    void ClearLogAll();
    void ShowLogKeys();
    void SaveLog2FileByName(const char *key, bool tips, FILE *fother);
    void SaveLog2FileAll(const char *filewithpath);
    void SaveLog2FileKeys(FILE *felse);

public:
    typedef std::vector<std::string> MLOG_VEC;
    typedef std::vector<std::string>::iterator MLOG_VEC_IT;
    typedef std::map<std::string, std::vector<std::string> > MLOG_MAP;
    typedef std::map<std::string, std::vector<std::string> >::iterator MLOG_MAP_IT;
    typedef std::pair<std::string, std::vector<std::string> > MLOG_MAP_PAIR;
    typedef std::pair<std::map<std::string, std::vector<std::string> >, bool > MLOG_MAP_RET;

private:
    MLOG_MAP mlog;
    pthread_mutex_t mutex;

private:
    static MemoryLog *pInstance;

public:
    static MemoryLog * GetInstance();

};


#ifdef __cplusplus
extern "C" {
#endif

/* func_declare_begin */
void pushmsgbyname(const char *key, void *msg, unsigned int msglen, char *fmt, ...);
void pushlogbyname(const char *key, char *fmt, ...);
void showmlogbyname( const char *key);
void showmlogall();
void clearmlogbyname( const char *key);
void clearmlogall();
void showmlogkeys();
void savemlog2filebyname(const char *key);
void savemlog2fileall(const char *filewithpath);
void savemlog2filekeys();
/* func_declare_end */
void set_mlogmaxsize(unsigned int _mlogmaxsize);
unsigned int get_mlogmaxsize(void);


#ifdef __cplusplus
}
#endif

#endif // MEMORYLOG_H
