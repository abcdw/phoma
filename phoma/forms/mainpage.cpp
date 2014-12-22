#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage() :
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    ui->sectionsTable->hideColumn(0);
    connect(ui->sectionsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(showIndex(QModelIndex)));
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
}

void MainPage::showIndex(QModelIndex indx)
{
    QModelIndex new_indx = ui->sectionsTable->model()->index(indx.row(), 0, QModelIndex());
    emit updatePhotos(new_indx.data().toInt());
}

//void MainPage::updateSectionsTable()
//{
//}
