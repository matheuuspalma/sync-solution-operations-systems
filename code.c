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

/*This is a variable of control and is responsible to say if
  the variable elvesWithTrouble can be readed. */
boolean elvesWithTroubleIsFree = true;

/*This is a variable of control and is responsible to say if
  the variable reindeersCounteR can be readed. */
boolean reindeersCounterIsFree = true;

/*This is a variable of control and is responsible to say if
  the variable elvesShouldWaitChristmasEnd can be readed. */
boolean elvesShouldWaitChristmasEndIsFree = true;

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
        if(reindeersCounterIsFree == true)
        {
            if(reindeers.counter >= ALL_REINDEERS_RETURNED)
            {
                LOG("Santa should awake !!");
                LOG("Elves should wait until after Christmas!!");
                prepareSleigh();
                reindeers.reindeersShouldGetHitched = true;
            }
            if(elvesWithTroubleIsFree == true)
            {
                if(elves.elvesWithTrouble >= MINIMUN_ELVES_IN_TROUBLE )
                {
                    LOG("Santa should awake and help Elves!!");
                    helpElves();
                }
                else
                {
                    LOG("Santa should keep resting !!");
                }
            }
            else
            {
                LOG("Santa should keep resting !!");
            }
        }
        else
        {
            LOG("Santa should keep resting !!");
        }
    }
    return OK;
}

static int reindeersThread(void)
{
    LOG("Reindeers' thread is running!");
    while (1)
    {
        if(IS_EVEN(rand())) //mocking a radom event to simulate the reindeers arriving from south pacific.
        {
            /* Região crítica */
            reindeersCounterIsFree = false;
            reindeers.counter++;
            reindeersCounterIsFree = true;
            LOG("waiting in a warming hut");
        }

        if(reindeers.reindeersShouldGetHitched = true)
        {
            LOG("All reindeers getting Hitched !!");
            getHitched();
            break;
        }
    }
    return OK;
}

static int elvesThread(void)
{
    LOG("Elves' thread is running!");

    while (1)
    {
        if(IS_EVEN(rand())) //mocking a random event to simulate the elves getting trouble.
        {
            if(elvesShouldWaitChristmasEndIsFree == true)
            {
                if(santa.elvesShouldWaitChristmasEnd == false)
                {
                    LOG("Getting help from santa !!");
                    getHelp();

                    /* Região crítica */
                    elvesWithTroubleIsFree = false;
                    elves.elvesWithTrouble += 1;
                    elvesWithTroubleIsFree = true;
                    /*****************/
                }
                else
                {
                    LOG("Waiting for christmas end!!");
                    break;
                }
            }
        }
    }
    return OK;
}

static int prepareSleigh(void)
{
    /* Região crítica */
    elvesShouldWaitChristmasEndIsFree = false;
    santa.elvesShouldWaitChristmasEnd = true;
    elvesShouldWaitChristmasEndIsFree = true;

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
    while(elvesWithTroubleIsFree == false)
    {

    }
    elves.elvesWithTrouble -= 3;
    return OK;
}
static int getHelp(void)
{

    return OK;
}

static void santaConstructor(void)
{
    santa.lock = opened;
    santa.shouldSleep = true;
}
static void reindeersConstructor(void)
{
    reindeers.lock = opened;
    reindeers.counter = 0;
    reindeers.reindeersShouldGetHitched = false;
}
static void elvesConstructor(void)
{
    elves.lock = opened;
    elves.elvesWithTrouble = 0;
    elves.elvesShouldWaitChristmasEnd = false;
}
