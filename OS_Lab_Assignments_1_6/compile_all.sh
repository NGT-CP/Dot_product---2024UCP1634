#!/bin/bash

echo "Assignment 2"
gcc Assignment_2/p1_finite_process.c -o p1_finite_process
gcc Assignment_2/monitor.c -o monitor
gcc Assignment_2/fork_child.c -o fork_child
gcc Assignment_2/fork_variables.c -o fork_variables
gcc Assignment_2/fork_wait_exit_execv.c -o fork_wait_exit_execv

echo "Assignment 3"
g++ Assignment_3/file_info.cpp -o file_info
g++ Assignment_3/system_info.cpp -o system_info
g++ Assignment_3/simple_shell.cpp -o simple_shell

echo "Assignment 4"
g++ Assignment_4/fcfs.cpp -o fcfs
g++ Assignment_4/sjf_nonpreemptive.cpp -o sjf_nonpreemptive
g++ Assignment_4/sjf_preemptive.cpp -o sjf_preemptive
g++ Assignment_4/priority_nonpreemptive.cpp -o priority_nonpreemptive
g++ Assignment_4/priority_preemptive.cpp -o priority_preemptive
g++ Assignment_4/round_robin.cpp -o round_robin

echo "Assignment 5"
gcc Assignment_5/ass5.c -o ass5

echo "Assignment 6"
gcc Assignment_6/dekker.c -o dekker
gcc Assignment_6/lamport_bakery.c -o lamport_bakery
gcc Assignment_6/peterson.c -o peterson
gcc Assignment_6/q2_peterson.c -o q2_peterson
gcc Assignment_6/bank.c -o bank -pthread
gcc Assignment_6/semaphore.c -o semaphore -pthread
gcc Assignment_6/threads.c -o threads -pthread

echo "Done"
