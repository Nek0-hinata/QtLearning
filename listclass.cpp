#include "listclass.h"
#include "cardclass.h"
#include <fstream>
#include <sstream>
#include <string>
#include <QMessageBox>

using namespace std;

ListClass::ListClass() {
    head = new Node;
    tail = new Node;
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
    len = 0;
    currentId = -1;
    base.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_base.dat)", ios::ate);
    base.seekg(0, ios::beg);
    if (!base)
        QMessageBox::warning(NULL, "warning!", "cannot open card_base.dat", QMessageBox::Yes);
    charge.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_charge.dat)", ios::ate);
    charge.seekg(0, ios::beg);
    if (!charge)
        QMessageBox::warning(NULL, "warning!", "cannot open card_charge.dat", QMessageBox::Yes);
    consume.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_consume.dat)", ios::ate);
    consume.seekg(0, ios::beg);
    if (!consume)
        QMessageBox::warning(NULL, "warning!", "cannot open card_consume.dat", QMessageBox::Yes);
    this->Read();
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

Node ListClass::find(int id) {
    if (len == 0) {
        QMessageBox::information(NULL, "warning", "list is empty", QMessageBox::Yes);
    }
    if (id > len) {
        QMessageBox::information(NULL, "warning", "out of bounds", QMessageBox::Yes);
    }
    Node *p;
    if (id < len / 2) {
        p = head->next;
        while (p->next != nullptr && stoi(p->currentId()) != id) {
            p = p->next;
        }
    } else {
        p = tail->prev;
        while (p->prev != nullptr && stoi(p->currentId()) != id) {
            p = p->next;
        }
    }
    this->currentId = stoi(p->currentId());
    return *p;
}

void ListClass::WriteToFile(string s) {
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
            base1 << p->str[i][0] << " ";
        }
        base1 << endl;
        for (int i = 0; i < Node::RMAX(); ++i) {
            charge1 << p->str[i][1] << " ";
        }
        charge1 << endl;
        for (int i = 0; i < Node::RMAX(); ++i) {
            consume1 << p->str[i][2] << " ";
        }
        consume1 << endl;
        p = p->next;
    }while (p->next != nullptr);
    base1.close();
    charge1.close();
    consume1.close();
    delete head;
    delete tail;
}
