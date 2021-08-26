#include "adminclass.h"
#include "md5.h"

AdminClass::AdminClass()
{

}

void AdminClass::write(string user, string password) {
    this->user = user;
    this->pwd = password;
}
