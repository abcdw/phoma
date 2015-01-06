#include "tsection.h"

TSection::TSection()
    : id(-1)
{
}

QVector<TSection> TSection::getAll()
{
    QSqlQuery query("SELECT * FROM sections");
}

void TSection::save()
{
    QSqlQuery query;
    query.prepare("INSERT INTO sections (name, description) \
                              VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.exec();
    id = query.lastInsertId().toInt();
}
