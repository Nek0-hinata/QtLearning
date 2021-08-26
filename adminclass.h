#ifndef ADMINCLASS_H
#define ADMINCLASS_H
#include "string"
using namespace std;

class AdminClass
{
public:
    AdminClass();

    AdminClass *next;
    AdminClass *prev;

    void write(string, string);

    string Ruser(){return user;};
    string Rpwd(){return pwd;};
    string user, pwd;
private:
};

#endif // ADMINCLASS_H
