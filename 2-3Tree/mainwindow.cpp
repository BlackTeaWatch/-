#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initSignalSlots(){
    //connect(,SIGNAL(clicked()),this,SLOT(accept()));
}

void MainWindow::initUI(){
    ui->setupUi(this);
    S=QPointF(width(),height());
    demo_rec=QRectF(QPointF(width()*0.05,height()*0.05),QPointF(width()*0.7,height()*0.9));
    //tree = new Btree();  //B树初始化
   // resize(1250, 800);  //窗口初始化
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initUI(); //界面创建与布局
    initSignalSlots(); //信号与槽的关联
    setWindowTitle(tr("B-Tree"));   //窗口标题初始化
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(tree.getRoot())tree.Painting(demo_rec.width(),demo_rec.height());
    QPainter painter(this);
   // painter.setBrush(QBrush(Qt::yellow));
    //painter.drawRect(demo_rec);
    if(!tree.getRoot())return;
    qreal sx=demo_rec.left()+demo_rec.width()*0.02;
    qreal sy=demo_rec.top()+demo_rec.height()*0.02;
    painter.setPen(QPen(Qt::black,2));
    for(BTNode* node:tree.v){
        QRectF rec=node->border.translated(sx,sy);
        painter.drawRect(rec);
        if(node!=tree.getRoot()){
            QLineF line=node->line.translated(sx,sy);
            painter.drawLine(line);
        }
    }
    int fontsize=20-2*(tree.getLevel());
    QFont font("Frutiger LT 45 Light",fontsize,QFont::Bold);
    //设置字体的类型，大小，加粗，斜体
    //font.setLetterSpacing(QFont::AbsoluteSpacing);
    //设置间距
    painter.setFont(font);
    //添加字体
    painter.setPen(QPen(Qt::black, 2));

    for(BTNode* node:tree.v){
        qreal i=0;
        QRectF rec=node->border.translated(sx,sy);
        qreal dx=rec.width()/node->keynum;

        for(int j = 1; j <= node->keynum; j++){
            qreal x = rec.left()+i*dx;
            QRectF text_rec = QRectF(x,rec.top(),dx,rec.height());
            QString text = QString::number(node->key[j],10);
            painter.drawText(text_rec,Qt::AlignCenter,text);
            i+=1;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    QString valString = ui->lineEdit->text();
    if(valString.isEmpty()){
        QMessageBox::information(this,"提示","请输入键值");
        return;
    }
    bool ok;
    int val = valString.toInt(&ok);
    if(!ok){
        QMessageBox::information(this,"提示","请输入数字");
        return;
    }

    ui->lineEdit->clear();
    if(tree.InsertBTree(val)==OK){
        this->update();
        return;
    }
    else{
        QMessageBox::information(this,"提示","键值"+valString+"已存在");
        return;
    }

}

void MainWindow::on_pushButton_2_clicked(){
    QString valString = ui->lineEdit_2->text();
    if(valString.isEmpty()){
        QMessageBox::information(this,"提示","请输入键值");
        return;
    }
    bool ok;
    int val = valString.toInt(&ok);
    if(!ok){
        QMessageBox::information(this,"提示","请输入数字");
        return;
    }

    ui->lineEdit_2->clear();
    if(tree.RemoveBTree(val)==OK){
        this->update();
        return;
    }
    else{
        QMessageBox::information(this,"提示","键值"+valString+"不存在");
        return;
    }
}

void MainWindow::on_pushButton_3_clicked(){
    QString valString = ui->lineEdit_3->text();
    if(valString.isEmpty()){
        QMessageBox::information(this,"提示","请输入键值");
        return;
    }
    bool ok;
    int val = valString.toInt(&ok);
    if(!ok){
        QMessageBox::information(this,"提示","请输入数字");
        return;
    }


//    ui->lineEdit_3->clear();
    Result *res = tree.SearchBTree(val);

    if(res->tag==1){
        QMessageBox::information(this,"提示","键值"+valString+"已存在");
        return;
    }
    else{
        QMessageBox::information(this,"提示","键值"+valString+"不存在");
        return;
    }

}
