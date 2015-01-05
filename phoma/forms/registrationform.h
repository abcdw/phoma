#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include "src/tuser.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = 0);
    ~RegistrationForm();
signals:
    void registerUser(TUser);

public slots:
    void regUser();

private:
    Ui::RegistrationForm *ui;
};

#endif // REGISTRATIONFORM_H
