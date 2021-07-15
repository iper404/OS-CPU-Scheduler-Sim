# OS-CPU-Scheduler-Sim

![os_scheduler_in_action](https://user-images.githubusercontent.com/48579650/125851734-66b06e5e-5eb0-4f96-9ced-2e1df1c007df.gif)


This project was done in C++.

In this project, I simulated the scheduling algorithms of Round Robin, Non-Preemptive Shortest Job First, and Shortest Remaining Time First scheduling algorithms.

This was done by reading in a given input file in the form "Process ID / Burst Time / Arrival Time". With that information, I read the data into a deque data structure and managed ready/wait queues in order to print out a Gantt chart which simulates the order of the scheduling algorithms.

It then prints out the Gantt Chart, and executes calculations to print out the Turnaround Time and Waiting Time for each process depending on which algorithm was chosen to execute.
