#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QCryptographicHash>

class TController : public QObject
{
    Q_OBJECT
public:
    explicit TController(QObject *parent = 0);
    ~TController();

signals:
    void authSuccess();
    void authFail();

public slots:
    void authenticate(const QString &user, const QString &pass);

private:
    QSqlDatabase sdb;

};

#endif // TCONTROLLER_H
