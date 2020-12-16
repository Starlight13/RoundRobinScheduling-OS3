#include<iostream>
#include <iomanip>
#include <list>
using namespace std;
#define quantum 2



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

struct Node {
    Node* prev;
    Node* next;
    Process* process;
};

class PriorityQueue {
private:
    int size;
    Node* last;
    Node* first;
public:
    PriorityQueue();
    void add(Process* process);
    Process* getFirst();
    Process* deleteFirst();
    int getSize();
    bool isEmpty();
    void display();
    Process* getElement(int index);
};

PriorityQueue::PriorityQueue() {
    this->size = 0;
    this->last = NULL;
    this->first = NULL;
}

void PriorityQueue::add(Process* process){
    Node* node = (Node*)(malloc(sizeof(Node)));
    node->process = process;
    if (size == 0) {
        node->prev = NULL;
        node->next = NULL;
        this->last = node;
        this->first = node;
    } else {
        Node* ourNode = this->first;
        for (int i = 0; i < this->size; i++) {
            if (ourNode->process->priority >= node->process->priority){
                if (ourNode->prev == NULL) {
                    node->prev = NULL;
                    node->next = first;
                    this->first->prev = node;
                    this->first = node;
                    break;
                } else {
                    Node* prevNode = ourNode->prev;
                    prevNode->next = node;
                    node->prev = prevNode;
                    node->next = ourNode;
                    ourNode->prev = node;
                    break;
                }
            } else {
                if (ourNode->next == NULL) {
                    this->last->next = node;
                    node->prev = last;
                    node->next = NULL;
                    this->last = node;
                    break;
                } else {
                    ourNode = ourNode->next;
                }
            }
        }
    }
    size++;
}

Process* PriorityQueue::getFirst() {
    if (size != 0) {
        return first->process;
    } else return NULL;
}

Process* PriorityQueue::deleteFirst() {
    if (size != 0) {
        Process *process = this->first->process;
        this->first = first->next;
        size--;
        return process;
    } else return NULL;
}

int PriorityQueue::getSize() {
    return this->size;
}

bool PriorityQueue::isEmpty() {
    return this->size == 0 ? true : false;
}

Process* PriorityQueue::getElement(int index) {
    if (index >= this->size) return NULL;
    Node* node = first;
    for (int i = 0; i < this->size; i++) {
        if (index == 0) break;
        else {
            index--;
            node = node->next;
        }
    }
    return node->process;
}


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
