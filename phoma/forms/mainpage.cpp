#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(TController *controller) :
    controller(controller),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

    connect(controller, SIGNAL(destroyed()), this, SLOT(deleteLater()));
    controller->updateSectionsTable(ui->sectionsTable);
    ui->sectionsTable->hideColumn(0);
    connect(ui->sectionsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(showIndex()));
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::showIndex()
{
    controller->getPhotos(ui->photosList);
//    QListWidgetItem *lwi = new QListWidgetItem(QIcon("test.jpeg"), "test");

//    PhotoForm *pf = new PhotoForm();
//    pf->show();
//    ui->photosList->insertItem(0, lwi);
}

void MainPage::updateSectionsTable()
{
    controller->updateSectionsTable(ui->sectionsTable);
}
