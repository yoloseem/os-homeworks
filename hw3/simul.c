/* simul.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROREXIT() {printf("ERROR!\n"); exit(0);}

#define MAX_PROCESSES 10
#define RR_QUANTUM 5

typedef struct Process {
    // (Integer) Bursting time in milliseconds
    int burstTime;
    // (Integer) Priority (lower value = higher prioirty)
    int priority;
    // (Integer) Time at the process appeared/created
    int startAt;
    // (Integer) Waiting time for the process
    int waitTime;
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
            procs[n].waitTime = 0;
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

    int i, timelapsed = 0;
    int quantum = RR_QUANTUM;
    int pick = -1;
    int futureProc = 0;

    do { // Repeat until there's no process that has remaining burst
        futureProc = 0;

        /* Picking process to run in next single millisecond
         * based on given scheduling policy */
        if (policy == FCFS) {
            pick = -1;
            int firstStartAt = 0x7fffffff;
            /* FCFS's picking criteria: first come (startAt) */
            for (i=0; i<n; i++) {
                if (procs[i].burstTime <= 0) continue;
                if (procs[i].startAt > timelapsed) {
                    futureProc = 1;
                    continue;
                }

                if (policy == FCFS) {
                    if (firstStartAt > procs[i].startAt) {
                        firstStartAt = procs[i].startAt;
                        pick = i;
                    }
                }
            }
        }
        else if (policy == RR) {
            /* RR's picking: switch to next only when current time quantum has
             * been ended */
            if (pick == -1) pick = 0;
            if (quantum == 0) {
                quantum = RR_QUANTUM;
                pick++;
            }
            for (i=0; i<n; i++) {
                if (procs[(pick + i) % n].burstTime > 0) {
                    if (procs[(pick + i) % n].startAt > timelapsed) {
                        futureProc = 1;
                        continue;
                    }
                    pick = (pick + i) % n;
                    break;
                }
            }
            if (i == n) pick = -1;
            else quantum--;
        }

        if (futureProc == 0 && pick == -1) // No more processes to be executed
            break;

        if (pick != -1) {
            printf("[DEBUG] At %d msec, running process #%d\n",
                   timelapsed, pick);
            for (i=0; i<n; i++) {
                if (procs[i].burstTime <= 0) continue;
                if (i == pick)
                    procs[i].burstTime--;
                else
                    procs[i].waitTime++;
            }
        }
        else { // there will be some processes in future
            printf("[DEBUG] At %d msec, no running process\n", timelapsed);
        }

    } while (++timelapsed);

    return 0;
}
