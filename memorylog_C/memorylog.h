#ifndef MEMORYLOG_H
#define MEMORYLOG_H



#define MLOG_VERSION ("1.0")

#pragma pack(1)
/*
** the memory log store info
*/
typedef struct T_MLOG{
    void *msgaddr          ;    /* store the address of msgs */
    unsigned int msglen    ;    /* the message len           */
    char tipsinfo[128]     ;    /* tips info                 */
}T_MLOG, *P_MLOG;
#pragma pack()




//struct mlognode * mlog_search(struct rb_root *root, char *string);
//int mlog_insert(struct rb_root *root, struct mlognode *data);
//void mlog_free(struct mlognode *node);
void PushLog(const char *key, T_MLOG *plog);
int test_mlog();
void MemoryLogInit();
const char* Version();
//unsigned int timeval_diff(struct timeval *tvbegin, struct timeval *tvend);
void set_mlogmaxsize(unsigned int _mlogmaxsize);
unsigned int get_mlogmaxsize(void);
void set_mlogformat(int _mlogformat);
int get_mlogformat(void);
void mloghelp();

void ShowLogByName(const char *key, int index);


void test_pushlog();
void test_pushpkg();
void test_savefile();



#endif // MEMORYLOG_H
