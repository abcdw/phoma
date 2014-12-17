#include "tcontroller.h"

TController::TController(QObject *parent) :
    QObject(parent)
{
}

void TController::authenticate(const QString &user, const QString &pass)
{
    emit authenticated();
}
