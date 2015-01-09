#include "tsection.h"

TSection::TSection()
    : id(-1)
{
}

TSection TSection::get(int id, bool &exist)
{
    exist = true;
    QSqlQuery query;
    query.prepare("SELECT * FROM sections WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    if (!query.next()) {
        exist = false;
        return TSection();
    }

    return getFromQuery(query);
}

TSection TSection::getFromQuery(QSqlQuery &query)
{
    TSection section;
    section.id = query.value(0).toInt();
    section.name = query.value(1).toString();
    section.description = query.value(2).toString();

    return section;
}

QVector<TSection> TSection::getAll()
{
    QSqlQuery query("SELECT * FROM sections");
    QVector<TSection> sections;

    while(query.next()) {
        sections.push_back(getFromQuery(query));
    }

    return sections;
}

void TSection::save()
{
    QSqlQuery query;
    bool sectionExist;
    get(id, sectionExist);

    if (sectionExist) {
        query.prepare("UPDATE sections SET name = :name, description = :description WHERE id=:id");
        query.bindValue(":name", name);
        query.bindValue(":description", description);
        query.exec();
    } else {
        query.prepare("INSERT INTO sections (name, description) \
                                  VALUES (:name, :description)");
        query.bindValue(":name", name);
        query.bindValue(":description", description);
        query.exec();
        id = query.lastInsertId().toInt();
    }
}
