#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_clearall_clicked();

    void on_pushButton_equal_clicked();

    void digitClicked();

    void on_pushButton_sign_clicked();

    void operatorClicked();

    void on_pushButton_dot_clicked();



private:

    bool calculate(double operand, QString pendingOperator);
    //终止运算，清除数据，报错
    void abortOperation();
    //连接信号和槽
    void connectSlots();
    //储存运算符
    void setShortcutKeys();//
    //初始化界面
    void initUi();


    QString pendingOperator;
    //储存运算结果
    double result;
    //标记是否等待一个操作数
    bool waitForOperand;



    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
