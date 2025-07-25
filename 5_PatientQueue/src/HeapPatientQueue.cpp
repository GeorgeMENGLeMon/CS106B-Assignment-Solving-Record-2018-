// heappatientqueue.cpp
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"

#include<algorithm>
#include<sstream>

HeapPatientQueue::HeapPatientQueue() {
    // TODO: write this constructor
    queueHeap = new pair<string,int> [capacity];
}

HeapPatientQueue::~HeapPatientQueue() {
    // TODO: write this destructor
    delete [] queueHeap;
    queueHeap = nullptr; // 防止悬空指针
    size = 0;
}

void HeapPatientQueue::clear() {
    // TODO: write this function
    delete [] queueHeap;
    queueHeap = nullptr; // 防止悬空指针
    size = 0;
}

string HeapPatientQueue::frontName() {
    // TODO: write this function
    return queueHeap[1].first;
}

int HeapPatientQueue::frontPriority() {
    // TODO: write this function
    return queueHeap[1].second;
}

bool HeapPatientQueue::isEmpty() {
    // TODO: write this function
    if(size) return true;
    else return false;
}

void HeapPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    if(size+1 >= capacity) throw("The size is going to exceed the capacity");

    queueHeap[++size] = {name,priority};
    up(size);
}

string HeapPatientQueue::processPatient() {
    // TODO: write this function
    string name = queueHeap[1].first;
    queueHeap[1] = queueHeap[size--];
    down(1);
    return name;
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    int idx = 0;int priority = 0;
    for(int i = 1 ; i <= size ; i ++) {
        if(queueHeap[i].first == name) {
            if(priority && priority > queueHeap[i].second) {
                priority = queueHeap[i].second;
                idx = i;
            }
            else if(!priority){
                priority = queueHeap[i].second;
                idx = i;
            }
        }
    }

    if(!idx) throw("The given patient is not already in the queue");
    if(priority <= newPriority) throw("The given patient is present in the queue and already has a more urgent priority than the given new priority.");

    queueHeap[idx].second = newPriority;
    up(idx);
}

string HeapPatientQueue::toString() {
    // TODO: write this function
    stringstream buffer;
    buffer << "{";
    for(int i = 1 ; i <= size ; i ++) {
        if(i > 1) buffer << ", ";
        buffer << queueHeap[i].second << ":" << queueHeap[i].first;
    }
    buffer << "}";
    string heapString = buffer.str();
    return heapString;
}

void HeapPatientQueue::up(int u) {
    if((u && queueHeap[u].second < queueHeap[u/2].second)
        || (queueHeap[u].second == queueHeap[u/2].second && queueHeap[u].first < queueHeap[u/2].first)) {
        swap(queueHeap[u],queueHeap[u/2]);
        up(u/2);
    }
}

void HeapPatientQueue::down(int u) {
    int tmp = u;
    if(u*2 <= size && (queueHeap[tmp].second > queueHeap[u*2].second || (queueHeap[tmp].second == queueHeap[u*2].second && queueHeap[tmp].first > queueHeap[u*2].first))) tmp = u*2;
    if(u*2+1 <= size && (queueHeap[tmp].second > queueHeap[u*2+1].second || (queueHeap[tmp].second == queueHeap[u*2+1].second && queueHeap[tmp].first > queueHeap[u*2+1].first))) tmp = u*2+1;

    if(tmp != u) {
        swap(queueHeap[tmp],queueHeap[u]);
        down(tmp);
    }
}
