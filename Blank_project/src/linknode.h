#ifndef LINKNODE_H
#define LINKNODE_H

#include"iostream"
using namespace std;

class LinkNode
{
public:
    LinkNode(int value);
    ~LinkNode();

private:
    int data;
    LinkNode* next;
};

#endif // LINKNODE_H
