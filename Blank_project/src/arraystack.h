#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "string"
#include "iostream"
#include "error.h"
#include "strlib.h"
using namespace std;

class ArrayStack
{
public:
    ArrayStack();
    ~ArrayStack(); // 析构函数 destructor 释放new的内存,防 memory leak
    void push(int n);
    int pop();
    int peek() const;
    bool isEmpty() const;
    string toString() const;

private:
    int* elements;
    int size;
    int capacity;
};

ostream& operator <<(ostream& out, ArrayStack& stack);

#endif // ARRAYSTACK_H
