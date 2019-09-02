#include"BTree.h"

void Btree::Painting(int w, int h)
{
    if(this->root==NULL)return;
    qreal W=(qreal)w;
    qreal H=(qreal)h;
    QQueue<BTNode*>q;
    v.clear();
    q.enqueue(root);
    while(!q.empty()){
        BTNode* p=q.dequeue();
        if(p->isLeaf()){
            v.push_back(p);
            continue;
        }
        for(int i = 0; i <= p->keynum; i++){
            q.enqueue(p->ptr[i]);
        }
    }
    int ln=v.size();//最底层节点数
    //层数
    int hn= this->getLevel();
    qreal wd=W/ln;
    qreal hd=min(min(H/(2*ln-1),wd/1.5),H/6.0);
    qreal line_d=hn!=1?(H-hd*hn)/(hn-1):0;
    for(int i=0;i<ln;++i){
        qreal left=i*wd;
//        qreal right=left+wd;
        qreal up=(hd+line_d)*(hn-1);
        v[i]->border=QRectF(left+wd*0.1,up,wd*0.8,hd);
    }
    dfs(root,1,hd,line_d);
}

void Btree::dfs(BTNode *p, int dep,qreal hd,qreal line_d)
{
    if(p->isLeaf())return;
    v.push_back(p);
    qreal x=0;
    qreal d=0;
    int n = p->keynum + 1;
    for(int i = 0; i <= p->keynum; i++){
        dfs(p->ptr[i],dep+1,hd,line_d);
        x+=(p->ptr[i]->border.left()+p->ptr[i]->border.right())/2.0;
        d=p->ptr[i]->border.width();
    }
    x/=qreal(n);
    qreal up=(line_d+hd)*(dep-1);
    p->border=QRectF(x-d/2.0,up,d,hd);
    int i=0;
    for(int j = 0; j <= p->keynum; j++){
        qreal xx=(p->ptr[j]->border.left()+p->ptr[j]->border.right())/2.0;
        qreal yy=p->ptr[j]->border.top();
        p->ptr[j]->line=QLineF(xx,yy,p->border.left()+j*(d/p->keynum),p->border.bottom());
        ++i;
    }
}


Btree::Btree() {
    this->root = NULL;
}

Btree::~Btree() {
    Delete(this->root);
}

void Btree::Delete(BTNode *q) {
    if (!q) {
        return;
    }

    for (int i = 0; i <= q->keynum; i++) {
        Delete(q->ptr[i]);
    }
    delete q;
}

BTNode* Btree::FindNextNode(BTNode* p, KeyType K, KeyType& nextKey) {
    if (!p) {
        return NULL;
    }
    int i = p->Search(K);
    assert(p->key[i] == K);
    while (!p->isLeaf()) {
        p = p->ptr[i];
        i = 0;
    }
    nextKey = p->key[i + 1];
    return p;
}

void Btree::maintainAfterErase(BTNode *p) {
    BTNode *pa = p->parent;
    if (p == root) {
        if (p->keynum == 0) {
            root = root->ptr[0];
            if (root) root->parent = NULL;
        }
        return;
    }
    if (p->keynum >= min_key_num)return;
    int ptrPos = p->getPointerPos();
    KeyType father_key = pa->key[ptrPos];
    BTNode* left = p->getLeftBrother();

    if (left)mergeNode(left, p, father_key);//存在左节点则合并左节点
    else {
        BTNode* right = p->getRightBrother();
        father_key = pa->key[ptrPos + 1];
        mergeNode(p, right, father_key);
    }
    this->maintainAfterErase(pa);
}

