# OS-CPU-Scheduler-Sim

This project was done in C++.

In this project, I simulated the scheduling algorithms of Round Robin, Non-Preemptive Shortest Job First, and Shortest Remaining Time First scheduling algorithms.

This was done by reading in a given input file in the form "Process ID / Burst Time / Arrival Time". With that information, I read the data into a deque data structure and managed ready/wait queues in order to print out a Gantt chart which simulates the order of the scheduling algorithms.

It then prints out the Gantt Chart, and executes calculations to print out the Turnaround Time and Waiting Time for each process depending on which algorithm was chosen to execute.
