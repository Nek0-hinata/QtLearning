#ifndef LISTCLASS_H
#define LISTCLASS_H

#include "cardclass.h"
#include "fstream"

using namespace std;

class ListClass {
public:
    ListClass();

    ~ListClass();

private:
    fstream base, charge, consume;

    void add();

    int change(int n);

    Node find(int id);

    void Read();

    Node *head;

    Node *tail;

    int len;

    int currentId;
};

#endif // LISTCLASS_H
