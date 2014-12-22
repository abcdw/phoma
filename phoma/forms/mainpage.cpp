#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);

    for (int i = 0; i < 100; ++i) {
        ui->sectionsList->addItem("testsection - testsection description");
    }

    connect(ui->sectionsList, SIGNAL(clicked(QModelIndex)), this, SLOT(showIndex()));
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::showIndex()
{
    qDebug() << ui->sectionsList->currentIndex().row();
    QListWidgetItem *lwi = new QListWidgetItem(QIcon("test.jpeg"), "test");

    PhotoForm *pf = new PhotoForm();
    pf->show();
    ui->photosList->insertItem(0, lwi);
}
