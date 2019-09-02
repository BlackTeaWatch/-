#ifndef RESULT_H
#define RESULT_H
#include"BTNode.h"

class Result {
protected:

public:
    BTNode *pt;//指向找到的结点
    int i;//1...m在结点中关键字序号
    int tag;//1：查找成功 0：查找失败

    Result(BTNode *pt, int i, int tag);
};//B-数的查找结果类型

#endif // RESULT_H
