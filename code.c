/*Rio de Janeiro - Federal University of Rio de Janeiro*/

/********** Includes *********/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

#include "code.h"


/********* Statics functions declarations */

static void reindeersConstructor(void);
static void elvesConstructor(void);
static void santaConstructor(void);
static int santaThread(void);
static int reindeersThread(unsigned int *);
static int elvesThread(unsigned int *);
static int prepareSleigh(void);
static int getHitched(void);
static int helpElves(void);
static void getHelp(unsigned int *);
static int random(void);

/********* Variable declarations */

pthread_mutex_t santaMutex;
pthread_mutex_t reindeersMutex;
pthread_mutex_t elvesMutex;

santaStruct santa;
reindeersStruct reindeers;
elvesStruct elves;


int qtChristmas = NUMBER_OF_CHRISTMAS;

/********* Main Function definition*/
int main(void)
{

    unsigned char index;
    pthread_t santaT;
    pthread_t reindeersT[NUMBER_OF_REINDEERS];
    pthread_t elvesT[NUMBER_MAX_ELVES];
    unsigned int elvesId[NUMBER_MAX_ELVES];
    unsigned int reindeersId[NUMBER_OF_REINDEERS];

    void *retValSanta;

    LOG("Debug mode on!\n");

    santaConstructor();
    reindeersConstructor();
    elvesConstructor();

    pthread_create(&santaT, NULL, (THREAD_FUNC_PTR)&santaThread, NULL);

    for(index = 0; index < NUMBER_MAX_ELVES; index++){
        elvesId[index] = index + 1;
        pthread_create(&elvesT[index], NULL, (THREAD_FUNC_PTR)&elvesThread, (void *)&elvesId[index]);
    }
    sleep(1);
    for(index = 0; index < NUMBER_OF_REINDEERS; index++){
        reindeersId[index] = index + 1;
        pthread_create(&reindeersT[index], NULL,(THREAD_FUNC_PTR)&reindeersThread, (void *)&reindeersId[index]);
    }

    /* Papai noel vai ser a ultima thread a terminar. ou seja, ao aguardar por ela garantimos que as outras ja terminaram.*/
    pthread_join(santaT, &retValSanta);

    if(qtChristmas)
    {
        qtChristmas--;
        main();
    }

    return OK;
}

/********* Threads Functios definitions*/
static int santaThread(void)
{

    LOG("\n%sSanta's thread is running!%s\n", WHITE, RESET);
    printf("\n%sSanta is sleeping%s\n",YELLOW, RESET);

    while(1)
    {
        pthread_mutex_lock(&reindeersMutex);
        pthread_mutex_lock(&elvesMutex);
        if(reindeers.counter == ALL_REINDEERS_RETURNED)
        {
            pthread_mutex_unlock(&reindeersMutex);
            pthread_mutex_unlock(&elvesMutex);
            printf("\n%sSanta should awake to prepare Sleigh !!%s\n", YELLOW, RESET);
            printf("\n%sElves should wait until Christmas END!!%s\n", YELLOW, RESET);
            prepareSleigh();
            break;

        }
        if(elves.elvesWithTrouble >= MAX_ELVES_IN_TROUBLE)
        {
            pthread_mutex_unlock(&elvesMutex);
            pthread_mutex_unlock(&reindeersMutex);
            printf("\n%sSanta should awake to help Elves !!%s\n", YELLOW, RESET);
            helpElves();
        }
        else
        {
            pthread_mutex_unlock(&elvesMutex);
            pthread_mutex_unlock(&reindeersMutex);
            printf("\n%sSanta should keep resting !!%s\n", YELLOW, RESET);
        }
        sleep(1);

    }
    return OK;
}

