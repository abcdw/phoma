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

QByteArray TController::uploadPhoto(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return QByteArray();

    QByteArray byteArray = file.readAll();
    return byteArray;
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

void TController::authenticate(const QString &name, const QString &pass)
{
    TUser user;
    if (TUser::authenticate(name, pass, user)) {
        emit authSuccess();
        if (user.isAdmin()) {
            RegistrationForm *rf = new RegistrationForm();
            showWidget(rf, "Registration");
            connect(rf, SIGNAL(registerUser(TUser)), this, SLOT(registerUser(TUser)));
            connect(this, SIGNAL(logout()), rf, SLOT(deleteLater()));
        }
        this->user = user;
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
    if (sectionId == -1)
        sectionId = lastSectionId;
    lastSectionId = sectionId;

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
    showWidget(pf, photo.title);
    connect(this, SIGNAL(logout()), pf, SLOT(deleteLater()));
}

void TController::showSectionsWidget()
{
    mainPage = new MainPage();
    showWidget(mainPage, "Sections/Photos");
    connect(mainPage, SIGNAL(updatePhotos(int)), this, SLOT(updatePhotos(int)));
    connect(mainPage, SIGNAL(showPhotoWidget(int)), this, SLOT(showPhotoWidget(int)));
    connect(mainPage, SIGNAL(closedSignal()), this, SLOT(deauthenticate())); // TODO
    connect(mainPage, SIGNAL(addSection()), this, SLOT(addSection()));
    connect(mainPage, SIGNAL(addPhoto()), this, SLOT(addPhoto()));
    connect(this, SIGNAL(logout()), mainPage, SLOT(deleteLater()));
    updateSections();
}

void TController::addSection()
{
    bool ok;
    QString name = QInputDialog::getText(0, tr("Section input"),
                                            tr("Section name:"), QLineEdit::Normal, "", &ok);
    QString description;
    if (ok)
        description = QInputDialog::getText(0, tr("Description input"),
                                            tr("Description:"), QLineEdit::Normal, "", &ok);

    if (ok) {
        TSection section;
        section.name = name;
        section.description = description;
        section.save();
        updateSections();
    }
}

void TController::addPhoto()
{

    bool ok;
    QString title = QInputDialog::getText(0, tr("Title input"),
                                            tr("Photo name:"), QLineEdit::Normal, "", &ok);
    QString description;
    if (ok)
        description = QInputDialog::getText(0, tr("Description input"),
                                            tr("Description:"), QLineEdit::Normal, "", &ok);

    QString fileName;
    if (ok)
        fileName = QFileDialog::getOpenFileName(0, tr("Open Image"));

    if (!fileName.isEmpty()) {
        TPhoto photo;
        photo.title = title;
        photo.description = description;
        photo.owner_id = user.id;
        QPixmap pm;
        pm.loadFromData(uploadPhoto(fileName));
        photo.photo = pm;
        photo.section_id = lastSectionId;
        photo.save();
        qDebug() << "uploaded photo";
        updatePhotos(-1);
    }
}

void TController::registerUser(TUser user)
{
    user.save();
}
