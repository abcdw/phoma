#include "tcontroller.h"

TController::TController(QObject *parent) :
    QObject(parent)
{
    connect(this, SIGNAL(authFail()), this, SLOT(deleteLater()));

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
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

void TController::updateSectionsTable(QTableView *table)
{
    QPointer<QSqlQueryModel> queryModel = new QSqlQueryModel;
    queryModel->setQuery("SELECT id, name, description FROM sections");
    table->setModel(queryModel);
}

void TController::uploadPhoto(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray byteArray = file.readAll();

    QSqlQuery query;
    query.prepare("INSERT INTO photos (photo) VALUES (?)");
    query.addBindValue(byteArray);
    query.exec();
}

void TController::getPhotos(QListWidget *list)
{
    QSqlQuery query("SELECT * FROM photos");

    while (query.next()) {
        QListWidgetItem *lwi;
        QByteArray image = query.value(6).toByteArray();
        QString name = query.value(2).toString();
        QPixmap pixmap;
        pixmap.loadFromData(image);
        lwi = new QListWidgetItem(QIcon(pixmap), name);
        list->insertItem(0, lwi);
    }
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
