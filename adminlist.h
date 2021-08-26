#ifndef ADMINLIST_H
#define ADMINLIST_H
#include "adminclass.h"
#include "fstream"

class AdminList
{
public:
    AdminList();
    ~AdminList();

    void Read();

    bool verify(string user, string password);

    void Reset() {Ptr = head->next;}

    bool find(string user);

    void add(string user, string password);

    void del(string user, string password);

private:

    fstream base;

    AdminClass *head;

    AdminClass *tail;

    AdminClass *Ptr;

    int len;
};

#endif // ADMINLIST_H
