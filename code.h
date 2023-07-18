#ifndef _CODE_H_
#define _CODE_H_


#include <stdio.h>
#include <string.h>

/*     MACROS OF PARAMETRIZATION     */
/*************************************/

#define NUMBER_OF_CHRISTMAS      5
#define NUMBER_MAX_ELVES         100
     
#define NUMBER_OF_REINDEERS      9
#define ALL_REINDEERS_RETURNED   9
#define MAX_ELVES_IN_TROUBLE     3

#define RED					    "\e[0;31m"
#define GREEN					"\e[0;32m"
#define BLUE					"\e[0;34m"
#define YELLOW					"\e[0;33m"
#define WHITE					"\e[0;37m"
#define RESET					"\e[0m"

/************************************/

#ifdef DEBUG
#define LOG_ON 1
#else
#define LOG_ON 0
#endif

#define LOG(...) do{ if(LOG_ON) {printf("DEBUG %d:%s(): ", __LINE__, __func__ ); printf(__VA_ARGS__); printf("\n");}} while(0)


typedef enum{
    closed = 0,
    opened
}operations;

typedef struct christmasFunctions_

{
    operations lock;
    unsigned int counter;
}christmasStruct;

typedef void * (*THREAD_FUNC_PTR)(void *);

/* Return Code*/

#define OK 0

typedef enum{
    true,
    false
}boolean;

typedef struct reindeersStruct_
{
    unsigned int counter;
    boolean reindeersShouldGetHitched;
}reindeersStruct;


typedef struct elvesStruct_
{
    unsigned int elvesWithTrouble;
    boolean elvesShouldWaitChristmasEnd;
}elvesStruct;

typedef struct santaStruct_
{
    boolean santaIsHelping;
}santaStruct;

//#define IS_EVEN(X)               ((X & 0x01) != 1)
#define EVENT(X)               ((X%10) == 0 )

#endif //_CODE_H
