#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QDebug>
#include "src/tcontroller.h"
#include "photoform.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(TController *controller);
    ~MainPage();

public slots:
    void showIndex();

private:
    Ui::MainPage *ui;
    TController *controller;
    void updateSectionsTable();
};

#endif // MAINPAGE_H
