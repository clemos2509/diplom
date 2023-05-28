#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QString>

struct LoginData
{
    QString name;
    QString password;

    bool operator==(const LoginData& LD) const
    {
        return name == LD.name && password == LD.password;
    }
};

class database : public QObject
{
    Q_OBJECT
public:
    database(QObject *parent = nullptr);

    ~database();

    QSqlTableModel* createTableModel(const QString& tableName);

    QStringList getTableNames();

    void getEmployeLoginData(QVector<LoginData>& EmployeLoginData);

signals:

private:
    //
    QSqlDatabase db;

    bool closed = true;
};

#endif // DATABASE_H
