#include "cardclass.h"
#include "fstream"
#include "sstream"

using namespace std;
extern long long MAXID;

Node::Node() {
}

Node::~Node() {

}

void Node::write(string s, int n) {
    stringstream ss;
    ss << s;
    for (int i = 0;ss >>str[i][n] && i < MAX; ++i) {

    }
    ss.clear();
}

void Node::write2(std::string s) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < MAX; ++j) {
            str[j][i] = std::to_string(0);
        }
    }
    stringstream ss;
    ss << s;
    str[0][0] = str[0][1] = str[0][2] = std::to_string(MAXID);
    str[6][0] = str[7][0] = std::to_string(1);
    for (int i = 1; ss >> str[i][0] && i < 4 ; ++i) {

    }
}

int Node::RMAX() {
    return MAX;
}

string Node::currentId() {
    return str[0][0];
}

