# Process Scheduling Simulator

* Implement a program that simulates CPU's process scheduling algorithm:
    * FCFS -- [First-come, first-served](https://en.wikipedia.org/wiki/First-come,_first-served)
    * SJF -- [Shortest job next](https://en.wikipedia.org/wiki/Shortest_job_next) (non-preemptvie)
    * Priority -- [Fixed-prioirty pre-emptive scheduling](https://en.wikipedia.org/wiki/Fixed-priority_pre-emptive_scheduling)
    * RR -- [Round-robin](https://en.wikipedia.org/wiki/Round-robin_scheduling)
* Time continues in unit of millisecond and let us ignore any overheads on context switching.
* Print [Gantt chart](https://en.wikipedia.org/wiki/Gantt_chart) for process schedule and waiting times for each process
* Define the `struct` for process

Execution format:
```bash
$ ./executable_name [input filename] [scheduling policy]
```

Example:
```bash
$ ./simulator processes.input rr
Gantt Chart:
0          5        10        15        20
 1 1 1 1 1 2 2 2 2 2 3 3 3 3 3 4 4 4 4 4 -

Process 1 waiting time = 0 msec
Process 2 waiting time = 5 msec
Process 3 waiting time = 10 msec
Process 4 waiting time = 15 msec
Average waiting time = 7.5 msec
```

## Submissions

* Report
    * Includes: Annotated source codes, Execution results (Screenshot)
* Raw source codes

## Due: ~2015.05.14 23:59
