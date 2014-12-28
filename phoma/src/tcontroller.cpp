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

    count = 1;

    if (count) {
        emit authSuccess();
    } else {
        emit authFail();
    }

}


void TController::deauthenticate()
{

    qDebug("TController::deauthenticate()");
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
    photos.erase(photos.begin(), photos.end());

    while (query.next()) {
        QListWidgetItem *lwi;
        photos.push_back(TPhoto::getFromQuery(query));
        TPhoto &photo = photos.back();
        lwi = new QListWidgetItem(QIcon(photo.photo), photo.title);
        list->insertItem(list->count(), lwi);
    }

}

void TController::showPhotoWidget(int index)
{
    PhotoForm *pf = new PhotoForm();
    TPhoto photo;
    QSqlQuery query;
    query.prepare("SELECT * FROM photos WHERE id=:id");
    query.bindValue(":id", photos[index].id);
    query.exec();

    while (query.next()) {
        photo = TPhoto::getFromQuery(query);
    }

    pf->setPhoto(photo);
    pf->show();
    connect(this, SIGNAL(logout()), pf, SLOT(deleteLater()));
}

void TController::showSectionsWidget()
{
    mainPage = new MainPage();
    mainPage->show();
    connect(mainPage, SIGNAL(updatePhotos(int)), this, SLOT(updatePhotos(int)));
    connect(mainPage, SIGNAL(showPhotoWidget(int)), this, SLOT(showPhotoWidget(int)));
    connect(mainPage, SIGNAL(closedSignal()), this, SLOT(deauthenticate())); // TODO
    connect(mainPage, SIGNAL(addSection()), this, SLOT(addSection()));
    connect(this, SIGNAL(logout()), mainPage, SLOT(deleteLater()));
    updateSections();
}

void TController::addSection()
{
//    QMessageBox *mb = new QMessageBox("test", "hello");
    qDebug() << "hello addSection()";
}
