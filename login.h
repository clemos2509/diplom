#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QtSql>
#include <QString>

#include "database.h"


class login : public QObject
{
    Q_OBJECT
public:
    explicit login(QObject *parent = nullptr);

    bool Login(LoginData LD);

    QVector<LoginData> getEmployeLoginData();

signals:


public:

    QVector<LoginData> EmployeLoginData;
};

#endif // LOGIN_H
