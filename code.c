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

pthread_cond_t santasRest = PTHREAD_COND_INITIALIZER;
pthread_cond_t reindeersNoReady = PTHREAD_COND_INITIALIZER;

int santaFinalized = 0;
int reindeersFinalized = 0;
int elvesFinalized = 0;

pthread_mutex_t santaMutex;
pthread_mutex_t reindeersMutex;
pthread_mutex_t elvesMutex;

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

    for(index = 0; index < NUMBER_OF_ELVES; index++){
        pthread_create(&elvesId[index], NULL, (THREAD_FUNC_PTR)&elvesThread, NULL);
    }
    sleep(10);
    for(index = 0; index < NUMBER_OF_REINDEERS; index++){
        pthread_create(&reindeersId[index], NULL,(THREAD_FUNC_PTR)&reindeersThread, NULL);
    }

    
    sleep(200);

    return 0;
}

/********* Threads Functios definitions*/
static int santaThread(void)
{
    pthread_mutex_init(&santaMutex, NULL);

    printf("\n%sSanta's thread is running!%s\n", WHITE, RESET);
    printf("\n%sSanta is sleeping%s\n",YELLOW, RESET);

    while(processing)
    {
        pthread_mutex_lock(&santaMutex);
        santaFinalized = 0;
        pthread_mutex_unlock(&santaMutex);
        if( reindeers.counter == ALL_REINDEERS_RETURNED)
        {
            printf("\n%sSanta should awake !!%s\n", YELLOW, RESET);
            printf("\n%sElves should wait wait until after Christmas!!%s\n", YELLOW, RESET);
            prepareSleigh();
            continue;
        }

        if(elves.counter >= MINIMUN_ELVES_IN_TROUBLE && reindeers.counter < ALL_REINDEERS_RETURNED )
        {
            printf("\n%sSanta should awake !!%s\n", YELLOW, RESET);
            helpElves();
            continue;
        }
        
        printf("\n%sSanta should keep resting !!%s\n", YELLOW, RESET);

        pthread_mutex_lock(&santaMutex);
        while(santaFinalized == 0)
            pthread_cond_wait(&santasRest, &santaMutex);
        pthread_mutex_unlock(&santaMutex);
    }
    return OK;
}

static int reindeersThread(void)
{
    pthread_mutex_init(&reindeersMutex, NULL);
   
    unsigned short cicle = 0;

    printf("\n%sReindeers thread is running!%s\n", WHITE, RESET);
    sleep(10);
    
    while(reindeersFinalized == 0){

        if(reindeers.counter == ALL_REINDEERS_RETURNED){
            cicle = 1;
            getHitched();
              
        }

        if(reindeers.counter < 9)
        {
            pthread_mutex_lock(&elvesMutex);
            elvesFinalized = 1;
            pthread_cond_signal(&reindeersNoReady);
            pthread_mutex_unlock(&elvesMutex);
        }

        srand(time(NULL));
        while (!(cicle))
        {
            if (rand() % 5 == 1) {
            cicle = 1;
            reindeers.counter += 1;
            printf("\n%sA reindeer arrived in the Pole!%s\n", BLUE, RESET);

            pthread_mutex_lock(&santaMutex);
            santaFinalized = 1;
            pthread_cond_signal(&santasRest);
            pthread_mutex_unlock (&santaMutex);
            }
        }
        pthread_mutex_unlock(&reindeersMutex); 
    }
    return OK;
}

static int elvesThread(void)
{
    pthread_mutex_init(&elvesMutex, NULL);
    printf("\n%sElves' thread is running!%s\n", WHITE, RESET);
    sleep(10);

    if(reindeers.counter == ALL_REINDEERS_RETURNED){
    pthread_mutex_lock(&elvesMutex);
        while(elvesFinalized == 0)
            pthread_cond_wait(&reindeersNoReady, &elvesMutex);
        pthread_mutex_unlock(&elvesMutex);
    }

    pthread_mutex_lock(&elvesMutex);
    while(elvesFinalized == 0)
        getHelp();
    elvesFinalized = 0;
    pthread_mutex_unlock(&elvesMutex);
    return OK;
}


/********* Auxiliar Functios definitions*/
static int prepareSleigh(void)
{

    pthread_mutex_lock(&reindeersMutex);
    
    printf("\n%sPreparing sleigh!%s\n", BLUE, RESET);
    sleep(5);
    reindeersFinalized = 0;
    pthread_cond_broadcast(&reindeersNoReady);
    while(reindeersFinalized != ALL_REINDEERS_RETURNED)
        pthread_cond_wait(&reindeersNoReady, &reindeersMutex);
    printf("\n%sDelivering gifts...%s\n", BLUE, RESET);
    sleep(10);
    reindeers.counter -= 9;
    printf("\n%sThe reindeers go back to South Pacific!%s\n", BLUE, RESET);
    
    pthread_mutex_lock(&elvesMutex);
    elvesFinalized = 1;
    pthread_mutex_unlock(&elvesMutex);

    pthread_cond_signal(&santasRest);
    pthread_cond_signal(&elvesCan);
    pthread_mutex_unlock(&reindeersMutex);


    return 0;
}

static int getHitched(void)
{
    sleep(5); 
    pthread_mutex_lock(&reindeersMutex);
    reindeersFinalized += 1;
    printf("%s\nSleigh Hitched!%s\n", BLUE, RESET);   
    pthread_cond_broadcast(&reindeersNoReady);
    pthread_mutex_unlock(&reindeersMutex);
    return 0;
}

static int helpElves(void)
{
    unsigned short index;
    printf("\n%sHelping elves...%s\n", RED, RESET);
    for(index=0; index < MINIMUN_ELVES_IN_TROUBLE; index++){
        elves.counter--;
        printf("\n%sAn elf was helped!%s\n", YELLOW, RESET);
        sleep(5);
    }

    return 0;
}

static int getHelp(void)
{
    srand(time(NULL));
    while (!(elvesFinalized)) {
        if (rand() % 5 == 1) {
            elves.counter += 1;
            printf("%s\nI need help (An Elf).%s\n", GREEN, RESET);
            
            pthread_mutex_lock(&santaMutex);
            pthread_cond_signal(&santasRest);
            pthread_mutex_unlock(&santaMutex);

            elvesFinalized = 1;
            sleep(5);
        }
    }
    
    return 1;
}

static void constructor(christmasStruct e, unsigned quantity)
{
    LOG("Constructing");
    e.lock = opened;
    e.counter = quantity;
    LOG("Construction sucessfull");
}