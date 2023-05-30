#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QSqlTableModel>
#include <QPushButton>
#include <Qstackedwidget.h>

#include "database.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void showTable(QString nameTable);

private:
    Ui::MainWindow *ui;

    database* db;
    QSqlTableModel* model;
    QPushButton* saveButton;
};
#endif // MAINWINDOW_H
