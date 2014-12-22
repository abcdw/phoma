#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include "src/tcontroller.h"
#include "mainpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
   void login(QString, QString);
   void removeController();

public slots:
   void login();
   void authSuccess();
   void authFail();
   void logout();

private:
    Ui::MainWindow *ui;
    QPointer<TController> controller;
    bool logined;
};

#endif // MAINWINDOW_H
