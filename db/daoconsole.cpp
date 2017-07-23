#include "daoconsole.h"

DAOConsole::DAOConsole()
{
    Connector::getInstance()->connect();
}

void DAOConsole::remove(unsigned id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CONSOLE WHERE ID = ?");
    query.addBindValue(id);

    query.exec();
}

void DAOConsole::save(Console *obj)
{
    QSqlQuery query;
    query.prepare("INSERT INTO CONSOLE(CONSOLE_NAME,COMMAND) VALUES(?,?)");

    query.addBindValue(obj->getConsoleName());
    query.addBindValue(obj->getCommand());

    query.exec();

    obj->setId(query.lastInsertId().toInt());
}

void DAOConsole::update(Console *obj)
{
    QSqlQuery query;
    query.prepare("UPDATE CONSOLE SET "
                  "CONSOLE_NAME = ?, "
                  "COMMAND = ?, "
                  "WHERE ID = ?");

    query.addBindValue(obj->getConsoleName());
    query.addBindValue(obj->getCommand());
    query.addBindValue(obj->getId());

    query.exec();
}

Console *DAOConsole::find(unsigned id)
{
    Console* console = new Console();

     QSqlQuery query;
     query.prepare("SELECT * FROM CONSOLE WHERE ID = ?");

     query.addBindValue(id);

     query.exec();

     if(query.next())
     {
        setValues(query,console);
     }

    return console;
}

QVector<Console> DAOConsole::getAll()
{
    QVector<Console> listConsole;

    QSqlQuery query;
    query.exec("SELECT * FROM CONSOLE ORDER BY CONSOLE_NAME");

    while (query.next()) {
        Console console;
        setValues(query,&console);
        listConsole.append(console);
    }

    return listConsole;
}

void DAOConsole::setValues(QSqlQuery query, Console *obj)
{
    unsigned int id = query.value(query.record().indexOf("ID")).toInt();
    QString consoleName = query.value(query.record().indexOf("CONSOLE_NAME")).toString();
    QString command = query.value(query.record().indexOf("COMMAND")).toString();

    obj->setId(id);
    obj->setConsoleName(consoleName);
    obj->setCommand(command);
}
