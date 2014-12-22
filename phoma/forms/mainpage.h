#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QDebug>
//#include "src/tcontroller.h"
#include "photoform.h"
#include <QtSql>
#include <QTableView>
#include <QListWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage();
    ~MainPage();
    QTableView *getSectionsTable();
    QListWidget *getPhotosWidget();

public slots:
    void showIndex(QModelIndex indx);
    void setSectionTableModel(QSqlQueryModel *model);

signals:
    void updatePhotos(int);

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
