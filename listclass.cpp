#include "listclass.h"
#include "cardclass.h"
#include <fstream>
#include <sstream>
#include <string>
#include <QMessageBox>

using namespace std;
extern long long MAXID;
extern string GetTime();

ListClass::ListClass() {
    head = new Node;
    tail = new Node;
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
    len = 0;
    currentId = -1;
    base.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_base.dat)", ios::ate | ios::in | ios::out);
    base.seekg(0, ios::beg);
    if (!base)
        QMessageBox::warning(NULL, "warning!", "cannot open card_base.dat", QMessageBox::Yes);
    charge.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_charge.dat)", ios::ate | ios::in | ios::out);
    charge.seekg(0, ios::beg);
    if (!charge)
        QMessageBox::warning(NULL, "warning!", "cannot open card_charge.dat", QMessageBox::Yes);
    consume.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_consume.dat)", ios::ate | ios::in | ios::out);
    consume.seekg(0, ios::beg);
    if (!consume)
        QMessageBox::warning(NULL, "warning!", "cannot open card_consume.dat", QMessageBox::Yes);
    this->Read();
    this->resetPtr();
}

void ListClass::Read() {
    string s;
    if (getline(base, s)) {
        do {
            this->tail->write(s, 0);
            s.clear();
            getline(charge, s);
            this->tail->write(s, 1);
            s.clear();
            getline(consume, s);
            this->tail->write(s, 2);
            s.clear();
            tail->next = new Node;
            Node *p = tail;
            tail = tail->next;
            tail->prev = p;
            tail->next = nullptr;
            len++;
        } while (getline(base, s));
    } else {
        this->tail->write("1 teacher ymq NCUT 0 0 1 1", 0);
        this->tail->write("1 0 0 0", 1);
        this->tail->write("1 0 0 0 Beijing ymq", 2);
        tail->next = new Node;
        Node *p = tail;
        tail = tail->next;
        tail->prev = p;
        tail->next = nullptr;
        len++;
    }
}

string ListClass::find(string s, int n) {
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
        return PtrString;
    } else {
        while (Ptr->next != nullptr) {
            if (s == Ptr->str[n][0]) {
                PtrString.clear();
                for (int i = 0; i < Node::RMAX(); ++i) {
                    PtrString += Ptr->str[i][0] + " ";
                }
                QMessageBox::information(NULL, "好耶", "找到了！", QMessageBox::Yes);
                Ptr = Ptr->next;
                return PtrString;
            } else {

            }
            Ptr = Ptr->next;
        }
        QMessageBox::warning(NULL, "糟糕", "已经到世界尽头了:)", QMessageBox::Yes);
        return PtrString;
    }
}

void ListClass::Charge() {

}

void ListClass::input(string s) {
    MAXID++;
    this->tail->write2(s);
    tail->next = new Node;
    Node *p = tail;
    tail = tail->next;
    tail->prev = p;
    tail->next = nullptr;
    len++;
}

ListClass::~ListClass() {
    Node *p = this->head->next;
    base.close();
    charge.close();
    consume.close();
    fstream base1(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_base.dat)", ios::out | ios::in | ios::trunc);
    fstream charge1(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_charge.dat)", ios::out | ios::in | ios::trunc);
    fstream consume1(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_consume.dat)", ios::out | ios::in | ios::trunc);
    base1.seekp(0, ios::end);
    charge1.seekp(0, ios::end);
    consume1.seekp(0, ios::end);
    do{
        for (int i = 0; i < Node::RMAX(); ++i) {
            base1 << " " << p->str[i][0] << " ";
        }
        base1 << endl;
        for (int i = 0; i < Node::RMAX(); ++i) {
            charge1 << " " << p->str[i][1] << " ";
        }
        charge1 << endl;
        for (int i = 0; i < Node::RMAX(); ++i) {
            consume1 << " " << p->str[i][2] << " ";
        }
        consume1 << endl;
        p = p->next;
    }while (p->next != nullptr);
    base1.close();
    charge1.close();
    consume1.close();
    base.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\ID.dat)", ios::in | ios::out | ios::trunc);
    base << MAXID;
    base.close();
    delete head;
    delete tail;
}
