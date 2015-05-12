# Process Scheduling Simulator

* Implement a program that simulates CPU's process scheduling algorithm:
    * FCFS
    * SJF (non-preemptive)
    * Prioirty
    * Round-Robin
* Time continues in unit of millisecond and let us ignore any overheads on context switching.
* Print Gantt chart for process schedule and waiting times for each process
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

## Due: ~2015.05.07 23:59
