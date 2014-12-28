#include "mainpage.h"
#include "ui_mainpage.h"

void MainPage::closeEvent(QCloseEvent * event)
{
    QWidget::closeEvent(event);
    emit closedSignal();
}

MainPage::MainPage() :
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    ui->sectionsTable->hideColumn(0);
    connect(ui->sectionsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(showPhotos(QModelIndex)));
    connect(ui->photosList, SIGNAL(clicked(QModelIndex)), this, SLOT(showPhoto(QModelIndex)));
    connect(ui->addSectionButton, SIGNAL(clicked()), this, SIGNAL(addSection()));
}

MainPage::~MainPage()
{
    delete ui;
}

QTableView *MainPage::getSectionsTable()
{
    return ui->sectionsTable;
}

QListWidget *MainPage::getPhotosWidget()
{
    return ui->photosList;
}

void MainPage::setSectionTableModel(QSqlQueryModel *model)
{
    ui->sectionsTable->setModel(model);
    ui->sectionsTable->adjustSize();
}

void MainPage::showPhoto(QModelIndex index)
{
    emit showPhotoWidget(index.row());
}

void MainPage::showPhotos(QModelIndex index)
{
    QModelIndex new_indx = ui->sectionsTable->model()->index(index.row(), 0, QModelIndex());
    emit updatePhotos(new_indx.data().toInt());
}

//void MainPage::updateSectionsTable()
//{
//}
