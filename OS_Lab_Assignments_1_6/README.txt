OS LAB ASSIGNMENTS 1-6
========================

This folder contains the exam-oriented code/reference files prepared
from the assignment questions provided.

ASSIGNMENT 1
------------
commands.txt

ASSIGNMENT 2
------------
p1_finite_process.c
monitor.c
fork_child.c
aslr_commands.txt
fork_variables.c
fork_wait_exit_execv.c

ASSIGNMENT 3
------------
file_info.cpp
system_info.cpp
simple_shell.cpp

ASSIGNMENT 4
------------
Part A uses your existing p13.cpp CPU/I/O simulator.
proc.dat is included as a sample input.

Standalone scheduling programs:
fcfs.cpp
sjf_nonpreemptive.cpp
sjf_preemptive.cpp
priority_nonpreemptive.cpp
priority_preemptive.cpp
round_robin.cpp

Part B/C inputs:
FCFS / SJF:
n
arrival burst

Priority:
n
arrival burst priority

Round Robin:
n
arrival burst
quantum

ASSIGNMENT 5
------------
ass5.c

ASSIGNMENT 6
------------
dekker.c
lamport_bakery.c
peterson.c
q2_peterson.c
bank.c
semaphore.c
threads.c

COMMON COMPILE COMMANDS
-----------------------
gcc file.c -o out
gcc file.c -o out -pthread

g++ file.cpp -o out

RUN
---
./out

NOTES
-----
1. These are intentionally kept simple for lab-exam memorization.
2. Assignment 4 Part A is not recreated here because the previously
   tested p13.cpp was already developed separately.
3. Assignment 6 Q2 uses 2 producers/2 consumers for "multiple" cases,
   because basic Peterson's algorithm is a two-process mutual exclusion
   algorithm.
