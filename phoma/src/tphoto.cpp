#include "tphoto.h"

TPhoto::TPhoto()
{
}

TPhoto TPhoto::getFromQuery(QSqlQuery &query)
{
    TPhoto photo;
    photo.id = query.value(0).toInt();
    photo.title = query.value(2).toString();
    photo.description = query.value(3).toString();
    QByteArray image = query.value(6).toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(image);
    photo.photo = pixmap;

    return photo;
}

void TPhoto::save()
{

}
