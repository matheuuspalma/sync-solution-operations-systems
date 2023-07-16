/*Rio de Janeiro - Federal University of Rio de Janeiro*/

/********** Includes *********/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "code.h"


/********* Statics functions declarations */

static void constructor(christmasStruct, unsigned);
static int santaThread(void);
static int reindeersThread(void);
static int elvesThread(void);
static int prepareSleigh(void);
static int getHitched(void);
static int helpElves(void);
static int getHelp(void);

/********* Variable declarations */
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int finalized = 0;
pthread_mutex_t mutex;

christmasStruct santa, reindeers, elves;


int processing = 1;

/********* Main Function definition*/
int main(void)
{
    
    unsigned char index;
    pthread_t santaId;
    pthread_t reindeersId [NUMBER_OF_REINDEERS];
    pthread_t elvesId[NUMBER_OF_ELVES];

    LOG("Debug mode on!\n");

    constructor(santa, 0);
    constructor(reindeers, 0);
    constructor(elves, 0);

    pthread_create(&santaId, NULL, (THREAD_FUNC_PTR)&santaThread, NULL);

    for(index = 0; index < NUMBER_OF_REINDEERS; index++){
        pthread_create(&reindeersId[index], NULL,(THREAD_FUNC_PTR)&reindeersThread, NULL);
    }

    for(index = 0; index < NUMBER_OF_ELVES; index++){
        pthread_create(&elvesId[index], NULL, (THREAD_FUNC_PTR)&elvesThread, NULL);
    }
    sleep(50);

    return 0;
}

/********* Threads Functios definitions*/
static int santaThread(void)
{
    pthread_mutex_init(&mutex, NULL);

    printf("\n%sSanta's thread is running!%s\n", WHITE, RESET);
    printf("\n%sSanta is sleeping%s\n",YELLOW, RESET);

    printf("\nSanta's thread\n");
    while(processing)
    {
        finalized = 0;
        if( reindeers.counter == ALL_ELVES_RETURNED)
        {
            printf("\n%sSanta should awake !!%s\n", YELLOW, RESET);
            printf("\n%sElves should wait wait until after Christmas!!%s\n", YELLOW, RESET);
            prepareSleigh();
        }

        if(elves.counter >= MINIMUN_ELVES_IN_TROUBLE || reindeers.counter < ALL_ELVES_RETURNED )
        {
            printf("\n%sSanta should awake !!%s\n", YELLOW, RESET);
            helpElves();
        }
        else
        {
            printf("\n%sSanta should keep resting !!%s\n", YELLOW, RESET);
        }
         sleep(200);

        pthread_mutex_lock(&mutex);
        while(finalized == 0)
            pthread_cond_wait(&condition, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return OK;
}

static int reindeersThread(void)
{
    printf("\n%sReindeers thread is running!%s\n", WHITE, RESET);
    sleep(10);
    if(reindeers.counter == 9){
            getHitched();
        }

    if(reindeers.counter < 9)
    {
        pthread_mutex_lock(&mutex);
        finalized = 1;
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    reindeers.counter += 1;
    printf("\n%sA reindeer arrived in the Pole!%s\n", BLUE, RESET);
    finalized = 1;
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
    
    return OK;
}

static int elvesThread(void)
{
    printf("\n%sElves' thread is running!%s\n", WHITE, RESET);
    sleep(10);
    
    if(reindeers.counter == 9){
        pthread_mutex_lock(&mutex);
        while(finalized == 0)
            pthread_cond_wait(&condition, &mutex);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    finalized = getHelp();
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
    return OK;
}


/********* Auxiliar Functios definitions*/
static int prepareSleigh(void)
{
   
    printf("\n%sPreparing sleigh!%s\n", BLUE, RESET);
    sleep(2);
    printf("\n%sDelivering gifts...%s\n", BLUE, RESET);
    sleep(20);
    reindeers.counter =- 9;
    printf("\n%sThe reindeers go back to South Pacific!%s\n", BLUE, RESET);
        

    return 0;
}

static int getHitched(void)
{
    printf("%s\nSleigh Hitched!%s\n", BLUE, RESET);
    //LOG("Sleigh Hitched");
    sleep(5);    
    return 0;
}

static int helpElves(void)
{
    
    printf("\n%sHelping elves%s\n", RED, RESET);
    elves.counter = elves.counter - 3;     
    printf("\n%sA elf was helped!%s\n", YELLOW, RESET);
    sleep(5);

    return 0;
}

static int getHelp(void)
{
    elves.counter += 1;
    printf("%s\nI need help (An Elf).%s\n", GREEN, RESET);
    sleep(5);
    return 1;
}

static void constructor(christmasStruct e, unsigned quantity)
{
    LOG("Constructing");
    e.lock = opened;
    e.counter = quantity;
    LOG("Construction sucessfull");
}