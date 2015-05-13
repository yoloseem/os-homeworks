/* simul.c */
#include <stdio.h>
#include <stdlib.h>

#define ERROREXIT() {printf("ERROR!\n"); exit(0);}

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

// (Integer) Number of process to be scheduled
int n;

int main (int argc, char** argv) {
    if (argc == 3) {
        /* Input from text file
         *     $ ./exename [filename] [policy]
         *
         * Text file must be in format of:
         *     Each line contains: "[burst time] [priority] [start time]"
         *     "0 0 0" indicates the end of the input */
        FILE *inputFp = fopen(argv[1], "r");
        while( inputFp ) {
            fscanf(inputFp, "%d%d%d",
                   &procs[n].burstTime, &procs[n].priority, &procs[n].startAt);
            if (!(procs[n].burstTime | procs[n].priority | procs[n].startAt))
                break;
            n++;
        }
        if (!n) ERROREXIT();
        printf("Scheduling %d processes...\n", n);
    }
    else {
        printf("Execute the program in format of:\n");
        printf("    $ %s [filename] [policy]\n", argv[0]);
    }

    return 0;
}
