// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
    // TODO: write this constructor
    patientQueue = new Vector<Patients> ();
}

VectorPatientQueue::~VectorPatientQueue() {
    // TODO: write this destructor
    delete patientQueue;
}

void VectorPatientQueue::clear() {
    // TODO: write this function
    patientQueue->clear();
    delete patientQueue;
}

string VectorPatientQueue::frontName() {
    // TODO: write this function
    if(!patientQueue->size())
        throw("The queue does not contain any patients.");

    int idx = 0;
    for(int i = 0 ; i < patientQueue->size() ; i++) idx = Urgent(i);
    string name = patientQueue->get(idx).name;

    return name;   // this is only here so it will compile
}

int VectorPatientQueue::frontPriority() {
    // TODO: write this function
    if(!patientQueue->size())
        throw("The queue does not contain any patients.");

    int idx = 0;
    for(int i = 0 ; i < patientQueue->size() ; i++) idx = Urgent(i);
    int priority = patientQueue->get(idx).priority;

    return priority;   // this is only here so it will compile
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    if(patientQueue->size()) return false;
    else return true;
}

void VectorPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    patientQueue->add({name,priority,++time});
}

string VectorPatientQueue::processPatient() {
    // TODO: write this function
    if(!patientQueue->size())
        throw("The queue does not contain any patients.");

    int idx = 0;
    for(int i = 0 ; i < patientQueue->size() ; i++) idx = Urgent(i);
    string name = patientQueue->get(idx).name;
    patientQueue->remove(idx);

    return name;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    int cnt = 0; int idx = 0;
    for(int i = 0 ; i < patientQueue->size() ; i ++) {
        if(patientQueue->get(i).name == name) {
            if(cnt) {
                idx = Urgent(i);
            }
            else {
                idx = i;
                cnt ++;
            }
        }
    }
    if(!cnt) throw("The given patient is not already in queue.");
    if(patientQueue->get(idx).priority <= newPriority) throw("The given patient already has a more urgent priority.");

    int time = patientQueue->get(idx).timestamp;
    patientQueue->remove(idx);
    patientQueue->add({name,newPriority,time});

}

string VectorPatientQueue::toString() {
    // TODO: write this function
    stringstream ss;
    ss << "{" ;
    for(int i = 0 ; i < patientQueue->size() ; i ++)
        ss << patientQueue->get(i).priority << ":" << patientQueue->get(i).name << ", ";
    ss << "}";
    string queueString = ss.str();
    return queueString; // this is only here so it will compile
}

// add any member functions necessary
int VectorPatientQueue::Urgent(int i) {
    int idx = 0;
    if(patientQueue->get(idx).priority > patientQueue->get(i).priority) {
        idx = i;
    }
    else if(patientQueue->get(idx).priority == patientQueue->get(i).priority) {
        if(patientQueue->get(idx).timestamp > patientQueue->get(i).timestamp) idx = i;
    }
    return idx;
}
