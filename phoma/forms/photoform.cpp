#include "photoform.h"
#include "ui_photoform.h"

PhotoForm::PhotoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoForm)
{
    ui->setupUi(this);
}

PhotoForm::~PhotoForm()
{
    delete ui;
}
