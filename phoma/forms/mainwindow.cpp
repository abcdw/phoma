#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainPage *mainPage = new MainPage();
    ui->tabWidget->addTab(mainPage, "Main");
}

MainWindow::~MainWindow()
{
    delete ui;
}
