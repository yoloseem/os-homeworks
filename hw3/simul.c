/* simul.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROREXIT() {printf("ERROR!\n"); exit(0);}

#define MAX_PROCESSES 10
#define MAX_TIMELAPSE 100
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

short gantt[MAX_TIMELAPSE];

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

                if (firstStartAt > procs[i].startAt) {
                    firstStartAt = procs[i].startAt;
                    pick = i;
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
                    quantum--;
                    break;
                }
            }
            if (i == n) {
                pick = -1;
                quantum = 0;
            }
        }
        else if (policy == PRIOR) {
            /* PRIOR's picking: Highest priority first (preemptive,
             * lower value is higher priority */
            int highprior = 0x7fffffff;
            if (pick != -1 && procs[pick].burstTime == 0) pick = -1;
            if (pick == -1) {
                for (i=0; i<n; i++) {
                    if (procs[i].burstTime > 0) {
                        if (procs[i].startAt > timelapsed) {
                            futureProc = 1;
                            continue;
                        }
                        if (highprior > procs[i].priority) {
                            highprior = procs[i].priority;
                            pick = i;
                        }
                    }
                }
            }
        }
        else if (policy == SJF) {
            pick = -1;
            int shortestBurst = 0x7fffffff;
            /* SJF's picking criteria: shortest remaining burst (burstTime) */
            for (i=0; i<n; i++) {
                if (procs[i].burstTime <= 0) continue;
                if (procs[i].startAt > timelapsed) {
                    futureProc = 1;
                    continue;
                }

                if (shortestBurst > procs[i].burstTime) {
                    shortestBurst = procs[i].burstTime;
                    pick = i;
                }
            }
        }

        if (futureProc == 0 && pick == -1) // No more processes to be executed
            break;

        if (pick != -1) {
            gantt[timelapsed] = pick + 1;
            for (i=0; i<n; i++) {
                if (procs[i].burstTime <= 0) continue;
                if (i == pick)
                    procs[i].burstTime--;
                else
                    procs[i].waitTime++;
            }
        }
        else { // there will be some processes in future
            gantt[timelapsed] = -1;
        }

    } while (++timelapsed);

    printf("0 ");
    for (i=1; i<=timelapsed; i++) {
        if (i % 5 == 0) printf("%2d", i);
        else printf("  ");
    }
    if (timelapsed % 5) printf("%2d", timelapsed);
    printf("\n");
    for (i=0; i<=timelapsed; i++) {
        if (gantt[i] > 0) printf(" %d", gantt[i]);
        else printf(" -");
    }
    printf("\n\n");

    double avgWait = 0.0;
    for (i=0; i<n; i++) {
        printf("Process %d waiting time = %d msec\n",
               i + 1, procs[i].waitTime);
        avgWait += procs[i].waitTime;
    }
    avgWait /= n;
    printf("Average waiting time = %.1f msec\n", avgWait);

    return 0;
}
