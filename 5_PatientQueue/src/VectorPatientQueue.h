// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#pragma once

#include "patientqueue.h"

#include"vector.h"
#include"sstream"
using namespace std;

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    // TODO: add specified member variable(s)
    struct Patients {
        string name;
        int priority;
        int timestamp;

        Patients() :
            name(""),priority(0),timestamp(0) {}

        Patients(string n,int p,int t) :
            name(n),priority(p),timestamp(t) {}
    };
    int time = 0;
    Vector<Patients>* patientQueue;

    // TODO: add any member functions necessary
    int Urgent(int i);
};
