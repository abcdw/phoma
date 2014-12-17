#include "tcontroller.h"

TController::TController(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(authFail()), this, SLOT(deleteLater()));
    qDebug() << "TController created";
}

TController::~TController()
{
    qDebug() << "TController deleted";
}

void TController::authenticate(const QString &user, const QString &pass)
{
    emit authSuccess();
}
