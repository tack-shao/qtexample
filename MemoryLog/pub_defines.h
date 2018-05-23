#ifndef PUB_DEFINES_H
#define PUB_DEFINES_H


/**
** return if pointer is NULL
**/
#define RETURN_IFNULL(PT, EXPRESS)\
    if(!PT){\
        EXPRESS;\
        fprintf(stdout,"error:null pointer!!!, func:%s,line:%u\n", __FUNCTION__, __LINE__);\
        return;\
    }



/**
** return self value if pointer is NULL
**/
#define RETURNRVAL_IFNULL(PT, EXPRESS,RVAL)\
    if(!PT){\
        EXPRESS;\
        fprintf(stdout,"error:null pointer!!!, func:%s,line:%u\n", __FUNCTION__, __LINE__);\
        return RVAL;\
    }








#endif // PUB_DEFINES_H
