#ifndef PHOTOFORM_H
#define PHOTOFORM_H

#include <QWidget>

namespace Ui {
class PhotoForm;
}

class PhotoForm : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoForm(QWidget *parent = 0);
    ~PhotoForm();

private:
    Ui::PhotoForm *ui;
};

#endif // PHOTOFORM_H
