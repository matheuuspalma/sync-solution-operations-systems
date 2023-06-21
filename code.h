#ifndef _CODE_H_
#define _CODE_H_

#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define LOG_ON 1
#else
#define LOG_ON 0
#endif

#define LOG(...) do{ if(LOG_ON) {printf("%d:%s(): ", __LINE__, __func__ ); printf(__VA_ARGS__); printf("\n");}} while(0)

typedef enum{
    semaphoreWait = -1,
    semaphoreSignal = 1
}operations;

typedef struct christmasFunctions_
{
    void (*signal) (operations *);
    void (*wait) (operations *);
    operations control;
    unsigned int counter;
}christmasStruct;

typedef void * (*THREAD_FUNC_PTR)(void *);

/* Return Code*/

#define OK 0


#endif //_CODE_H
