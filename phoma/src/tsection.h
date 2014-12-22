#ifndef TSECTION_H
#define TSECTION_H

#include <QVector>
#include <QString>

class TSection
{
public:
    TSection();

    static TSection get(int id);
    static QVector<TSection> getAll();
    void save();

private:
    int id;
    QString name;
    QString description;
};

#endif // TSECTION_H
