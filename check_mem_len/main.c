#include <stdio.h>
#include <assert.h>


#define para_checkpointer(para)\
do{\
    if(NULL == para)\
        return 0;\
}while(0)


#define para_checkvalidlen(para)\
do{\
    if(para){\
    fprintf(stdout, "invalid len@Fn:%s,Fl:%s,L:%d\n", __FUNCTION__, __FILE__, __LINE__);\
        assert(0);\
    }\
}while(0)





/* func_declare_begin */
int testmemlen( void);
/* func_declare_end */


/* func_implement */
int testmemlen( void)
{
    char *p = (char *)malloc(100);
    char *q = NULL;
    para_checkpointer(p);
    para_checkvalidlen(q = (p + 1000) > p + 100);  /* 长度判断非常重要 */



    if(p)
    {
        free(p);
        p = NULL;
    }

    return 0;
}

int main(void)
{
    testmemlen();
    printf("Hello World!\n");
    return 0;
}

