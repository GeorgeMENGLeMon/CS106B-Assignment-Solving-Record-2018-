// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"

#include"sstream"

LinkedListPatientQueue::LinkedListPatientQueue() {
    // TODO: write this constructor
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    PatientNode* curr = front;
    while(curr != nullptr) {
        PatientNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    front = nullptr;
}

void LinkedListPatientQueue::clear() {
    // TODO: write this function
    PatientNode* curr = front;
    while(curr != nullptr) {
        PatientNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    front = nullptr;
}

string LinkedListPatientQueue::frontName() {
    // TODO: write this function
    return front->name;   // this is only here so it will compile
}

int LinkedListPatientQueue::frontPriority() {
    // TODO: write this function
    return front->priority;   // this is only here so it will compile
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    if(front == nullptr) return true;
    else return false;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    // case 1:
    if(front == nullptr)
        front = new PatientNode(name,priority);

    // case 2:
    else if(priority < front->priority) {
        PatientNode* patient = new PatientNode(name,priority,front);
        front = patient;
    }
    // case 3:
    else
    for(PatientNode* i = front ; i != nullptr ; i = i->next) {
        if(i->next == nullptr || priority < i->next->priority) {
            PatientNode* patient = new PatientNode(name,priority,i->next);
            i->next = patient;
            return;
        }
    }
}

string LinkedListPatientQueue::processPatient() {
    // TODO: write this function
    PatientNode* head = front;
    string name = head->name;
    front = front->next;
    delete head;
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    // case 1:
    if(front == nullptr) throw("The queue is empty.");

    // case 2:
    if(front->name == name) {
        if(newPriority >= front->priority) throw("The given patient is present in the queue and already has a more urgent priority than the given new priority.");
        else {
            front->priority = newPriority;
            return;
        }
    }

    // case 3:
    PatientNode* newPre = nullptr;
    for(PatientNode* i = front ; i->next != nullptr ; i = i->next) {
        if(newPriority < i->next->priority) {
            newPre = i;
            break;
        }
    }

    for(PatientNode* i = front ; i->next != nullptr ; i = i->next) {
        if(name == i->next->name) {
            if(newPriority >= i->next->priority) throw("The given patient is present in the queue and already has a more urgent priority than the given new priority.");
            else {
                i->next->priority = newPriority;
                if(i == newPre) return; // 防止位置不变时产生自环
                PatientNode* tmp = i->next->next;
                i->next->next = newPre->next;
                newPre->next = i->next;
                i->next = tmp;
            }
            return;
        }
    }

    // case 4:
    throw("The given patient is not already in the queue");
}

string LinkedListPatientQueue::toString() {
    // TODO: write this function
    stringstream buffer;
    buffer << "{";
    for(PatientNode* i = front ; i != nullptr ; i = i->next) {
        if(i != front) buffer << ", " ;
        buffer << i->priority << ":" << i->name;
    }
    buffer << "}";

    string queueString = buffer.str();
    return queueString; // this is only here so it will compile
}
