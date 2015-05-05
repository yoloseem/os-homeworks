#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#define DEBUG true
#define debug_print(fmt, ...) \
    do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#define HUNGRY 0
#define EATING 1
#define THINKING 2

#define NUM_PHIL 5
#define EXEC_TIME 600

typedef struct philosopher {
    unsigned short numEat; int state;
    long wait;
} philosopher;
philosopher phil[NUM_PHIL];

sem_t chopstick[NUM_PHIL];

int idlewait () // 10~500 msec wait
{
    int sleepTimeMS = (rand() % 491 + 10);
    usleep(sleepTimeMS * 1000);
    return sleepTimeMS;
}

unsigned int tick () { //get current time (msec)
    struct timeval tv;
    gettimeofday(&tv, (void*)0);
    return tv.tv_sec * (unsigned int)1000 + tv.tv_usec / 1000;
}

void initPhil (void) {
    unsigned short i;
    for (i=0; i<NUM_PHIL; i++) {
        phil[i].numEat = 0;
        phil[i].state = THINKING;
        phil[i].wait = 0;
    }
}

void* dining (void* arg) {
    unsigned short i;
    unsigned short left, right;
    unsigned int start_time;
    unsigned int start_hungry, end_hungry;

    /* .......... To be implemented */
}

int main (void) {
    pthread_t t[NUM_PHIL];
    unsigned short i, args[NUM_PHIL], minCount = USHRT_MAX, maxCount =0;
    long start, end, minWait = LONG_MAX, maxWait = 0, waitAVG = 0, waitVar = 0;
    double countAVG = 0, countVar = 0;

    srand(time(NULL));
    start = tick();
    initPhil();

    for (i=0; i<NUM_PHIL; i++)
        args[i] = i;

    /* .......... To be implemented */

    end = tick();

    for (i=0; i<NUM_PHIL; i++) {
        printf("Philosopher %d eating count : %d\nPhilosopher %d waiting time in HUNGRY state : %ld.%ld sec\n\n", i, phil[i].numEat, i, phil[i].wait / 1000, phil[i].wait % 1000);
        countAVG += phil[i].numEat;

        if(minCount > phil[i].numEat)
            minCount = phil[i].numEat;
        if (maxCount < phil[i].numEat)
            maxCount = phil[i].numEat;

        waitAVG += phil[i].wait;

        if (minWait > phil[i].wait)
            minWait = phil[i].wait;
        if (maxWait < phil[i].wait)
            maxWait = phil[i].wait;
    }
    countAVG /= NUM_PHIL;
    waitAVG /= NUM_PHIL;

    for (i=0; i<NUM_PHIL; i++) {
        countVar += (countAVG - phil[i].numEat) * (countAVG - phil[i].numEat);
        waitVar += (waitAVG - phil[i].wait) * (waitAVG - phil[i].wait);
    }
    countVar /= NUM_PHIL;
    waitVar /= NUM_PHIL;

    printf("Min count : %d\nMax count : %d\nAVG count : %.3f\nCount variance : %.3f\n\n", minCount, maxCount, countAVG, countVar);
    printf("Min wait time in HUNGRY state : %ld.%ld sec\nMax wait time in HUNGRY state : %ld.%ld sec\nAVG wait time in HUNGRY state : %ld.%ld sec\nVariance wait time in HUNGRY state : %ld.%ld sec\n\n", minWait / 1000, minWait % 1000, maxWait / 1000, maxWait % 1000, waitAVG / 1000,waitAVG % 1000, waitVar / 1000000, (waitVar % 1000000) / 1000);
    printf("Total run time : %ld.%ld sec\n\n", (end - start)/ 1000, (end - start)% 1000);

    return 0;
}
