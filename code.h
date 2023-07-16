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

/* MACROS */

#define RED					"\e[0;31m"
#define BLACK					"\e[0;30m"
#define RED					"\e[0;31m"
#define GREEN					"\e[0;32m"
#define BLUE					"\e[0;34m"
#define YELLOW					"\e[0;33m"
#define MAGENTA       				"\e[0;35m"
#define CYAN					"\e[0;36m"
#define WHITE					"\e[0;37m"
#define RESET					"\e[0m"


#define NUMBER_OF_REINDEERS      9
#define NUMBER_OF_ELVES          10
#define ALL_ELVES_RETURNED       9
#define MINIMUN_ELVES_IN_TROUBLE 3
#endif //_CODE_H
