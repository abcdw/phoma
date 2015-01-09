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
    photo.owner_id = query.value(4).toInt();
    QByteArray image = query.value(6).toByteArray();
    QPixmap pixmap;
    pixmap.loadFromData(image);
    photo.photo = pixmap;
    photo.section_id = query.value(7).toInt();

    return photo;
}

TUser TPhoto::getOwner()
{
    bool exist;
    return TUser::get(owner_id, exist);
}

void TPhoto::save()
{
    QSqlQuery query;
    bool photoExist;
    get(id, photoExist);
    QByteArray img;
    QBuffer buf(&img);
    buf.open(QIODevice::WriteOnly);
    photo.save(&buf, "PNG");

    if (photoExist) {
        query.prepare("UPDATE photos SET title = :title, description = :description, photo = :photo, owner_id = :owner_id, section_id = :section_id WHERE id=:id");
        query.bindValue(":id", id);
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":photo", img);
        query.bindValue(":owner_id", owner_id);
        query.bindValue(":section_id", section_id);
        query.exec();
    } else {
        query.prepare("INSERT INTO photos (title, description, photo, owner_id, section_id) \
                                  VALUES (:title, :description, :photo, :owner_id, :section_id)");
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":photo", img);
        query.bindValue(":owner_id", owner_id);
        query.bindValue(":section_id", section_id);
        query.exec();
        qDebug() << "ok" << query.lastQuery();
        id = query.lastInsertId().toInt();
    }
}
