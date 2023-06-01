#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListView>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QTableView>
#include <QHeaderView>
#include <QStyledItemDelegate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new database(nullptr);
    model = new QSqlTableModel();
    saveButton = new QPushButton();

    QStringListModel *modelTablesName = new QStringListModel();

    ui->listTablesName->setModel(modelTablesName);

    modelTablesName->setStringList(db->getTableNames());

    QObject::connect(ui->pushButton_2, &QPushButton::clicked, [=]()
    {
        LoginData LD{ui->lineEdit->text(), ui->lineEdit_2->text()};

        ui->error_msg->setText(0);

        ui->error_msg->setAlignment(Qt::AlignCenter);
        ui->error_msg->setStyleSheet("color: red;");

        if (db->login(LD))
        {
            ui->stackedWidget->setCurrentIndex(1);
        }

        else if (!(LD.name.isEmpty() && LD.password.isEmpty()))
        {
            ui->error_msg->setText(QString("Incorrect username or password"));
        }
    });

    QObject::connect(ui->chose_table, &QPushButton::clicked, [=]()
    {
        QModelIndex currentIndex = ui->listTablesName->currentIndex();
        ui->stackedWidget->setCurrentIndex(2); showTable(currentIndex.data(Qt::DisplayRole).toString());
        ui->table_name->setText(currentIndex.data(Qt::DisplayRole).toString());
    });

    QObject::connect(ui->back, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget->setCurrentIndex(0);
    });

    QObject::connect(ui->back_1, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
    });

    QObject::connect(model, &QSqlTableModel::dataChanged, [](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
    {
        QVariant newData = topLeft.data();

        int row = topLeft.row();
        int column = topLeft.column();

        QSqlTableModel *model = qobject_cast<QSqlTableModel*>(model);
        if (model) {
            QModelIndex primaryKeyIndex = model->index(row, 0);
            int id = model->data(primaryKeyIndex).toInt();
            model->setData(topLeft, newData);
            model->submitAll();
        }
    });
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

