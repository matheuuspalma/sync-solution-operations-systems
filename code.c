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


    return 0;
}

static void semaphoreConstructor(void)
{
    memcpy(semaphore.signal, signal,sizeof(signal));
    //semaphore.signal = &signal;
    memcpy(semaphore.wait, wait, sizeof(wait));
    //semaphore.wait = &wait;
}

static void wait(void)
{
    semaphore.control = semaphoreWait;
}

static void signal(void)
{
    semaphore.control = semaphoreSignal;
}
