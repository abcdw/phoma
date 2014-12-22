#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QDebug>
#include "photoform.h"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

public slots:
    void showIndex();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
