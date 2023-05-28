#include "login.h"

login::login(QObject *parent)
    : QObject{parent}
{

}

bool login::Login(LoginData LD)
{
    int count = 0;

    for (int i = 0; i < EmployeLoginData.size(); i++)
    {
        if (EmployeLoginData[i] == LD)
        {
            count += 1;
        }
    }

    return count;
}

QVector<LoginData> login::getEmployeLoginData()
{
    return EmployeLoginData;
}

