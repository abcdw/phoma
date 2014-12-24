#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(new TController(this))
{
    ui->setupUi(this);
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->logoutButton, SIGNAL(clicked()), controller, SLOT(deauthenticate()));
    connect(ui->actionLogout, SIGNAL(triggered()), controller, SLOT(deauthenticate()));
    connect(this, SIGNAL(login(QString, QString)),
            controller, SLOT(authenticate(QString,QString)));
    connect(controller, SIGNAL(authSuccess()), this, SLOT(authSuccess()));
    connect(controller, SIGNAL(authFail()), this, SLOT(authFail()));
    connect(controller, SIGNAL(logout()), this, SLOT(logout()));
//    login();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::login()
{

    ui->statusBar->showMessage("Authentication in progress...");

//    emit login(ui->loginEdit->text(), ui->passEdit->text());
    emit login("admin", "admin");
}

void MainWindow::authSuccess()
{
    ui->statusBar->showMessage("Login successful");
//    QPointer<MainPage> mainPage = new MainPage(controller);
//    ui->tabWidget->addTab(mainPage, "Main");
    ui->loginButton->setEnabled(false);
    ui->loginEdit->setEnabled(false);
    ui->passEdit->setEnabled(false);
    ui->logoutButton->setEnabled(true);
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::authFail()
{
    ui->statusBar->showMessage("Login failed");
}

void MainWindow::logout()
{
    ui->tabWidget->removeTab(1);
    ui->loginButton->setEnabled(true);
    ui->logoutButton->setEnabled(false);
    ui->loginEdit->setEnabled(true);
    ui->passEdit->setEnabled(true);
    ui->statusBar->showMessage("Logout successful");
}
