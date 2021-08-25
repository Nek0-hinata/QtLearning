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
    base.open("/data/card_base.dat");
    stringstream sss;
    if (!base)
        QMessageBox::warning(NULL, "warning!", "cannot open card_base.dat", QMessageBox::Yes);
    charge.open("/data/card_charge.dat");
    if (!charge)
        QMessageBox::warning(NULL, "warning!", "cannot open card_charge.dat", QMessageBox::Yes);
    consume.open("/data/card_consume.dat");
    if (!consume)
        QMessageBox::warning(NULL, "warning!", "cannot open card_consume.dat", QMessageBox::Yes);
}

void ListClass::Read() {
    string s;
    while (getline(base, s)){
        this->tail->write(s, 1);
        s.clear();
        getline(charge, s);
        this->tail->write(s, 2);
        s.clear();
        getline(consume, s);
        this->tail->write(s, 3);
        s.clear();
        tail->next = new Node;
        Node *p = tail;
        tail = tail->next;
        tail->prev = p;
        tail->next = nullptr;
        len++;
    }
}

Node ListClass::find(int id) {
    if (len == 0){
        QMessageBox::information(NULL, "warning", "list is empty", QMessageBox::Yes);
    }
    if (id > len) {
        QMessageBox::information(NULL, "warning", "out of bounds", QMessageBox::Yes);
    }
    int x = 0;
    Node *p;
    if (id < len/2) {
        p = head->next;
        while (p->next != nullptr && x++ != id){
            p = p->next;
        }
    } else {
        p = tail->prev;
        while (p->prev != nullptr && x++ != id) {
            p = p->next;
        }
    }
    this->currentId = p->currentId;
    return *p;
}
