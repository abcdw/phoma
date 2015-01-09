#ifndef TPHOTO_H
#define TPHOTO_H

#include <QString>
#include <QVector>
#include <QPixmap>
#include <QSqlQuery>
#include <QVariant>
#include <QBuffer>

class TPhoto
{
public:
    TPhoto();

    static TPhoto get(int id, bool &exist);
    static QVector<TPhoto> getPhotos(int sectionId);
    static TPhoto getFromQuery(QSqlQuery &query);
    void save();

//private:
    int id;
    QString filename;
    QString title;
    QString description;
    int owner_id;
    bool removed;
    QPixmap photo;
};

#endif // TPHOTO_H
