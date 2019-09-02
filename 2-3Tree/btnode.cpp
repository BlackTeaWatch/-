#include"BTNode.h"


BTNode::BTNode() {
    this->keynum = 0;
    for (int i = 0; i <= M; i++) {
        this->key[i] = 0;
        this->ptr[i] = NULL;
    }
    this->parent = NULL;

}

BTNode* BTNode::getRightBrother() {
    BTNode* right = NULL;
    int i;
    for (i = 0; i <= parent->keynum; i++) {
        if (parent->ptr[i]->key[1] == this->key[1])
            break;
    }
    if (i != parent->keynum) {
        right = parent->ptr[i + 1];
    }
    return right;
}

BTNode* BTNode::getLeftBrother() {
    BTNode* left = NULL;
    int i;
    for (i = 0; i <= parent->keynum; i++) {
        if (parent->ptr[i]->key[1] == this->key[1])
            break;
    }
    if (i != 0) {
        left = parent->ptr[i - 1];
    }
    return left;
}

bool BTNode::isLeaf() {
    return this->ptr[0] == NULL;
}

int BTNode::getPointerPos() {
    int i;
    for (i = 0; i <= parent->keynum; i++) {
        if (parent->ptr[i]->key[1] == this->key[1])
            break;
    }
    return i;
}

Status BTNode::replace(KeyType Key, KeyType newKey) {
    for (int i = 1; i <= this->keynum; i++) {
        if (this->key[i] == Key) {
            this->key[i] = newKey;
            return OK;
        }
    }
    return ERROR;
}

Status BTNode::Erase(KeyType K) {
    int i = this->Search(K);
    if (key[i] != K) {
        return ERROR;
    }
    this->Remove(i);
    return OK;
}


Status BTNode::eraseKey(KeyType K) {
    for (int i = 1; i <= this->keynum; i++) {
        if (this->key[i] == K) {
            for (int j = i; j < this->keynum; j++) {
                this->key[j] = this->key[j + 1];
            }
            this->key[this->keynum] = 0;
            this->keynum--;
            return OK;
        }
    }
    return ERROR;
}

Status BTNode::erasePtr(BTNode* p) {
    for (int i = 0; i <= this->keynum; i++) {
        if (this->ptr[i] == p) {
            for (int j = i; this->ptr[j]; j++) {
                this->ptr[j] = this->ptr[j + 1];
            }
            return OK;
        }
    }
    return ERROR;
}

int BTNode::Search(KeyType x) {
    int i = 0;
    while (i < this->keynum&&x >= this->key[i + 1]) {
        i++;
    }
    return i;
}

Status BTNode::Insert(int i, KeyType k, BTNode *aq) {
    if (i <= 0 || i > keynum + 1) {
        return ERROR;
    }
    for (int j = keynum; j >= i; j--) {
        key[j + 1] = key[j];
        ptr[j + 1] = ptr[j];
    }
    key[i] = k;
    ptr[i] = aq;
    keynum++;
    return OK;
}

Status BTNode::insertKey(int i, KeyType k) {
    if (i <= 0 || i > keynum + 1) {
        return ERROR;
    }
    for (int j = keynum; j >= i; j--) {
        key[j + 1] = key[j];
    }
    key[i] = k;
    keynum++;
    return OK;
}

Status BTNode::insertChild(int i, BTNode *aq) {
    if (i < 0 || i > keynum + 1) {
        return ERROR;
    }
    for (int j = keynum; j >= i; j--) {
        ptr[j + 1] = ptr[j];
    }
    ptr[i] = aq;
    return OK;
}

Status BTNode::Remove(int i) {
    if (i <= 0 || i > keynum) {
        return ERROR;
    }
    for (int j = i; j < keynum; j++) {
        key[i] = key[i + 1];
        ptr[i] = ptr[i + 1];
    }
    key[keynum] = 0;
    ptr[keynum] = NULL;
    keynum--;
    return OK;
}

void BTNode::updateChild() {
    for (int i = 0; i <= keynum; i++) {
        if(ptr[i])
            ptr[i]->parent = this;
    }
}
