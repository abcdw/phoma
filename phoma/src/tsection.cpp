#include "tsection.h"

TSection::TSection()
{
}

QVector<TSection> TSection::getAll()
{
    QSqlQuery query("SELECT * FROM sections");
}
