//A lot of unused variables, but working as intended.
//Only issues might be with the "reason" strings

#include <iostream>
#include <string>
#include <fstream>
#include <deque>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int indexofSmallestElement(deque<int> array, int size);


int main(){
   /*
    string processID[] = {"A","B","C","D","E"};
    int burstTime[] = {10,1,2,1,5};
    int arrivalTime[] = {0,1,3,0,1};
    */
    const int TOTAL_PROCESSES = 8;

    //deque<string> processID;
    //deque<int> burstTime;
    //deque<int> arrivalTime;

    /*
    vector<string> processID;
    vector<int> burstTime;
    vector<int> arrivalTime;
    */

    deque<string> processIDQ;
    deque<int> processTimeQ;
    deque<string> reasonQ;
    deque<int> submissionTimeQ;
    deque<int> turnaroundTimeQ;
    deque<int> waitingTimeQ;

    deque<string> readyQID;
    deque<int> readyQBurst;
    deque<int> arrivalQRdy;
    deque<int> readyQInitialBurst;
    deque<int> quantumQ;

/*
    deque<string> readyQID;
    deque<int> readyQBurst;
    deque<int> arrivalQRdy;
*/
    deque<string> waitQID;
    deque<int> waitQBurst;
    deque<int> waitQInitialBurst;
    deque<int> waitQArrival;

    deque<int> completeQVal;
    deque<string> completeQID;
    deque<int> completeQSubmission;
    deque<int> completeQInitialBurst;


    string processID[TOTAL_PROCESSES] = {"Z", "Z", "Z", "Z", "Z", "Z", "Z", "Z"};
    int burstTime[TOTAL_PROCESSES] = {50, 50, 50, 50, 50, 50, 50, 50};
    int arrivalTime[TOTAL_PROCESSES] = {50, 50, 50, 50, 50, 50, 50, 50};


    string id = "";
    int burstVar = 0;
    int arrivalVar = 0;

    string termStr = "Process terminated";
    string quantStr = "Quantum expired";
    string preemptStr = "Process preempted by process with shorter burst time";
    string complStr = "Complete";

    int arrival = 0;
    int complete = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;

    int userChoice = 0;

    //read in data from inputfile
    ifstream file;
    file.open("Lab3inputfileF20.txt");

    if(!file){
        cout << "\n\n**Error, no file found. Exiting./n";
        return 0;
    }

    int fileCount = 0;

    while(fileCount < TOTAL_PROCESSES){
        string procID = "";
        int brstT = 0;
        int arrT = 0;

        file >> procID >> brstT >> arrT;

        processID[fileCount] = procID;
        burstTime[fileCount] = brstT;
        arrivalTime[fileCount] = arrT;
        fileCount++;
    }

    //testing
    for(int i = 0; i < TOTAL_PROCESSES; i++){
        cout << "\nProcessID: " << processID[i] << " | Burst Time: " <<
        burstTime[i] << " | Arrival Time: " << arrivalTime[i] << "\n";
    }

    cout << "\n***Welcome to the scheduler simulator***\n" << endl;
    cout << "Input: \n1: Non-Preemptive Shortest Job First\n2: Round Robin\n3: Shortest Remaining Time First\n\n";
    cin >> userChoice;

    if(userChoice == 1){
        cout << "\nSJF Scheduling\n";
        //associate w each process the length of its next CPU burst.
        //use these lengths to schedule the process with the shortest time.
        //Non-preemptive: once CPU given to the process it cannot be preempted until it completes its CPU burst

        //initial loop to set ready q
            int schedTime = 0;
            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] <= schedTime){
                    //pop into ready q
                    //first iter: [0] and [1] should pop into q
                    //3rd iter: [2]-[7] should pop into q
                    readyQID.push_back(processID[i]);
                    readyQBurst.push_back(burstTime[i]);
                    arrivalQRdy.push_back(arrivalTime[i]);
                    //cout << "Ready Q: " << readyQID[i] << endl;
                }
            }

            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] > schedTime){
                    waitQID.push_back(processID[i]);
                    waitQBurst.push_back(burstTime[i]);
                    waitQArrival.push_back(arrivalTime[i]);
                    //cout << "Wait Q: " << waitQID[i-2] << endl;
                }
            }
        //now we have the ready q populated with A and B.
        //wait Q has all other values.

        bool loop = true;
        while(loop == true){ //enter scheduling loop
            //check if wait queue's arrival time matches sched timer for next iteration of while loop
            while(waitQArrival[0] <= schedTime && waitQID.empty() == false){
                //if the first element in the wait q's arrival time is
                //<= current scheduling time, then we should
                //add it to the ready queue.
                //cout << "Ready Q Back: " << readyQID.back() << endl;
                readyQID.push_back(waitQID.front());
                waitQID.pop_front();
                readyQBurst.push_back(waitQBurst.front());
                waitQBurst.pop_front();
                arrivalQRdy.push_back(waitQArrival.front());
                waitQArrival.pop_front();
                //so now we add to rdy and pop off of wait until it's all done.
                if(waitQID.empty() == true){
                    //cout << "Ready Q Back: " << readyQID.back() << endl;
                    break;
                }
            }
            //rdy Q fully populated by the 3rd iteration
            //Iter 1: schedTime = 0
            //Iter 2: schedTime = 1
            //Iter 3: schedTime = 5

            //handle ready q data
            //let's find the smallest burst in the ready q and handle it
            //best way is to find the INDEX of the SMALLEST BURST
            int sizeOfQ = readyQBurst.size();
            int smallestBurstIndex = 0;
            if(sizeOfQ >= 2){ //iter 2 - only time size will be < 2.
                //cout << "Size of Q: " << sizeOfQ << endl;
                smallestBurstIndex = indexofSmallestElement(readyQBurst, sizeOfQ);
                //cout << "Smallest Burst: " << smallestBurstIndex << endl;
            }

            //now we should have the smallest index. let's handle it.
            //push it into the display queue and pop it off of the ready q.
            processIDQ.push_back(readyQID[smallestBurstIndex]);
            processTimeQ.push_back(schedTime);
            reasonQ.push_back(termStr);
            //take note of submission time into the Q
            submissionTimeQ.push_back(schedTime);
            //calc turnaround time?
            arrival = schedTime;
            //for SJF, readyQ submission is at 0 for all processes
            int readyQ = 0;

            //update Sched Time by adding current burst time
            schedTime += readyQBurst[smallestBurstIndex];

            //turnaround complete time
            complete = schedTime;

            //do calculation for turnaround time, store into queue
            turnaroundTime = complete - arrivalQRdy[smallestBurstIndex];
            turnaroundTimeQ.push_back(turnaroundTime);

            //calculate WAITING TIME -> turnaround time - cpu run time
            waitingTime = turnaroundTime - readyQBurst[smallestBurstIndex];
            waitingTimeQ.push_back(waitingTime);

            //now that we have the data we need, pop off of the ready q for next iter
            readyQID.erase(readyQID.begin() + smallestBurstIndex);
            readyQBurst.erase(readyQBurst.begin() + smallestBurstIndex);
            arrivalQRdy.erase(arrivalQRdy.begin() + smallestBurstIndex);

        if(readyQID.empty() == true && waitQID.empty() == true){
            loop = false; //break out of loop if rdy q & wait q is empty
            }
        } //end while loop

        //should be ready to display first set of rules
        //display everything in the queue
        for(int i = 0; i < TOTAL_PROCESSES; i++){
            cout << "\nProcessID: " << processIDQ[i] << " | Schedule Time: " <<
            processTimeQ[i] << " | Reason: " << reasonQ[i] << "\n";
            }

        cout << "\n\t||End Time: " << schedTime << " | " << complStr << "||\n\n";

        //Print 2nd set of rules - ID / Turnaround Time / Waiting Time
        //Turnaround time = completion time - submission time (arrival time)
        //Waiting time = turnaround time - burst time (CPU run time)

        int turnTotal = 0;
        int waitTotal = 0;
        int turnAvg = 0;
        int waitAvg = 0;

        for(int i = 0; i < TOTAL_PROCESSES; i++){
            cout << "\nProcessID: " << processIDQ[i] << " | Turnaround Time: " <<
            turnaroundTimeQ[i] << " | Waiting Time: " << waitingTimeQ[i] << "\n";
            turnTotal += turnaroundTimeQ[i];
            waitTotal += waitingTimeQ[i];
        }

        turnAvg = turnTotal / TOTAL_PROCESSES;
        waitAvg = waitTotal / TOTAL_PROCESSES;

        cout << "\n\t||Average Turnaround Time: " << turnAvg << " | Average Wait Time:"
            << waitAvg << "||\n\n";

        }

    else if(userChoice == 2){
        cout << "RR Scheduling: Q = 4\n";
        //preemptive RR. When SchedTime % 4 == 0. time to switch processes.
            //initial loop to set ready q
            int schedTime = 0;
            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] <= schedTime){
                    //pop into ready q
                    //first iter: [0] and [1] should pop into q
                    //3rd iter: [2]-[7] should pop into q
                    readyQID.push_back(processID[i]);
                    readyQBurst.push_back(burstTime[i]);
                    readyQInitialBurst.push_back(burstTime[i]);
                    arrivalQRdy.push_back(arrivalTime[i]);
                    //cout << "Ready Q: " << readyQID[i] << endl;
                }
            }

            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] > schedTime){
                    waitQID.push_back(processID[i]);
                    waitQBurst.push_back(burstTime[i]);
                    waitQInitialBurst.push_back(burstTime[i]);
                    waitQArrival.push_back(arrivalTime[i]);
                    //cout << "Wait Q: " << waitQID[i-2] << endl;
                }
            }
        //now we have the ready q populated with A and B.
        //wait Q has all other values.
        bool loop = true;
        while(loop == true){

            //check if wait queue's arrival time matches sched timer for next iteration of while loop
            while(waitQArrival[0] <= schedTime && waitQID.empty() == false){
                //if the first element in the wait q's arrival time is
                //<= current scheduling time, then we should
                //add it to the ready queue.
                //cout << "Ready Q Back: " << readyQID.back() << endl;
                readyQID.push_back(waitQID.front());
                waitQID.pop_front();
                readyQBurst.push_back(waitQBurst.front());
                waitQBurst.pop_front();
                readyQInitialBurst.push_back(waitQInitialBurst.front());
                waitQInitialBurst.pop_front();
                arrivalQRdy.push_back(waitQArrival.front());
                waitQArrival.pop_front();
                //so now we add to rdy and pop off of wait until it's all done.
                if(waitQID.empty() == true){
                    //cout << "Ready Q Back: " << readyQID.back() << endl;
                    break;
                }
            }

            if(processIDQ.empty() == true || schedTime == 0){
                //cout << "If 1" << endl;
                //This statement runs only for the first iteration

                processIDQ.push_back(readyQID.front());
                processTimeQ.push_back(schedTime);
                reasonQ.push_back(termStr);
                quantumQ.push_back(schedTime);
                //take note of submission time into the Q
                //submissionTimeQ.push_back(schedTime);
                
                //update schedTime for next iteration
                schedTime++;
                //we also need to subtract the burst time
                //for the current readyQBurst
                readyQBurst.front() = readyQBurst.front() - 1;
                quantumQ.front() = quantumQ.front() + 1;
                //if readyQBurst[i] is 0, process is complete. pop it off the queue.
                if(readyQBurst.front() == 0){
                    //first, let's track our completion time by adding the id, submission time 
                    //and the completion time to a q
                    completeQID.push_back(readyQID.front());
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy.front());
                    completeQInitialBurst.push_back(readyQInitialBurst.front());

                    //now we remove the process from the rdy q
                    readyQID.pop_front();
                    readyQBurst.pop_front();
                    arrivalQRdy.pop_front();
                    //reasonQ.push_back(termStr);
                    quantumQ.front() = 0;
                }
            }

            else if(processIDQ.back() != readyQID.front()){
                //in this case, we are swapping processes for the shortest remaining time process
                //OR the process just changed
               // cout << "If 2" << endl;
                processIDQ.push_back(readyQID.front());
                processTimeQ.push_back(schedTime);
                //reasonQ.push_back(preemptStr);
                //submissionTimeQ.push_back(schedTime);
                schedTime++;
                readyQBurst.front() = readyQBurst.front() - 1;
                quantumQ.front() = quantumQ.front() + 1;
                if(readyQBurst.front() == 0){
                    completeQID.push_back(readyQID.front());
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy.front());
                    completeQInitialBurst.push_back(readyQInitialBurst.front());

                    //now we remove the process from the rdy q
                    readyQID.pop_front();
                    readyQBurst.pop_front();
                    arrivalQRdy.pop_front();
                    reasonQ.push_back(termStr);
                    quantumQ.front() = 0;
                }
                else if(quantumQ.front() % 4 == 0){
                    //we hit our quant -> push front of the queue to the back
                    readyQID.push_back(readyQID.front());
                    readyQID.pop_front();
                    readyQBurst.push_back(readyQBurst.front());
                    readyQBurst.pop_front();
                    arrivalQRdy.push_back(arrivalQRdy.front());
                    arrivalQRdy.pop_front();
                    reasonQ.push_back(quantStr);
                    quantumQ.front() = 0;
                }
            }


            else{
                                //cout << "If 3" << endl;

                //in this case, we are in the same processID,
                //we don't need to change anything but we need to
                //accelerate schedTime
                schedTime++;
                readyQBurst.front() = readyQBurst.front() - 1;
                quantumQ.front() = quantumQ.front() + 1;
                //if readyQBurst[i] is 0, process is complete. pop it off the queue.
                if(readyQBurst.front() == 0){
                    completeQID.push_back(readyQID.front());
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy.front());
                    completeQInitialBurst.push_back(readyQInitialBurst.front());

                    //now we remove the process from the rdy q
                    readyQID.pop_front();
                    readyQBurst.pop_front();
                    arrivalQRdy.pop_front();
                    reasonQ.push_back(termStr);
                    quantumQ.front() = 0;
                }
                else if(quantumQ.front() % 4 == 0){
                    //we hit our quant -> push front of the queue to the back
                    readyQID.push_back(readyQID.front());
                    readyQID.pop_front();
                    readyQBurst.push_back(readyQBurst.front());
                    readyQBurst.pop_front();
                    arrivalQRdy.push_back(arrivalQRdy.front());
                    arrivalQRdy.pop_front();
                    reasonQ.push_back(quantStr);
                    quantumQ.front() = 0;
                }

            }


            if(readyQID.empty() == true && waitQID.empty() == true){
                    loop = false; //break out of loop if rdy q & wait q is empty
                }
        }

        int sizeOfQ = processIDQ.size();
        for(int i = 0; i < sizeOfQ; i++){
            cout << "\nProcessID: " << processIDQ[i] << " | Schedule Time: " <<
            processTimeQ[i] << " | Reason: " << reasonQ[i] << "\n";
            }

        cout << "\n\t||End Time: " << schedTime << " | " << complStr << "||\n\n";

        //for SRTF, we need to organize our data.
        int waitBurst = 0;
        sizeOfQ = completeQID.size();
        for(int i = 0; i < sizeOfQ; i++){
            turnaroundTime = completeQVal[i]-completeQSubmission[i];
            turnaroundTimeQ.push_back(turnaroundTime);

            for(int j = 0; j < sizeOfQ; j++){
                if(completeQID[i] == processID[j]){
                    waitBurst = burstTime[j];
                    break;
                }
            }

            waitingTime = turnaroundTime - waitBurst;
            waitingTimeQ.push_back(waitingTime);
            //this calculates the turnaround time & waiting time
            //for the ID in index[i] for the completeQID
        }

        //print final results
        int turnTotal = 0;
        int waitTotal = 0;
        int turnAvg = 0;
        int waitAvg = 0;

        for(int i = 0; i < sizeOfQ; i++){
            cout << "\nProcessID: " << completeQID[i] << " | Turnaround Time: " <<
            turnaroundTimeQ[i] << " | Waiting Time: " << waitingTimeQ[i] << "\n";
            turnTotal += turnaroundTimeQ[i];
            waitTotal += waitingTimeQ[i];
        }

        turnAvg = turnTotal / TOTAL_PROCESSES;
        waitAvg = waitTotal / TOTAL_PROCESSES;

        cout << "\n\t||Average Turnaround Time: " << turnAvg << " | Average Wait Time:"
            << waitAvg << "||\n\n";
        
    }

    else if(userChoice == 3){
        cout <<"SRTF Scheduling\n";
        //preemptive SJF. if a new process arrives with CPU burst length less than remaining
        //time of current executing process, preempt.
        //we need a time variable to keep track of each second
        //and we need to adjust the ready queue to reflect that

            //initial loop to set ready q
            int schedTime = 0;
            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] <= schedTime){
                    //pop into ready q
                    //first iter: [0] and [1] should pop into q
                    //3rd iter: [2]-[7] should pop into q
                    readyQID.push_back(processID[i]);
                    readyQBurst.push_back(burstTime[i]);
                    readyQInitialBurst.push_back(burstTime[i]);
                    arrivalQRdy.push_back(arrivalTime[i]);
                    //cout << "Ready Q: " << readyQID[i] << endl;
                }
            }

            for(int i = 0; i < TOTAL_PROCESSES; i++){
                if(arrivalTime[i] > schedTime){
                    waitQID.push_back(processID[i]);
                    waitQBurst.push_back(burstTime[i]);
                    waitQInitialBurst.push_back(burstTime[i]);
                    waitQArrival.push_back(arrivalTime[i]);
                    //cout << "Wait Q: " << waitQID[i-2] << endl;
                }
            }
        //now we have the ready q populated with A and B.
        //wait Q has all other values.
        bool loop = true;
        while(loop == true){ //enter scheduling loop
            //check if wait queue's arrival time matches sched timer for next iteration of while loop
            while(waitQArrival[0] <= schedTime && waitQID.empty() == false){
                //if the first element in the wait q's arrival time is
                //<= current scheduling time, then we should
                //add it to the ready queue.
                //cout << "Ready Q Back: " << readyQID.back() << endl;
                readyQID.push_back(waitQID.front());
                waitQID.pop_front();
                readyQBurst.push_back(waitQBurst.front());
                waitQBurst.pop_front();
                readyQInitialBurst.push_back(waitQInitialBurst.front());
                waitQInitialBurst.pop_front();
                arrivalQRdy.push_back(waitQArrival.front());
                waitQArrival.pop_front();
                //so now we add to rdy and pop off of wait until it's all done.
                if(waitQID.empty() == true){
                    //cout << "Ready Q Back: " << readyQID.back() << endl;
                    break;
                }
            }
            //Iter 1: schedTime = 0
            //Iter 2: schedTime = 1
            //Iter 3: schedTime = 2...etc
            //cout << "SchedTime: " << schedTime << endl;

            //handle ready q data
            //let's find the smallest burst in the ready q and handle it
            //best way is to find the INDEX of the SMALLEST BURST
            int sizeOfQ = readyQBurst.size();
            int smallestBurstIndex = 0;
            if(sizeOfQ >= 2){ //iter 2 - only time size will be < 2.
                //cout << "Size of Q: " << sizeOfQ << endl;
                smallestBurstIndex = indexofSmallestElement(readyQBurst, sizeOfQ);
               // cout << "Smallest Burst: " << smallestBurstIndex << endl;
            }

            //now we should have the smallest index. let's handle it.
            //check if the current process is different

            if(processIDQ.empty() == true || schedTime == 0){
                //cout << "If 1" << endl;
                //This statement runs only for the first iteration

                processIDQ.push_back(readyQID[smallestBurstIndex]);
                processTimeQ.push_back(schedTime);
                reasonQ.push_back(termStr);
                //take note of submission time into the Q
                //submissionTimeQ.push_back(schedTime);
                
                //update schedTime for next iteration
                schedTime++;
                //we also need to subtract the burst time
                //for the current readyQBurst
                readyQBurst[smallestBurstIndex] = readyQBurst[smallestBurstIndex] - 1;
                //if readyQBurst[i] is 0, process is complete. pop it off the queue.
                if(readyQBurst[smallestBurstIndex] == 0){
                    //first, let's track our completion time by adding the id, submission time 
                    //and the completion time to a q
                    completeQID.push_back(readyQID[smallestBurstIndex]);
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy[smallestBurstIndex]);
                    completeQInitialBurst.push_back(readyQInitialBurst[smallestBurstIndex]);

                    //now we remove the process from the rdy q
                    readyQID.erase(readyQID.begin() + smallestBurstIndex);
                    readyQBurst.erase(readyQBurst.begin() + smallestBurstIndex);
                    arrivalQRdy.erase(arrivalQRdy.begin() + smallestBurstIndex);
                    //reasonQ.push_back(termStr);
                }
            }

            else if(processIDQ.back() != readyQID[smallestBurstIndex]){
                //in this case, we are swapping processes for the shortest remaining time process
                //OR the process just changed
               // cout << "If 2" << endl;
                processIDQ.push_back(readyQID[smallestBurstIndex]);
                processTimeQ.push_back(schedTime);
                reasonQ.push_back(preemptStr);
                //submissionTimeQ.push_back(schedTime);
                schedTime++;
                readyQBurst[smallestBurstIndex] = readyQBurst[smallestBurstIndex] - 1;
                if(readyQBurst[smallestBurstIndex] == 0){
                    completeQID.push_back(readyQID[smallestBurstIndex]);
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy[smallestBurstIndex]);
                    completeQInitialBurst.push_back(readyQInitialBurst[smallestBurstIndex]);

                    readyQID.erase(readyQID.begin() + smallestBurstIndex);
                    readyQBurst.erase(readyQBurst.begin() + smallestBurstIndex);
                    arrivalQRdy.erase(arrivalQRdy.begin() + smallestBurstIndex);
                    reasonQ.push_back(termStr);
                }
            }


            else{
                                //cout << "If 3" << endl;

                //in this case, we are in the same processID,
                //we don't need to change anything but we need to
                //accelerate schedTime
                schedTime++;
                readyQBurst[smallestBurstIndex] = readyQBurst[smallestBurstIndex] - 1;
                //if readyQBurst[i] is 0, process is complete. pop it off the queue.
                if(readyQBurst[smallestBurstIndex] == 0){
                    completeQID.push_back(readyQID[smallestBurstIndex]);
                    completeQVal.push_back(schedTime);
                    completeQSubmission.push_back(arrivalQRdy[smallestBurstIndex]);
                    completeQInitialBurst.push_back(readyQInitialBurst[smallestBurstIndex]);

                    readyQID.erase(readyQID.begin() + smallestBurstIndex);
                    readyQBurst.erase(readyQBurst.begin() + smallestBurstIndex);
                    arrivalQRdy.erase(arrivalQRdy.begin() + smallestBurstIndex);
                    reasonQ.push_back(termStr);
                }

            }

            if(readyQID.empty() == true && waitQID.empty() == true){
                    loop = false; //break out of loop if rdy q & wait q is empty
                }
        } //end while loop

        //should be ready to display first set of rules
        //display everything in the queue
        int sizeOfQ = processIDQ.size();
        for(int i = 0; i < sizeOfQ; i++){
            cout << "\nProcessID: " << processIDQ[i] << " | Schedule Time: " <<
            processTimeQ[i] << " | Reason: " << reasonQ[i] << "\n";
            }

        cout << "\n\t||End Time: " << schedTime << " | " << complStr << "||\n\n";

        //for SRTF, we need to organize our data.
        int waitBurst = 0;
        sizeOfQ = completeQID.size();
        for(int i = 0; i < sizeOfQ; i++){
            turnaroundTime = completeQVal[i]-completeQSubmission[i];
            turnaroundTimeQ.push_back(turnaroundTime);

            for(int j = 0; j < sizeOfQ; j++){
                if(completeQID[i] == processID[j]){
                    waitBurst = burstTime[j];
                    break;
                }
            }

            waitingTime = turnaroundTime - waitBurst;
            waitingTimeQ.push_back(waitingTime);
            //this calculates the turnaround time & waiting time
            //for the ID in index[i] for the completeQID
        }

        //print final results
        int turnTotal = 0;
        int waitTotal = 0;
        int turnAvg = 0;
        int waitAvg = 0;

        for(int i = 0; i < sizeOfQ; i++){
            cout << "\nProcessID: " << completeQID[i] << " | Turnaround Time: " <<
            turnaroundTimeQ[i] << " | Waiting Time: " << waitingTimeQ[i] << "\n";
            turnTotal += turnaroundTimeQ[i];
            waitTotal += waitingTimeQ[i];
        }

        turnAvg = turnTotal / TOTAL_PROCESSES;
        waitAvg = waitTotal / TOTAL_PROCESSES;

        cout << "\n\t||Average Turnaround Time: " << turnAvg << " | Average Wait Time:"
            << waitAvg << "||\n\n";
        }//while end

    return 0;
}

int indexofSmallestElement(deque<int> array, int size){
    int index = 0;

    for(int i = 1; i < size; i++){
        //cout << "Array[i] = " << array[i] << "array[index] = " << array[index] << endl;
            if(array[i] < array[index]){ //if(array[1] = 4 < array[0] = 1)
                index = i;              //index = 1
            }

    }
    return index;
}
