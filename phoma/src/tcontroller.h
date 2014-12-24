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
#include <QVector>
#include "tuser.h"
#include "tsection.h"
#include "tphoto.h"
#include "forms/mainpage.h"
#include "forms/photoform.h"

class TController : public QObject
{
    Q_OBJECT
public:
    explicit TController(QObject *parent = 0);
    ~TController();
    void uploadPhoto(const QString &path);
    void getPhotos(QListWidget *list);
    bool isLogged();

signals:
    void authSuccess();
    void authFail();
    void logout();

public slots:
    void authenticate(const QString &user, const QString &pass);
    void deauthenticate();
    void updateSections();
    void updatePhotos(int sectionId);
    void showPhotoWidget(int index);
    void showSectionsWidget();

private:
    bool logged;
    QVector<TPhoto> photos;
    QVector<TSection> sections;
    TUser user;
    MainPage *mainPage;
};

#endif // TCONTROLLER_H
