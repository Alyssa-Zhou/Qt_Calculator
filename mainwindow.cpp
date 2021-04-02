#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_result->setText("0");
    result = 0.0;
    waitForOperand = true;

    connectSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//定义运算
bool MainWindow::calculate(double operand, QString pendingOperator)
{
    if(pendingOperator == "+")
    {
        result += operand;
    }
    else if(pendingOperator == "-")
    {
        result -= operand;
    }
    else if(pendingOperator == "*")
    {
        result *= operand;
    }
    else if(pendingOperator == "/")
    {
        if(operand == 0.0)
            return false;
        result /= operand;
    }
    return true;
}

void MainWindow::abortOperation()
{
    result = 0.0;
    pendingOperator.clear();
    ui->lineEdit_result->setText("0");
    waitForOperand = true;
    QMessageBox::warning(this, "运算错误", "除数不能为零");
}

void MainWindow::connectSlots()
{
    QPushButton *digitBtns[10] = {
        ui->pushButton_0,      ui->pushButton_1,          ui->pushButton_2,          ui->pushButton_3,
        ui->pushButton_4,      ui->pushButton_5,          ui->pushButton_6,          ui->pushButton_7,
        ui->pushButton_8,      ui->pushButton_9
    };
    for (auto btn : digitBtns)
        connect(btn, &QPushButton::clicked, this, &MainWindow::digitClicked);

    QPushButton *operatorBtns[4] = {
        ui->pushButton_plus,         ui->pushButton_subtract,     ui->pushButton_multiply,  ui->pushButton_divide,
    };
    for (auto btn : operatorBtns)
        connect(btn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
}

//单击数字键
void MainWindow::digitClicked()
{
    QPushButton *digitBtn = static_cast<QPushButton*>(sender());
    QString value = digitBtn->text();
    if(ui->lineEdit_result->text() == "0" && value == "0")
        return;
    if(waitForOperand)//如果在等待操作数
    {
        ui->lineEdit_result->setText(value);
        waitForOperand = false;
    }
    else//如果已经有操作数 在后面添加
    {
        ui->lineEdit_result->setText(ui->lineEdit_result->text() + value);
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    //将当前显示的数归零
    ui->lineEdit_result->setText("0");
    waitForOperand = true;
}

void MainWindow::on_pushButton_clearall_clicked()
{
    //将当前显示的数据归零，并将之前保存的数据运算清除
    ui->lineEdit_result->setText("0");  //清空显示结果
    waitForOperand = true;              //清空操作数标记
    result = 0.0;                       //清空结果
    pendingOperator.clear();            //清空操作符
}


void MainWindow::on_pushButton_equal_clicked()
{
    double operand = ui->lineEdit_result->text().toDouble();
    if(pendingOperator.isEmpty())
        return;
    if(!calculate(operand, pendingOperator))//?
    {
        abortOperation();
        return;
    }
    ui->lineEdit_result->setText(QString::number(result));
    pendingOperator.clear();
    result = 0.0;
    waitForOperand = true;
}
//设置符号
void MainWindow::on_pushButton_sign_clicked()
{
    QString text = ui->lineEdit_result->text();
    double value = text.toDouble();
    if(value > 0)
    {
        text.prepend('-');//？
    }
    else if(value < 0)
    {
        text.remove(0, 1);//？
    }
    ui->lineEdit_result->setText(text);
}

void MainWindow::operatorClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedBtn->text();
    double operand = ui->lineEdit_result->text().toDouble();
    if(!pendingOperator.isEmpty())
    {
        if(!calculate(operand, pendingOperator))
        {
            abortOperation();
            return;
        }
        ui->lineEdit_result->setText(QString::number(result));
    }
    else
    {
        result = operand;
    }
    pendingOperator = clickedOperator;
    waitForOperand = true;
}


void MainWindow::on_pushButton_dot_clicked()
{
    if (waitForOperand)
        ui->lineEdit_result->setText("0");
    if (!ui->lineEdit_result->text().contains('.'))
        ui->lineEdit_result->setText(ui->lineEdit_result->text() + ".");
    waitForOperand = false;
}
