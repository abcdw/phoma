#include "tuser.h"

TUser::TUser()
{
}

TUser TUser::get(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    query.next();

    return getFromQuery(query);
}

int TUser::authenticate(const QString &name, const QString &pass)
{
    qDebug() << "Trying authenticate...";
    QCryptographicHash md5Generator(QCryptographicHash::Md5);
    md5Generator.addData(pass.toStdString().c_str());
    QString pass_hash(md5Generator.result().toHex());
    qDebug() << pass_hash;

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND pass_hash = :pass");
    query.bindValue(":username", name);
    query.bindValue(":pass", pass_hash);
    query.exec();

    int count = 0;
    while (query.next()) {
        ++count;
        QString username = query.value(1).toString();
        qDebug() << username << " authenticated";
    }

    if (count) {
        return 1;
    } else {
        return -1;
    }
}

TUser TUser::getFromQuery(QSqlQuery &query)
{
    TUser user;
    user.id = query.value(0).toInt();
    user.username = query.value(1).toString();
    user.pass_hash = query.value(2).toString();
    user.first_name = query.value(3).toString();
    user.last_name = query.value(4).toString();
    user.access_level = query.value(5).toInt();

    return user;
}

void TUser::save()
{
    QSqlQuery query;
    query.prepare("UPDATE users SET first_name = :first_name, last_name = :last_name, access_level = :access_level WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":first_name", first_name);
    query.bindValue(":last_name", last_name);
    query.bindValue(":access_level", access_level);

    query.exec();
}
