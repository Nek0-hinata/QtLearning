#ifndef LISTCLASS_H
#define LISTCLASS_H

#include "cardclass.h"
#include "fstream"

using namespace std;

class ListClass {
public:
    ListClass();

    ~ListClass();

    void add();

    int change(int id);

    Node find(int id);

    void input(string s);  //录入

    void Read();   //获取链表
private:

    fstream base, charge, consume;

    Node *head;

    Node *tail;

    int len;

    int currentId;
};

#endif // LISTCLASS_H
