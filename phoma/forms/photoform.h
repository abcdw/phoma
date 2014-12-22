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

private:
    Ui::PhotoForm *ui;
};

#endif // PHOTOFORM_H
