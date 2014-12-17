#ifndef TCONTROLLER_H
#define TCONTROLLER_H

#include <QObject>

class TController : public QObject
{
    Q_OBJECT
public:
    explicit TController(QObject *parent = 0);

signals:
    void authenticated();

public slots:
    void authenticate(const QString &user, const QString &pass);

};

#endif // TCONTROLLER_H
