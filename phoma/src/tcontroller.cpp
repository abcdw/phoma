#include "tcontroller.h"

TController::TController(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("db.sqlite3");

    if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
    }

    qDebug("TController created");
    connect(this, SIGNAL(authSuccess()), this, SLOT(showSectionsWidget()));
}

TController::~TController()
{
    qDebug("TController deleted");
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


void TController::deauthenticate()
{

    emit logout();
}

void TController::updateSections()
{
    QPointer<QSqlQueryModel> queryModel = new QSqlQueryModel();
    queryModel->setQuery("SELECT id, name, description FROM sections");
//  queryModel = TSection::getAll();
    mainPage->setSectionTableModel(queryModel);
}

void TController::updatePhotos(int sectionId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM photos WHERE section_id=:sectionId");
    query.bindValue(":sectionId", sectionId);
    query.exec();

    QListWidget *list;
    list = mainPage->getPhotosWidget();
    list->clear();

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

void TController::showPhotoWidget()
{
    PhotoForm *pf = new PhotoForm();
    TPhoto photo;
    QSqlQuery query;
    query.prepare("SELECT * FROM photos WHERE id=:id");
    query.bindValue(":id", 1);
    query.exec();

    while (query.next()) {
        QByteArray image = query.value(6).toByteArray();
        QString name = query.value(2).toString();
        QPixmap pixmap;
        pixmap.loadFromData(image);
        photo.title = name;
        photo.photo = pixmap;
    }

    pf->setPhoto(photo);
    pf->show();
}

void TController::showSectionsWidget()
{
    mainPage = new MainPage();
    mainPage->show();
    connect(mainPage, SIGNAL(updatePhotos(int)), this, SLOT(updatePhotos(int)));
    connect(mainPage, SIGNAL(showPhotoWidget()), this, SLOT(showPhotoWidget()));
    updateSections();
}
