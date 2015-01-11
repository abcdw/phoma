#ifndef PHOTOFORM_H
#define PHOTOFORM_H

#include <QWidget>
#include "src/tphoto.h"

namespace Ui {
class PhotoForm;
}

class PhotoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoForm(QWidget *parent = 0);
    ~PhotoForm();
    void setPhoto(TPhoto &photo);

signals:
    void updatePhotos();

public slots:
    void deletePhoto();

private:
    Ui::PhotoForm *ui;
    TPhoto photo;
};

#endif // PHOTOFORM_H
