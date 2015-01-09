#include "tphoto.h"

TPhoto::TPhoto()
    : id(-1)
{
}

TPhoto TPhoto::get(int id, bool &exist)
{
    exist = true;
    QSqlQuery query;
    query.prepare("SELECT * FROM photos WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    if (!query.next()) {
        exist = false;
        return TPhoto();
    }

    return getFromQuery(query);
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
    QSqlQuery query;
    bool photoExist;
    get(id, photoExist);
    QByteArray img;
    QBuffer buf(&img);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "JPG");

    if (photoExist) {
        query.prepare("UPDATE photos SET title = :title, description = :description, photo = :photo WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":photo", img);
        query.exec();
    } else {
        query.prepare("INSERT INTO photos (title, description, photo) \
                                  VALUES (:titile, :description, :photo)");
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":photo", img);
        query.exec();
        id = query.lastInsertId().toInt();
    }
}
