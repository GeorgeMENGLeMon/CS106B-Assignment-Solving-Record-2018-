#ifndef LINKEDINTLIST_H
#define LINKEDINTLIST_H

#include"iostream"
using namespace std;

class LinkedIntList
{
public:
    LinkedIntList();  // constructor
    ~LinkedIntList();  // destructor

    // member functions(methods)
    void add(int value);
    void addFront(int value);
    int get(int index) const;
    void insert(int index, int value);
    bool isEmpty() const;
    void removeFront();
    void removeBack();
    void remove(int index);
    int size() const;

    // declared as 'friend' so it can access private front variable
    friend ostream& operator <<(ostream& out, const LinkedIntList& list);

private:


};

#endif // LINKEDINTLIST_H
