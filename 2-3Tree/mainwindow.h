#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Btree.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Btree tree;//B树
    QRectF demo_rec;//显示B树的面板
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent*);
private:
    int change=0;
    Ui::MainWindow *ui;
    void updateRec();
    QPointF S;
    void initSignalSlots();
    void initUI();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
