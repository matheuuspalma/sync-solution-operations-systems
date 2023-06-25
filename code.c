/*Rio de Janeiro - Federal University of Rio de Janeiro*/

/********** Includes *********/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "code.h"


/********* Statics functions declarations */

static void reindeersConstructor(void);
static void elvesConstructor(void);
static void santaConstructor(void);
static int santaThread(void);
static int reindeersThread(void);
static int elvesThread(void);
static int prepareSleigh(void);
static int getHitched(void);
static int helpElves(void);
static int getHelp(void);

/********* Variable declarations */

santaStruct santa;
reindeersStruct reindeers;
elvesStruct elves;
time_t seed;

/********* Functios definitions*/
int main(void)
{
    pthread_t santaId;
    pthread_t reindeersId;
    pthread_t elvesId;
    void *retValSanta, *retValReindeers, *retValElves;

    struct timespec ts;

    seed = clock_gettime(CLOCK_REALTIME, &ts);
    srand(seed);

    LOG("Debug mode on!\n");

    santaConstructor();
    reindeersConstructor();
    elvesConstructor();


    pthread_create(&santaId, NULL, (THREAD_FUNC_PTR)&santaThread, NULL);
    pthread_create(&reindeersId, NULL,(THREAD_FUNC_PTR)&reindeersThread, NULL);
    pthread_create(&elvesId, NULL, (THREAD_FUNC_PTR)&elvesThread, NULL);

    pthread_join(santaId, &retValSanta);
    pthread_join(reindeersId, &retValReindeers);
    pthread_join(elvesId, &retValElves);

    return OK;
}

static int santaThread(void)
{
    LOG("Santa's thread is running!\n");
    LOG("Santa is sleeping");

    while(1)
    {
        if(reindeers.counter == ALL_REINDEERS_RETURNED)
        {
            LOG("Santa should awake !!");
            LOG("Elves should wait wait until after Christmas!!");
            prepareSleigh();
            santa.elveShouldWaitChristmasEnd = true;
            break;;
        }

        else if(reindeers.counter != ALL_REINDEERS_RETURNED &&
                elves.elvesWithTrouble >= MINIMUN_ELVES_IN_TROUBLE )
        {
            LOG("Santa should awake !!");
            helpElves();
        }
        else
        {
             LOG("Santa should keep resting !!");
        }
        sleep(1);
    }
    sleep(10);
    return OK;
}

static int reindeersThread(void)
{
    LOG("Reindeers' thread is running!");
    while (1)
    {
        if(IS_EVEN(rand())) //mocking a radom event to simulate the reindeers arriving from south pacific.
        {
            reindeers.counter++;
            LOG("waiting in a warming hut");
        }
        if(reindeers.counter == ALL_REINDEERS_RETURNED)
        {
            getHitched();
            break;
        }
        sleep(1);
    }
    return OK;
}

static int elvesThread(void)
{
    LOG("Elves' thread is running!");

    while (1)
    {
        if(IS_EVEN(rand())) //mocking a radom event to simulate the elves getting trouble.
        {
            elves.elvesWithTrouble += 1;
            if(santa.elveShouldWaitChristmasEnd == false)
            {
                LOG("Getting help from santa !!");
                getHelp();
            }
            else
            {
                LOG("Waiting for christmas end!!");
                break;
            }
        }
        sleep(2);
    }
    return OK;
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
    LOG("Helping elves!");
    /*região critica*/
    elves.elvesWithTrouble = 0;
    return OK;
}
static int getHelp(void)
{

    /*
    pedir ajuda a santa
    receber a resposta
    caso sim -> zerar numero de elves with trouble
    caso não -> esperar pelo fim do natal
    */
    return 0;
}

static void santaConstructor(void)
{
    santa.lock = opened;
    santa.shouldSleep = true;
    santa.elveShouldWaitChristmasEnd = false;
}
static void reindeersConstructor(void)
{
    reindeers.lock = opened;
    reindeers.counter = 0;
}
static void elvesConstructor(void)
{
    elves.lock = opened;
    elves.elvesWithTrouble = 0;
}
