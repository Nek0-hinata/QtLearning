#include "listclass.h"
#include "cardclass.h"
#include <fstream>
#include <sstream>
#include "adminlist.h"
#include <string>
#include <QMessageBox>

using namespace std;
extern long long MAXID;

extern string GetTime();
extern long long CASHID;
extern AdminList AL;

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
        this->tail->write("1 teacher ymq NCUT 0 0 0 0", 0);
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

void ListClass::Use(string s, int kind) {
    stringstream ss(s);
    Node *p = head->next;
    string s1[8];
    for (int i = 0;ss >> s1[i] && i < 8; ++i) {

    }
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
    } else {
        while (p->next != nullptr) {
            if (p->str[0][0] == s1[0]) {
                if (stoi(p->str[kind][0]) >= stoi(s1[3])) {
                    p->str[1][2] = std::to_string(CASHID);
                    p->str[2][2] = GetTime();
                    int i1 = stoi(p->str[3][2]);
                    p->str[3][2] = std::to_string(i1 + stoi(s1[3]));
                    p->str[4][2] = s1[4];
                    p->str[5][2] = s1[5];
                    p->str[kind][0] = std::to_string(stoi(p->str[kind][0]) - stoi(s1[3]));
                    string t = "您已消费 " + s1[3] + "元!";
                    QMessageBox::information(NULL, "oops", QString::fromStdString(t), QMessageBox::Yes);
                    return;
                } else {
                    QMessageBox::warning(NULL, "糟糕", "您没钱了！快去充点吧~", QMessageBox::Yes);
                    return;
                }
            }
            p = p->next;
        }
        QMessageBox::warning(NULL, "糟糕", "找不到您的卡片！", QMessageBox::Yes);
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

//4公交费 5校内金额
void ListClass::Charge(string id, string money, int kinds) {
    Node *p = head->next;
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
    } else {
        while (p->next != nullptr) {
            if (id == p->str[0][1]) {
                int t1 = stoi(p->str[kinds][0]);
                int t2 = stoi(money);
                int t3 = stoi(p->str[1][1]);
                p->str[1][1] = std::to_string(t2+t3);
                p->str[2][1] = GetTime();
                p->str[3][1] = AL.Operators();
                p->str[kinds][0] = std::to_string(t1+t2);
                string t = "成功充值 " + money + "元!";
                QMessageBox::information(NULL, "好耶", QString::fromStdString(t), QMessageBox::Yes);
                return;
            }
            p = p->next;
        }
        QMessageBox::warning(NULL, "糟糕", "找不到您的卡片！", QMessageBox::Yes);
    }
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
    fstream charge1(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_charge.dat)",
                    ios::out | ios::in | ios::trunc);
    fstream consume1(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\card_consume.dat)",
                     ios::out | ios::in | ios::trunc);
    base1.seekp(0, ios::end);
    charge1.seekp(0, ios::end);
    consume1.seekp(0, ios::end);
    do {
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
    } while (p->next != nullptr);
    base1.close();
    charge1.close();
    consume1.close();
    base.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\ID.dat)", ios::in | ios::out | ios::trunc);
    base << MAXID;
    base.close();
    base.open(R"(E:\Program_dev\QtGui\schoolWork\schoolWork1\data\charge.dat)", ios::in | ios::out | ios::trunc);
    base << CASHID;
    base.close();
    delete head;
    delete tail;
}

void ListClass::Change(string id, string user, int kind, string status) {
    Node *p = head->next;
    if (len == 0) {
        QMessageBox::warning(NULL, "warning", "UNKNOWN FAIL",
                             QMessageBox::Yes);
    } else {
        while (p->next != nullptr) {
            if (id == p->str[0][0] && user == p->str[2][0]) {
                if (stoi(p->str[6][0]) || stoi(p->str[7][0])) {
                    string t = "id为 " + p->str[0][0] + " 的用户 " + p->str[2][0] + " 貌似已经离开了我们！ " + status;
                    QMessageBox::warning(NULL, "哦不", QString::fromStdString(t), QMessageBox::Yes);
                    return;
                } else {
                    p->str[kind][0] = status;
                    string t = "id为 " + p->str[0][0] + " 的用户 " + p->str[2][0] + " 已成功将状态切换成了 " + status;
                    QMessageBox::information(NULL, "好耶", QString::fromStdString(t), QMessageBox::Yes);
                    return;
                }
            }
            p = p->next;
        }
        QMessageBox::warning(NULL, "糟糕", "找不到您的卡片！", QMessageBox::Yes);
    }
}