void Btree::mergeNode(BTNode*p1, BTNode*p2, KeyType father_key) {
    BTNode *pa = p1->parent;
    if (p2->keynum > min_key_num) {
        int replace_key = p2->key[1];
        BTNode *replace_child = p2->ptr[0];
        p2->eraseKey(replace_key);
        p2->erasePtr(replace_child);
        pa->replace(father_key, replace_key);

        p1->Insert(p1->keynum + 1, father_key, replace_child);

        if(replace_child)replace_child->parent = p1;
    }
    else if (p1->keynum > min_key_num) {
        int replace_key = p1->key[p1->keynum];
        BTNode *replace_child = p1->ptr[p1->keynum];
        p1->eraseKey(replace_key);
        p1->erasePtr(replace_child);
        pa->replace(father_key, replace_key);

        p2->insertKey(1, father_key);
        p2->insertChild(0, replace_child);

        if(replace_child)replace_child->parent = p2;
    }
    else {
        pa->eraseKey(father_key);
        pa->erasePtr(p2);
        p1->Insert(p1->keynum + 1, father_key, p2->ptr[0]);
        for (int i = 1; i <= p2->keynum; i++) {
            p1->Insert(p1->keynum + 1, p2->key[i], p2->ptr[i]);
        }
        p1->updateChild();
        pa->updateChild();
        delete p2;
    }
}

Result* Btree::SearchBTree(KeyType K) {
    BTNode* p = this->root;
    BTNode* q = NULL;
    int found = FALSE;
    int i = 0;
    while (p && !found) {
        i = p->Search(K);
        if (i > 0 && p->key[i] == K) {
            found = true;
        }
        else {
            q = p;
            p = p->ptr[i];
        }
    }
    if (found) return new Result(p, i, 1);
    else return new Result(q, i, 0);
}

Status Btree::InsertBTree(KeyType K) {
    Result* res = SearchBTree(K);
    if (res->tag == 1) {//树中已有该值
        return ERROR;
    }
    KeyType x = K;
    BTNode *ap = NULL;
    BTNode *q = res->pt;
    int finished = FALSE;
    int i = res->i;
    while (q && !finished) {
        q->Insert(i + 1, x, ap);
        if (q->keynum < M)
            finished = true;
        else {
            const int s = (M + 1) / 2;//取结点中间
            ap = new BTNode();//将q->key[s+1...M],q->ptr[s..M]和q->recptr[s+1...M]移入新结点*ap
            for (int j = s + 1; j <= M; j++) {
                ap->key[j - s] = q->key[j];
                ap->ptr[j - s] = q->ptr[j];
            }
            ap->ptr[0] = q->ptr[s];
            ap->keynum = M - s;
            ap->parent = q->parent;
            ap->updateChild();

            q->keynum = s - 1;
            x = q->key[s];
            for (int j = s; j <= M; j++) {
                q->key[j] = 0;
                q->ptr[j] = NULL;
            }
            q = q->parent;
            if (q) {
                i = q->Search(x);
            }
        }
    }

    delete res;

    if (!finished) {
        BTNode *newRoot = new BTNode();
        newRoot->key[1] = x;
        newRoot->ptr[1] = ap;
        newRoot->ptr[0] = this->root;

        if (ap)ap->parent = newRoot;
        if (this->root)this->root->parent = newRoot;

        this->root = newRoot;
        this->root->keynum = 1;
    }
    return OK;
}

Status Btree::RemoveBTree(KeyType K) {
    Result* res = SearchBTree(K);
    if (res->tag == 0) {//树中没有该值
        return ERROR;
    }
    BTNode *p = res->pt;


    if (!p->isLeaf()) {
        KeyType nextKey;
        BTNode* nextNode = FindNextNode(p, K, nextKey);
        assert(p->replace(K, nextKey) == OK);
        K = nextKey;
        p = nextNode;
    }
    assert(p->Erase(K) == OK);

    this->maintainAfterErase(p);

    return OK;
}

void Btree::DisplayBTree() {
    Display(root, 0);
}

void Btree::Display(BTNode *q, int level) {
    if (!q) {//如果是空树
        return;
    }
    for (int i = 0; i <= q->keynum; i++) {
        Display(q->ptr[i], level + 1);
    }
    cout << endl;
    for (int i = 0; i < level; i++) {
        cout << "         ";
    }
    for (int i = 1; i <= q->keynum; i++) {
        cout << q->key[i] << ' ';
    }
}

int Btree::getLevel() {
    BTNode *p = root;
    int i;
    for (i = 0;p; i++) {
        p = p->ptr[0];
    }
    return i;
}

BTNode* Btree::getRoot(){
    return this->root;
}
