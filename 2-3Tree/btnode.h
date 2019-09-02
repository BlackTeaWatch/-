#pragma once
#ifndef BTNODE_H
#define BTNODE_H

#include<assert.h>
#include<iostream>
#include<fstream>
#include <algorithm>
#include <QRectF>
#include <QLineF>
#include <QVector>
#include <QQueue>
#include <QString>
#include <QDebug>
#include <QTime>
#include<qpainter.h>
#include <Qt>
#include <QtGlobal>
#include <QMessageBox>
#include <list>
#include <QTime>

using namespace std;
typedef int KeyType;
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFESIBLE -1
#define OVERFLOW -2

#define M 3
#define min_key_num ((M+1)/2-1)
#define max_key_num (M-1)

class BTNode {
public:
    int keynum;//关键字数量
    BTNode *parent;//双亲结点
    KeyType key[M + 1];//关键字数组
    BTNode *ptr[M + 1];//子树数组

    BTNode();
    BTNode* getRightBrother();
    BTNode* getLeftBrother();
    int getPointerPos();
    Status replace(KeyType Key,KeyType newKey);
    Status Erase(KeyType K);
    Status eraseKey(KeyType K);
    Status erasePtr(BTNode* p);
    void updateChild();
    int Search(KeyType x);
    Status Insert(int i, KeyType k, BTNode *aq);
    Status insertKey(int i, KeyType k);
    Status insertChild(int i, BTNode *aq);
    Status Remove(int i);
    bool isLeaf();

    //qt
    QRectF border;
    QLineF line;
};

#endif // BTNODE_H
