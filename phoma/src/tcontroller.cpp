#include "tcontroller.h"

TController::TController(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(authFail()), this, SLOT(deleteLater()));

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("db.sqlite3");

    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
        emit authFail();
    }

    qDebug() << "TController created";
}

TController::~TController()
{
    qDebug() << "TController deleted";
}

void TController::authenticate(const QString &user, const QString &pass)
{
    qDebug() << "Trying authenticate...";
    QCryptographicHash md5Generator(QCryptographicHash::Md5);
    md5Generator.addData(pass.toStdString().c_str());
    QString pass_hash(md5Generator.result().toHex());
    qDebug() << pass_hash;

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND pass_hash = :pass");
    query.bindValue(":username", user);
    query.bindValue(":pass", pass_hash);
    query.exec();

    int count = 0;
    while (query.next()) {
        ++count;
        QString username = query.value(1).toString();
        qDebug() << username << " authenticated";
    }

    if (count) {
        emit authSuccess();
    } else {
        emit authFail();
    }
}
