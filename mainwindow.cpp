#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile styleSheetFile(":/styles.qss");
    if (styleSheetFile.open(QIODevice::ReadOnly)) {
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        qApp->setStyleSheet(styleSheet);
        styleSheetFile.close();
    }

    // Manually connect number buttons
    connect(ui->pushButton_00, &QPushButton::clicked, this, &MainWindow::on_pushButton_0_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_01, &QPushButton::clicked, this, &MainWindow::on_pushButton_1_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_02, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_03, &QPushButton::clicked, this, &MainWindow::on_pushButton_3_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_04, &QPushButton::clicked, this, &MainWindow::on_pushButton_4_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_05, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_06, &QPushButton::clicked, this, &MainWindow::on_pushButton_6_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_07, &QPushButton::clicked, this, &MainWindow::on_pushButton_7_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_08, &QPushButton::clicked, this, &MainWindow::on_pushButton_8_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_09, &QPushButton::clicked, this, &MainWindow::on_pushButton_9_clicked, Qt::UniqueConnection);

    // Manually connect operation buttons
    connect(ui->pushButton_pluss, &QPushButton::clicked, this, &MainWindow::on_pushButton_plus_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_less, &QPushButton::clicked, this, &MainWindow::on_pushButton_minus_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_times, &QPushButton::clicked, this, &MainWindow::on_pushButton_times_clicked, Qt::UniqueConnection);
    connect(ui->pushButton_divided, &QPushButton::clicked, this, &MainWindow::on_pushButton_divided_clicked, Qt::UniqueConnection);

    // Manually connect point button
    connect(ui->pushButton_point, &QPushButton::clicked, this, &MainWindow::on_pushButton_point_clicked, Qt::UniqueConnection);

    // Manually connect result button
    connect(ui->pushButton_sendResult, &QPushButton::clicked, this, &MainWindow::on_pushButton_sendResult_clicked, Qt::UniqueConnection);

    // Initialize variables
    firstNumber = 0.0;
    secondNumber = 0.0;
    currentOperation = "";
    isOperationSet = false;
    currentExpression = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_0_clicked()
{
    appendNumber("0");
}

void MainWindow::on_pushButton_1_clicked()
{
    appendNumber("1");
}

void MainWindow::on_pushButton_2_clicked()
{
    appendNumber("2");
}

void MainWindow::on_pushButton_3_clicked()
{
    appendNumber("3");
}

void MainWindow::on_pushButton_4_clicked()
{
    appendNumber("4");
}

void MainWindow::on_pushButton_5_clicked()
{
    appendNumber("5");
}

void MainWindow::on_pushButton_6_clicked()
{
    appendNumber("6");
}

void MainWindow::on_pushButton_7_clicked()
{
    appendNumber("7");
}

void MainWindow::on_pushButton_8_clicked()
{
    appendNumber("8");
}

void MainWindow::on_pushButton_9_clicked()
{
    appendNumber("9");
}

void MainWindow::on_pushButton_point_clicked()
{
    if (!ui->label->text().contains('.') && !currentOperation.isEmpty()) {
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::on_pushButton_plus_clicked()
{
    setOperation("+");
}

void MainWindow::on_pushButton_minus_clicked()
{
    setOperation("-");
}

void MainWindow::on_pushButton_times_clicked()
{
    setOperation("*");
}

void MainWindow::on_pushButton_divided_clicked()
{
    setOperation("/");
}

void MainWindow::on_pushButton_sendResult_clicked()
{
    calculateResult();
}

void MainWindow::appendNumber(const QString &number)
{
    qDebug() << "Appending number: " << number; // Debug statement
    if (isOperationSet) {
        ui->label->setText(number);
        isOperationSet = false;
    } else {
        if (ui->label->text() == "0" || ui->label->text() == "Error") {
            ui->label->setText(number);
        } else {
            ui->label->setText(ui->label->text() + number);
        }
    }
}

void MainWindow::setOperation(const QString &operation)
{
    qDebug() << "Setting operation: " << operation; // Debug statement
    if (currentOperation.isEmpty()) {
        firstNumber = ui->label->text().toDouble();
        currentOperation = operation;
        currentExpression = QString::number(firstNumber) + operation;
        ui->label->setText(currentExpression);
        isOperationSet = true;
    } else {
        calculateResult();
        currentOperation = operation;
        currentExpression += operation;
        ui->label->setText(currentExpression);
    }
}

void MainWindow::calculateResult()
{
    qDebug() << "Calculating result"; // Debug statement
    if (currentOperation.isEmpty()) {
        return;
    }

    secondNumber = ui->label->text().split(currentOperation).last().toDouble();
    double result = 0.0;

    if (currentOperation == "+") {
        result = firstNumber + secondNumber;
    } else if (currentOperation == "-") {
        result = firstNumber - secondNumber;
    } else if (currentOperation == "*") {
        result = firstNumber * secondNumber;
    } else if (currentOperation == "/") {
        if (secondNumber != 0) {
            result = firstNumber / secondNumber;
        } else {
            ui->label->setText("Error");
            currentOperation = "";
            isOperationSet = false;
            return;
        }
    }

    currentExpression = QString::number(result);
    ui->label->setText(currentExpression);
    firstNumber = result;
    currentOperation = "";
    isOperationSet = false;
}