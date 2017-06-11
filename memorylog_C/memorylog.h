#ifndef MEMORYLOG_H
#define MEMORYLOG_H



#define MLOG_VERSION ("1.0")

/*
** the memory log store info
*/
typedef struct T_MLOG{
    void *msgaddr          ;    /* store the address of msgs */
    unsigned int msglen    ;    /* the message len           */
    char tipsinfo[128]     ;    /* tips info                 */
}T_MLOG, *P_MLOG;




#endif // MEMORYLOG_H
