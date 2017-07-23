#include "connector.h"
#include <QDebug>

Connector* Connector::instance = 0;

QSqlDatabase Connector::getDb() const
{
    return db;
}

bool Connector::connect()
{
    bool result = true;
    if(!db.isOpen()){
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);

        result = db.open();
        createTables();
    }

    return result;
}

Connector *Connector::getInstance()
{
    if(!instance)
    {
        instance = new Connector();
    }

    return instance;
}

Connector::Connector()
{
    QDir home(QDir::homePath()+ QDir::separator() + QString(BASE_FOLDER));
    if(!home.exists())
    {
        home.mkdir(home.absolutePath());
    }

    dbName = home.absolutePath();
    dbName += QDir::separator() + QString(BASE_NAME);

}

void Connector::createTables()
{
    QSqlQuery query;
    query.exec("CREATE TABLE CONSOLE("
               "ID INTEGER PRIMARY KEY,"
               "CONSOLE_NAME varchar(128),"
               "COMMAND varchar(512)"
               ")");

    query.exec("CREATE TABLE GAMES("
               "ID INTEGER PRIMARY KEY,"
               "CONSOLE_ID INTEGER,"
               "GAME_NAME varchar(128),"
               "PATH_IMG varchar(512),"
               "PATH varchar(512)"
               ")");
}
