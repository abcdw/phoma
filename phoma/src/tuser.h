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

    static TUser get(int id, bool &exist);
    static bool authenticate(const QString &name, const QString &pass, TUser &user);
    static TUser getFromQuery(QSqlQuery &query);
    bool isAdmin();
    bool isModerator();
    void setPass(const QString &pass);
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
