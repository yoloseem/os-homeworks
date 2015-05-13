/* simul.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
// (Integer) Number indicating scheduling algorithm
int policy;
// Enum values for policy
const short FCFS=0, SJF=1, PRIOR=2, RR=3;
char *verbosePolicy[] = {"First-come, first-served",
                         "Shortest-job-frst",
                         "Prioirty-based",
                         "Round-robin"};

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
    }
    else {
        printf("Execute the program in format of:\n");
        printf("    $ %s [filename] [policy]\n", argv[0]);
    }

    printf("Scheduling %d processes... ", n);
    if (!strcmp(argv[2], "fcfs")) policy = FCFS;
    else if (!strcmp(argv[2], "sjf")) policy = SJF;
    else if (!strcmp(argv[2], "prior")) policy = PRIOR;
    else if (!strcmp(argv[2], "rr")) policy = RR;
    else ERROREXIT();
    printf("based on %s.\n", verbosePolicy[policy]);

    return 0;
}
