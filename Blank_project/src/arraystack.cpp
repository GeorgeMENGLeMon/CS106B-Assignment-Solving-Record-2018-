#include "arraystack.h"

ArrayStack::ArrayStack() {
    elements = new int[10]();
    size = 0;
    capacity = 10;
};

ArrayStack::~ArrayStack() {
    cout << "Destructor was called" << endl;
    delete[] elements;
}


void ArrayStack::push(int n) {
    if(size + 1 <= capacity) {
        elements[size] = n;
        size ++;
    }
    else {
        cerr << "Out of Space!" << endl;
    }
}


int ArrayStack::pop() {
    if(size == 0) {
        error("Stack is empty");
    }
    int res = elements[size - 1];
    size --;
    return res;
}

int ArrayStack::peek() const {
    if(!size) {
        error("Stack is empty");
    }
    return elements[size - 1];
}

bool ArrayStack::isEmpty() const {
    return size == 0;
}

string ArrayStack::toString() const {
    string s = "{";
    for(int i = 0 ; i < size ; i ++) {
        s += " " + integerToString(elements[i]);
    }
    s += " }";
    return s;
}

ostream& operator <<(ostream& out, ArrayStack& stack) {
    out << stack.toString();
    return out;
}
