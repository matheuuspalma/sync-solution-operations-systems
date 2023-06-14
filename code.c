/*Rio de Janeiro - Federal University of Rio de Janeiro*/

/********** Includes *********/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "code.h"


/********* Statics functions declarations */

static void semaphoreConstructor(semaphoreStruct, unsigned);
static void wait(operations *);
static void signal(operations *);
static int santaThread(void);
static int reindeersThread(void);
static int elvesThread(void);

/********* Variable declarations */

semaphoreStruct santa, reindeers, elves;

/********* Functios definitions*/
int main(void)
{
    pthread_t santaId;
    pthread_t reindeersId;
    pthread_t elvesId;

    LOG("Debug mode on!\n");

    semaphoreConstructor(santa, 0);
    semaphoreConstructor(reindeers, 9);
    semaphoreConstructor(elves, 0);

    pthread_create(&santaId, NULL, (THREAD_FUNC_PTR)&santaThread, NULL);
    pthread_create(&reindeersId, NULL,(THREAD_FUNC_PTR)&reindeersThread, NULL);
    pthread_create(&elvesId, NULL, (THREAD_FUNC_PTR)&elvesThread, NULL);

    sleep(20);

    return 0;
}

static int santaThread(void)
{
    LOG("Santa's thread is running!\n");
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

static void semaphoreConstructor(semaphoreStruct semaphore, unsigned quantity)
{
    LOG("Constructing");
    semaphore.signal = &signal;
    semaphore.wait = &wait;
    semaphore.counter = quantity;
    LOG("Construction sucessfull");
}

static void wait(operations *control)
{
    *control = semaphoreWait;
    LOG("Waiting!!");
}

static void signal(operations *control)
{
    *control = semaphoreSignal;
    LOG("Signal!!");
}
