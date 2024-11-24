#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_point_clicked();
    void on_pushButton_plus_clicked();
    void on_pushButton_minus_clicked();
    void on_pushButton_times_clicked();
    void on_pushButton_divided_clicked();
    void on_pushButton_sendResult_clicked();

private:
    Ui::MainWindow *ui;
    double firstNumber;
    double secondNumber;
    QString currentOperation;
    bool isOperationSet;
    QString currentExpression;

    void appendNumber(const QString &number);
    void setOperation(const QString &operation);
    void calculateResult();
};

#endif // MAINWINDOW_H