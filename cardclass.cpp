#include "cardclass.h"
#include "fstream"
#include "sstream"

using namespace std;

Node::Node() {
}

Node::~Node() {

}

void Node::write(string s, int n) {
    stringstream ss;
    ss << s;
    for (int i = 0;ss >>str[i][n] && i < MAX; ++i) {

    }
}

void Node::write2(std::string s) {
    stringstream ss;
    ss << s;
    for (int i = 1; ss >> str[i][0] && i < 4 ; ++i) {

    }
}

int Node::RMAX() {
    return MAX;
}

string Node::currentId() {
    return str[0][0];
}

