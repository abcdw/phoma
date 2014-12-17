#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->logoutButton, SIGNAL(clicked()), this, SLOT(logout()));
    connect(ui->actionLogout, SIGNAL(triggered()), this, SLOT(logout()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete controller;
    delete ui;
}

void MainWindow::login()
{
    ui->statusBar->showMessage("Authentication in progress...");
    logout();

    controller = new TController();
    connect(this, SIGNAL(login(QString, QString)),
            controller, SLOT(authenticate(QString,QString)));
    connect(controller, SIGNAL(authSuccess()), this, SLOT(authSuccess()));
    connect(controller, SIGNAL(authFail()), this, SLOT(authFail()));
    connect(this, SIGNAL(removeController()), controller, SLOT(deleteLater()));

    emit login(ui->loginEdit->text(), ui->passEdit->text());
}

void MainWindow::authSuccess()
{
    ui->statusBar->showMessage("Login successful");
    QPointer<MainPage> mainPage = new MainPage();

    ui->loginButton->setEnabled(false);
    ui->logoutButton->setEnabled(true);
    ui->tabWidget->addTab(mainPage, "Main");
    ui->tabWidget->setCurrentIndex(1);
    logined = true;
}

void MainWindow::authFail()
{
    ui->statusBar->showMessage("Login failed");
    emit removeController();
}

void MainWindow::logout()
{
    if (logined) {
        ui->tabWidget->removeTab(1);
        ui->loginButton->setEnabled(true);
        ui->logoutButton->setEnabled(false);
        emit removeController();
        logined = false;
        ui->statusBar->showMessage("Logout successful");
    }
}