static int reindeersThread(unsigned int *id)
{
    LOG("\n%sReindeers thread is running!%s\n", WHITE, RESET);

    sleep(1);

    while(1)
    {
        if(EVENT(random())) //mock that simulate an reindeer arriving or not from pacific
        {
            printf("\n%sI'm the reindeers %d and arrived in the Pole!%s\n", BLUE, *id, RESET);

            pthread_mutex_lock(&reindeersMutex);
            reindeers.counter += 1;
            LOG("reindeers counter = %d", reindeers.counter);
            pthread_mutex_unlock(&reindeersMutex);
            break;
        }
        sleep(1);
    }

    printf("\n%sWaiting in a warming hut! %s\n", BLUE, RESET);

    while(1)
    {
        if(reindeers.reindeersShouldGetHitched == true){
            getHitched();
            break;
        }
        sleep(1);
    }
    return OK;
}

static int elvesThread(unsigned int *id)
{
    pthread_t getHelpId;
    LOG("\n%sElves' thread is running!%s\n", WHITE, RESET);

    while(1)
    {
        pthread_mutex_lock(&elvesMutex);
        if(elves.elvesShouldWaitChristmasEnd == true)
        {
            pthread_mutex_unlock(&elvesMutex);
            break;
        }
        pthread_mutex_unlock(&elvesMutex);

        if (EVENT(random())) /*Condicional to mock an random event that simulate an elve getting trouble making toys.*/
        {
            while (1)
            {
                pthread_mutex_lock(&elvesMutex);
                if(elves.elvesWithTrouble < MAX_ELVES_IN_TROUBLE)
                {
                    pthread_create(&getHelpId, NULL, (THREAD_FUNC_PTR)&getHelp, (void *)id);
                    elves.elvesWithTrouble++;
                    LOG("Elves counter = %d", elves.elvesWithTrouble);
                    pthread_mutex_unlock(&elvesMutex); //is necessary call unlock because the thread will be waiting getHelp finish.
                    pthread_join(getHelpId, NULL);
                    break;
                }
            pthread_mutex_unlock(&elvesMutex);
            break;
            }
        }
    //    sleep(1);
    }

    return OK;
}


/********* Auxiliar Functios definitions*/
static int prepareSleigh(void)
{

    printf("\n%sPreparing sleigh!%s\n", BLUE, RESET);

    /*Não tem necessidade de lock devido ao fato de serem escrita apenas uma vez em uma thread em apenas um lugar*/

    reindeers.reindeersShouldGetHitched = true;
    elves.elvesShouldWaitChristmasEnd = true;

    printf("\n%sDelivering gifts...%s\n", BLUE, RESET);

    sleep(3);

    return OK;
}

static int getHitched(void)
{
    printf("%s\nSleigh Hitched!%s\n", BLUE, RESET);
    return OK;
}

static int helpElves(void)
{
    unsigned short index;
    printf("\n%sHelping elves...%s\n", RED, RESET);

    pthread_mutex_lock(&santaMutex);
    santa.santaIsHelping = true;

    pthread_mutex_lock(&elvesMutex);
    for(index=0; index < MAX_ELVES_IN_TROUBLE; index++){
        elves.elvesWithTrouble--;
        printf("\n%sAn elf was helped!%s\n", YELLOW, RESET);
        sleep(1);
    }
    pthread_mutex_unlock(&elvesMutex);
    pthread_mutex_unlock(&santaMutex);
    return OK;
}

static void getHelp(unsigned int *id)
{

    printf("\n%sI'm the elve number %d and i'm with trouble.\nAsking help for Santa!!!!%s\n",GREEN, *id,RESET);

    while(1) {
        pthread_mutex_lock(&santaMutex);
        if (santa.santaIsHelping == true) {
            pthread_mutex_unlock(&santaMutex);
            break;
        }
        pthread_mutex_unlock(&santaMutex);
        sleep(1);
    }
}

static int random()
{
    srand(time(NULL));

    return rand();
}

static void santaConstructor(void)
{
    pthread_mutex_init(&santaMutex, NULL);
    santa.santaIsHelping = false;
}
static void reindeersConstructor(void)
{
    pthread_mutex_init(&reindeersMutex, NULL);
    reindeers.counter = 0;
    reindeers.reindeersShouldGetHitched = false;
}
static void elvesConstructor(void)
{
    pthread_mutex_init(&elvesMutex, NULL);
    elves.elvesWithTrouble = 0;
    elves.elvesShouldWaitChristmasEnd = false;
}
