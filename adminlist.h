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

    bool verify(string user, string password);   //用户验证

    void Reset() {Ptr = head->next;}

    bool find(string user);  //用户是否存在

    void add(string user, string password);

    void del(string user, string password);

    void change(string bPwd, string aPwd);

    string getUser() {return Ptr->Ruser();}

    string Operators() {return Ptr->Ruser();}

private:

    fstream base;

    AdminClass *head;

    AdminClass *tail;

    AdminClass *Ptr;

    int len;
};

#endif // ADMINLIST_H
