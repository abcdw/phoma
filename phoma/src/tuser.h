#ifndef TUSER_H
#define TUSER_H

#include <QString>

class TUser
{
public:
    TUser();

    static TUser get(int id);
    static int authenticate(const QString &name, const QString &pass);
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
