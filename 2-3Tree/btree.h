#ifndef BTREE_H
#define BTREE_H

#include"Result.h"

class Btree {
protected:
    BTNode *root;//根节点

public:
    Btree();//构造函数
    ~Btree();//删除所有节点

    Result* SearchBTree(KeyType K);//查找关键字
    Status InsertBTree(KeyType K);//插入关键字
    Status RemoveBTree(KeyType K);//删除关键字
    BTNode* FindNextNode(BTNode* q,KeyType K,KeyType& nextKey);
    void maintainAfterErase(BTNode *p);
    void mergeNode(BTNode*p1, BTNode*p2, KeyType father_key);
    void DisplayBTree();
    void Display(BTNode *q,int level);
    void Delete(BTNode *q);//删除子树
    BTNode* getRoot();
    int getLevel();//得到b树的高度

    //qt
    QVector<BTNode*>v;
    void Painting(int w, int h);
    void dfs(BTNode *p, int dep,qreal hd,qreal line_d);
};

#endif // BTREE_H
