/*Rio de Janeiro - Federal University of Rio de Janeiro*/

/********** Includes *********/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "code.h"

/********* Variable functions declarations */


/********* Statics functions declarations */

static void semaphoreConstructor(void);
static void wait(void);
static void signal(void);

/********* Functios definitions*/

semaphoreFunctions semaphore;

int main(void)
{
    LOG("Debug mode on!\n");

    semaphoreConstructor();

    semaphore.signal();
    semaphore.wait();

    return 0;
}

static void semaphoreConstructor(void)
{
    LOG("Constructing");
    //memcpy(semaphore.signal, &signal(),sizeof(semaphore.signal));
    semaphore.signal = &signal;
    //memcpy(semaphore.wait, &wait(), sizeof(semaphore.wait));
    semaphore.wait = &wait;
    LOG("Construction sucessfull");
}

static void wait(void)
{
    semaphore.control = semaphoreWait;
    LOG("Waiting!!");
}

static void signal(void)
{
    semaphore.control = semaphoreSignal;
    LOG("Signal!!");
}
