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
    true,
    false
}boolean;

typedef enum{
    closed = 0,
    opened
}operations;

typedef struct reindeersStruct_
{
    operations lock;
    unsigned int counter;
    boolean reindeersShouldGetHitched;
}reindeersStruct;


typedef struct elvesStruct_
{
    operations lock;
    unsigned int elvesWithTrouble;
    boolean elvesShouldWaitChristmasEnd;
}elvesStruct;

typedef struct santaStruct_
{
    operations lock;
    boolean shouldSleep;
}santaStruct;

typedef void * (*THREAD_FUNC_PTR)(void *);

/* Return Code*/

#define OK 0

/* MACROS */

#define ALL_REINDEERS_RETURNED       9
#define MINIMUN_ELVES_IN_TROUBLE 3
#define IS_EVEN(X)               ((X & 0x01) != 1)
#endif //_CODE_H
