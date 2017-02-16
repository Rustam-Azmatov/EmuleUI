#ifndef CONNECTOR_H
#define CONNECTOR_H
#define BASE_NAME "emule.sqlite"
#define BASE_FOLDER ".emuleUI"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDir>

class Connector
{
public:
    QSqlDatabase getDb() const;
    bool connect();
    static Connector* getInstance();
private:
    QSqlDatabase db;
    QString dbName;
    static Connector* instance;
    Connector();
    void createTables();
};

#endif // CONNECTOR_H
