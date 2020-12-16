# RoundRobinScheduling-OS3
Round Robin is a CPU scheduling algorithm where each process is assigned a fixed time slot in a cyclic way. Time slices (also known as time quanta) are assigned to each process in equal portions and in circular order, handling all processes without priority.

### Main features of the RR algorithm
* simple
* easy to implement
* starvation-free
* preemptive as processes are assigned CPU only for a fixed slice of time at most.

### RR logic
To schedule processes fairly, a round-robin scheduler generally employs time-sharing, giving each job a time slot or quantum[4] (its allowance of CPU time), and interrupting the job if it is not completed by then. The job is resumed next time a time slot is assigned to that process. If the process terminates or changes its state to waiting during its attributed time quantum, the scheduler selects the first process in the ready queue to execute.

### Code
#### class Process
The class Process has a constructor and the folowing fields:\
`int id` - contains process's id\
`int priority` – contains process's priority\
`int burstTime` – contains process's time to execute\
`int burstLeft` – contains how much time is left to full execution\
`int wait` – contains process's time spent waiting for its queue\
`int turnAround` – contains burstTime + waitTime

```c++
class Process{
public:
    Process(int id, int priority, int burstTime);
    int burstTime;
    int burstLeft;
    int wait;
    int turnAround;
    int id;
    int priority;
};

Process::Process(int id, int priority, int burstTime){
    this->id = id;
    this->priority = priority;
    this->burstTime = burstTime;
    this->burstLeft = burstTime;
    this->wait = 0;
    this->turnAround = 0;
}
```

#### class Scheduler
`PriorityQueue procQueue`– a priority queue for processes\
`void findTime()`– method to calculate the waaiting times and turnaround times for processes in a queue\
`void output()` – outputs all the info about processes in a queue\
`void addProcess(Process* proc)` – adds a process to the queue
```c++
class Scheduler{
    
public:
    PriorityQueue procQueue;
    void findTime();
    void output();
    void addProcess(Process* proc);
};

void Scheduler::addProcess(Process* proc){
    procQueue.add(proc);
}

void Scheduler::findTime(){
    int time = 0;
    
    while (true) {
        bool noProcLeft = true;
        PriorityQueue queue = this -> procQueue;
        for (int i = 0; i < queue.getSize(); i++) {
            if(queue.getElement(i)->burstLeft > 0){
                noProcLeft = false;
                if(queue.getElement(i)->burstLeft > quantum){
                    time +=quantum;
                    queue.getElement(i)->burstLeft -= quantum;
                } else{
                    time += queue.getElement(i)->burstLeft;
                    queue.getElement(i)->turnAround = time;
                    queue.getElement(i)->wait = time - queue.getElement(i)->burstTime;
                    queue.getElement(i)->burstLeft = 0;
                }
            }
        }
        if (noProcLeft == true)
            break;
    }
}


void Scheduler::output(){
    int totalWait = 0, totalTurnAround = 0;
    findTime();
    cout << "ProcID"<< setw(10)<< "BurstT" << setw(10) << "WaitT" << setw(15)<< setfill(' ') << "Turn Around\n";
    for (int i = 0; i < this -> procQueue.getSize(); i++){
        cout << this -> procQueue.getElement(i)->id << setw(12) << this -> procQueue.getElement(i)->burstTime <<setw(12) << this -> procQueue.getElement(i)->wait << setw(10) << this -> procQueue.getElement(i)->turnAround <<endl;
        totalWait += this -> procQueue.getElement(i)->wait;
        totalTurnAround = totalTurnAround + this -> procQueue.getElement(i)->turnAround;
    }
    cout << "\nAVG Waiting Time = " << (float)totalWait / (float)procQueue.getSize();
    cout << "\nAverage turn around time = " << (float)totalTurnAround / (float)procQueue.getSize() << '\n';
}
```

### Code execution
```c++
int main(){
    Scheduler dis;
    Process* p1 = new Process(1,2,10);
    Process* p2 = new Process(2,1,5);
    Process* p3 = new Process(3,3,9);
    Process* p4 = new Process(4,3,8);
    Process* p5 = new Process(5,3,7);
    Process* p6 = new Process(6,3,2);
    dis.addProcess(p1);
    dis.addProcess(p2);
    dis.addProcess(p3);
    dis.addProcess(p4);
    dis.addProcess(p5);
    dis.addProcess(p6);
    dis.output();
    return 0;
}
```

##### Result
```
ProcID    BurstT     WaitT   Turn Around
2           5          18        23
1          10          30        40
6           2           4         6
5           7          27        34
4           8          28        36
3           9          32        41

AVG Waiting Time = 23.1667
Average turn around time = 30
```

### Graph showing the wait and turn around time of all processes
![graph](https://github.com/Starlight13/RoundRobinScheduling-OS3/blob/main/graphScheduler.png)

### Pros of using Round Robin Scheduling algorithm
1. There is fairness since every process gets equal share of CPU.
2. The newly created process is added to end of ready queue.
3. A round-robin scheduler generally employs time-sharing, giving each job a time slot or quantum.
4. While performing a round-robin scheduling,a particular time quantum is alloted to different jobs.
5. Each process get a chance to reschedule after a particular quantum time in this scheduling.

### Cons of using Round Robin Scheduling algorithm
1. There is Larger waiting time and Response time.
2. Processor spends time switching context.
3. Time consuming scheduling for small quantums.
4. Decreases comprehension.
5. Its performance heavily depends on time quantum.
