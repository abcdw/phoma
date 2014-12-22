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

void PhotoForm::setPhoto(TPhoto &photo)
{
    ui->nameLabel->setText(photo.title);
    QGraphicsScene *scene = new QGraphicsScene(ui->photoView);
    scene->addPixmap(photo.photo);
    ui->photoView->setScene(scene);
}
