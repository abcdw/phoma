#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QCryptographicHash>
#include <QListView>
#include <QTableView>
#include <QFileDialog>
#include <QFile>
#include <QListWidget>

class TController : public QObject
{
    Q_OBJECT
public:
    explicit TController(QObject *parent = 0);
    ~TController();
    void updateSectionsTable(QTableView *table);
    void uploadPhoto(const QString &path);
    void getPhotos(QListWidget *list);

signals:
    void authSuccess();
    void authFail();

public slots:
    void authenticate(const QString &user, const QString &pass);

private:
    QSqlDatabase sdb;

};

#endif // TCONTROLLER_H
