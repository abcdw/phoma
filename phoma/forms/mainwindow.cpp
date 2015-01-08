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
    connect(controller, SIGNAL(showWidget(QWidget *, QString)), this, SLOT(addTab(QWidget*,QString)));
//    login();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTab(QWidget *widget, const QString &label)
{
    ui->tabWidget->addTab(widget, label);
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

    ui->tabWidget->setCurrentIndex(1);
    ui->loginButton->setEnabled(false);
    ui->loginEdit->setEnabled(false);
    ui->passEdit->setEnabled(false);
    ui->logoutButton->setEnabled(true);
}

void MainWindow::authFail()
{
    ui->statusBar->showMessage("Login failed");
}

void MainWindow::logout()
{
    while (ui->tabWidget->count() > 1)
        ui->tabWidget->removeTab(1);

    ui->loginButton->setEnabled(true);
    ui->logoutButton->setEnabled(false);
    ui->loginEdit->setEnabled(true);
    ui->passEdit->setEnabled(true);
    ui->statusBar->showMessage("Logout successful");
}
