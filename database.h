#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

class database : public QObject
{
    Q_OBJECT
public:
    database(QObject *parent = nullptr);

    ~database();

    QSqlTableModel* createTableModel(const QString& tableName);

    QStringList getTableNames();

signals:

private:
    //
    QSqlDatabase db;

    bool closed = true;
};

#endif // DATABASE_H
