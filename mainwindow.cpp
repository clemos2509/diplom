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

    QObject::connect(ui->pushButton_2, &QPushButton::clicked, [=]()
    {
        LoginData LD{ui->lineEdit->text(), ui->lineEdit_2->text()};

        if (db->login(LD))
        {
            ui->stackedWidget->setCurrentIndex(1);
        }

    });


    QObject::connect(ui->pushButton, &QPushButton::clicked, [=]() {ui->stackedWidget->setCurrentIndex(2); showTable(ui->comboBox->currentText());});
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

