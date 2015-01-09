#ifndef TSECTION_H
#define TSECTION_H

#include <QVector>
#include <QString>
#include <QtSql>

class TSection
{
public:
    TSection();

    static TSection get(int id, bool &exist);
    static TSection getFromQuery(QSqlQuery &query);
    static QVector<TSection> getAll();
    void save();

public:
    int id;
    QString name;
    QString description;
};

#endif // TSECTION_H
