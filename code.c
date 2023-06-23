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

christmasStruct santa, reindeers, elves;

int processing = 0;

/********* Functios definitions*/
int main(void)
{
    pthread_t santaId;
    pthread_t reindeersId;
    pthread_t elvesId;

    LOG("Debug mode on!\n");

    constructor(santa, 0);
    constructor(reindeers, 0);
    constructor(elves, 0);

    pthread_create(&santaId, NULL, (THREAD_FUNC_PTR)&santaThread, NULL);
    pthread_create(&reindeersId, NULL,(THREAD_FUNC_PTR)&reindeersThread, NULL);
    pthread_create(&elvesId, NULL, (THREAD_FUNC_PTR)&elvesThread, NULL);

    sleep(20);

    return 0;
}

static int santaThread(void)
{
    LOG("Santa's thread is running!\n");
    LOG("Santa is sleeping");

    while(processing)
    {

        if( reindeers.counter == ALL_ELVES_RETURNED ||
            elves.counter     == MINIMUN_ELVES_IN_TROUBLE)
        {
            LOG("Santa should awake !!");
            LOG("Elves should wait wait until after Christmas!!");
            prepareSleigh();
        }

        else if(reindeers.counter != ALL_ELVES_RETURNED ||
        elves.counter     == MINIMUN_ELVES_IN_TROUBLE )
        {
            LOG("Santa should awake !!");
            helpElves();
        }
        else
        {
             LOG("Santa should keep resting !!");
        }
    }
    sleep(10);
    return OK;
}

static int reindeersThread(void)
{
    LOG("Reindeers' thread is running!\n");
    sleep(10);
    return OK;
}

static int elvesThread(void)
{
    LOG("Elves' thread is running!\n");
    sleep(10);
    return OK;
}

static void constructor(christmasStruct e, unsigned quantity)
{
    LOG("Constructing");
    e.lock = opened;
    e.counter = quantity;
    LOG("Construction sucessfull");
}

static int prepareSleigh(void)
{
    return 0;
}
static int getHitched(void)
{
    return 0;
}

static int helpElves(void)
{
    return 0;
}
static int getHelp(void)
{
    return 0;
}
