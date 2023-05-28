#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new database(nullptr);
    model = new QSqlTableModel();
    saveButton = new QPushButton();
    ui->comboBox->addItems(db->getTableNames());
    lg = new login(nullptr);

    db->getEmployeLoginData(lg->EmployeLoginData);

    QObject::connect(ui->pushButton_2, &QPushButton::clicked, [=]() { if (lg->Login(LoginData{ui->lineEdit->text(), ui->lineEdit_2->text()})) ui->stackedWidget->setCurrentIndex(1);});
    //QObject::connect(ui->pushButton, &QPushButton::clicked, [=]() {ui->stackedWidget->setCurrentIndex(1); showTable(ui->comboBox->currentText());});
}

MainWindow::~MainWindow()
{
    delete model;

    delete ui;
}

void MainWindow::showTable(QString nameTable)
{
    model = db->createTableModel(nameTable);

    model->select();

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();

    ui->tableView->resizeRowsToContents();
}

