#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);

    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(regUser()));
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::regUser()
{
    TUser user;
    user.username = ui->usernameEdit->text();
    if (user.username.isEmpty())
        return
    user.setPass(ui->passEdit->text());
    user.first_name = ui->firstnameEdit->text();
    user.last_name = ui->lastnameEdit->text();
    user.access_level = ui->accessBox->currentIndex();
    emit registerUser(user);
}
