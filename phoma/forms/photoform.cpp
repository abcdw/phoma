#include "photoform.h"
#include "ui_photoform.h"

PhotoForm::PhotoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoForm)
{
    ui->setupUi(this);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(deleteLater()));
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
    ui->descriptionLabel->setText(photo.description);
    qDebug() << photo.getOwner().id << photo.owner_id;
    ui->ownerNameLabel->setText(photo.getOwner().username);
}
