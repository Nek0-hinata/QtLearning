#include "adminlist.h"
#include "QMessageBox"
#include "md5.h"
#include "sstream"

AdminList::AdminList()
{
    this->tail = new AdminClass;
    this->head = new AdminClass;
    head->next = tail;
    tail->next = nullptr;
    tail->prev = head;
    head->prev = nullptr;
    len = 0;
    base.open("/data/user.dat", ios::ate);
    base.seekg(0, ios::beg);
    if (!base)
        QMessageBox::warning(NULL, "warning!", "cannot open card_base.dat", QMessageBox::Yes);
    this->Read();
}

void AdminList::Read() {
    string s;
    stringstream ss;
    while (getline(base, s)) {
        string u, p;
        ss << s;
        ss >> u >> p;
        this->tail->write(u, p);
        ss.clear();
        tail->next = new AdminClass;
        AdminClass *Ptr = tail;
        tail = tail->next;
        tail->prev = Ptr;
        tail->next = nullptr;
        len++;
    }
    if (len == 0) {
        string user = "Admin";
        string pwd = "123456";
        this->tail->write(user, pwd);
        AdminClass *Ptr = tail;
        tail = tail->next;
        tail->prev = Ptr;
        tail->next = nullptr;
        len++;
    }
}

bool AdminList::find(string user, string password) {
    string md5pwd = md5(password);
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
        return false;
    } else {
        AdminClass *temp = head->next;
        while (temp->next != nullptr && temp->Ruser() != user && temp->Rpwd() != md5pwd) {
            temp = temp->next;
            return true;
        }
        return false;
    }
}

AdminList::~AdminList() {
    base.close();
    base.open("user.dat", ios::out);
    AdminClass *temp = this->head->next;
    while (temp->next != nullptr) {
        base.seekp(0, ios::end);
        base << temp->Ruser() << " " << temp->Rpwd() << endl;
        temp = temp->next;
    }
    base.close();
    delete head;
    delete tail;
    delete temp;
}

void AdminList::add(string user, string password) {
    string md5pwd = md5(password);
    this->tail->user = user;
    this->tail->pwd = md5pwd;
    this->tail->next = new AdminClass;
    AdminClass *p = this->tail;
    tail = tail->next;
    tail->prev = p;
    tail->next = nullptr;
    len++;
}
