#ifndef CARDCLASS_H
#define CARDCLASS_H

#include "sstream"

class Node {
private:

    static const int MAX = 8;
public:
    Node();

    ~Node();

    Node *next;

    Node *prev;

    void write(std::string s, int n);   //写入自身存储区域

    std::string currentId();

    void write2(std::string s);

    static int RMAX();

    std::string str[MAX][3];
    //一卡通编号、种类（教工卡、学生卡、其它卡、临时卡）   基本信息
    // 、姓名、单位、公交费金额、校内金额、挂失（1表示正常，0表示挂失，此内容选做），
    // 有效性等信息。
    //一卡通编号、充值金额、充值日期、操作员等    充值管理
    //消费编号、一卡通编号、消费日期、消费金额、消费地点、消费人员等  消费管理



};

#endif // CARDCLASS_H
