#include "photoform.h"
#include "ui_photoform.h"

PhotoForm::PhotoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoForm)
{
    ui->setupUi(this);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(deleteLater()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deletePhoto()));
}

PhotoForm::~PhotoForm()
{
    delete ui;
}

void PhotoForm::setPhoto(TPhoto &photo)
{
    this->photo = photo;
    ui->nameLabel->setText(photo.title);
    QGraphicsScene *scene = new QGraphicsScene(ui->photoView);
    scene->addPixmap(photo.photo);
    ui->photoView->setScene(scene);
    ui->descriptionLabel->setText(photo.description);
    qDebug() << photo.getOwner().id << photo.owner_id;
    ui->ownerNameLabel->setText(photo.getOwner().username);
}

void PhotoForm::deletePhoto()
{
    photo.removed = 1;
    photo.save();
    emit updatePhotos(-1);
    deleteLater();
}
