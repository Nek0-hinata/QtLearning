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

    bool find(string user, string password);

    void add(string user, string password);

    void del(string user, string password);

private:

    fstream base;

    AdminClass *head;

    AdminClass *tail;

    int len;
};

#endif // ADMINLIST_H
