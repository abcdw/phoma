#ifndef TUSER_H
#define TUSER_H

#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QCryptographicHash>

class TUser
{
public:
    TUser();

    static TUser get(int id);
    static int authenticate(const QString &name, const QString &pass);
    static TUser getFromQuery(QSqlQuery &query);
    void save();

public:
    int id;
    QString username;
    QString pass_hash;
    QString first_name;
    QString last_name;
    int access_level;
};

#endif // TUSER_H
