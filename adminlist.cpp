#include "adminlist.h"
#include "QMessageBox"
#include "md5.h"
#include "sstream"
#include "QtDebug"

AdminList::AdminList() {
    this->tail = new AdminClass;
    this->head = new AdminClass;
    head->next = tail;
    tail->next = nullptr;
    tail->prev = head;
    head->prev = nullptr;
    len = 0;
    base.open(R"(./data/user.dat)", ios::ate | ios::in | ios::out);
    base.seekg(0, ios::beg);
    base.seekp(0, ios::beg);
    if (!base)
        qDebug() <<"cannot open user.dat";
    else
        this->Read();
    Ptr = head->next;
}

void AdminList::Read() {
    string s;
    stringstream ss;
    if (getline(base, s)) {
        do {
            string u, p;
            ss << s;
            ss >> u >> p;
            this->tail->write(u, p);
            ss.clear();
            s.clear();
            tail->next = new AdminClass;
            AdminClass *Ptr = tail;
            tail = tail->next;
            tail->prev = Ptr;
            tail->next = nullptr;
            len++;
        } while (getline(base, s));
    } else {
        string user = "admin";
        string pwd = "123456";
        this->tail->write(user, md5(pwd));
        AdminClass *Ptr = tail;
        tail = tail->next;
        tail->prev = Ptr;
        tail->next = nullptr;
        len++;
    }
}

bool AdminList::verify(string user, string password) {
    string md5pwd = md5(password);
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
        return false;
    } else {
        while (Ptr->next != nullptr) {
            if (Ptr->Ruser() == user && Ptr->Rpwd() == md5pwd){
                return true;
            }
            Ptr = Ptr->next;
        }
        return false;
    }
}

AdminList::~AdminList() {
    base.close();
    base.open(R"(./data/user.dat)", ios::out | ios::in | ios::trunc);
    AdminClass *temp = this->head->next;
    base.seekp(0, ios::end);
    do {
        base << temp->Ruser() << " " << temp->Rpwd() << endl;
        temp = temp->next;
    } while (temp->next != nullptr);
    base.close();
    delete head;
    delete tail;
    delete temp;
}

void AdminList::add(string user, string password) {
    if (find(user)) {
        string info = "User " + user + " already exists!";
        QMessageBox::warning(NULL, "warning", QString::fromStdString(info),
                                 QMessageBox::Yes);
        return;
    }
    string md5pwd = md5(password);
    this->tail->user = user;
    this->tail->pwd = md5pwd;
    this->tail->next = new AdminClass;
    AdminClass *p = this->tail;
    tail = tail->next;
    tail->prev = p;
    tail->next = nullptr;
    len++;
    string info = "succeed! user " + user + " was added!";
    QMessageBox::information(NULL, "information", QString::fromStdString(info),
                         QMessageBox::Yes);
}

void AdminList::del(string user, string password) {
    string md5pwd = md5(password);
    if (user == "admin") {
        QMessageBox::warning(NULL, "warning", "deleting the reserved word!",
                             QMessageBox::Yes);
        return;
    }
    if (user == Ptr->user) {
        QMessageBox::warning(NULL, "错误！", "无法删除活动中账号！",
                             QMessageBox::Yes);
        return;
    }
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
        return;
    } else {
        AdminClass *temp = head->next;
        while (temp->next != nullptr) {
            if (temp->Ruser() == user && temp->Rpwd() == md5pwd){
                AdminClass *p = temp;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                p->prev = nullptr;
                p->next = nullptr;
                string info = "succeed! user " + user + " was deleted!";
                QMessageBox::information(NULL, "information", QString::fromStdString(info),
                                     QMessageBox::Yes);
                return;
            }
            temp = temp->next;
        }
        string info = "User " + user + " doesn't exists!";
        QMessageBox::information(NULL, "warning", QString::fromStdString(info),
                                 QMessageBox::Yes);
    }
}

bool AdminList::find(string user) {
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
        return false;
    } else {
        AdminClass *temp = head->next;
        while (temp->next != nullptr) {
            if (temp->Ruser() == user){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
}

void AdminList::change(string bPwd, string aPwd) {
    if (this->verify(this->Ptr->Ruser(), bPwd)) {
        this->Ptr->pwd = md5(aPwd);
        QMessageBox::information(NULL, "好耶", "修改成功了！",
                             QMessageBox::Yes);
    } else {
        QMessageBox::warning(NULL, "滴滴！", "密码错误",
                             QMessageBox::Yes);
    }
}
