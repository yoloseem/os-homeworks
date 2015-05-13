/* simul.c */
#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct Process {
    // (Integer) Bursting time in milliseconds
    int burstTime;
    // (Integer) Priority (lower value = higher prioirty)
    int priority;
    // (Integer) Time at the process appeared/created
    int startAt;
} Process;
Process procs[MAX_PROCESSES];


int main (void) {
    printf("Hyunjun gonna start hw 3\n");

    return 0;
}
