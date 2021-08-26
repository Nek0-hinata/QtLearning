#ifndef LISTCLASS_H
#define LISTCLASS_H

#include "cardclass.h"
#include "fstream"
#include "vector"

using namespace std;

class ListClass {
public:
    ListClass();

    ~ListClass();

    void Charge();

    int change(int id);

    void resetPtr() {Ptr = head->next;}

    string find(string str, int n);

    void input(string s);  //录入

    void Read();   //获取链表
private:

    fstream base, charge, consume;

    Node *head;

    Node *tail;

    Node *Ptr;

    int len;

    int currentId;

    string PtrString;
};

#endif // LISTCLASS_H
