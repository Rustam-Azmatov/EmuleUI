#include "daogames.h"

DAOGames::DAOGames()
{
    Connector::getInstance()->connect();
}

void DAOGames::remove(unsigned id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GAMES WHERE ID = ?");
    query.addBindValue(id);

    query.exec();
}

void DAOGames::save(Game *obj)
{
    QSqlQuery query;
    query.prepare("INSERT INTO GAMES(CONSOLE_ID,GAME_NAME,PATH_IMG,PATH)"
                  " VALUES(?,?,?,?)");

    query.addBindValue(obj->getConsoleId());
    query.addBindValue(obj->getName());
    query.addBindValue(obj->getPathImg());
    query.addBindValue(obj->getPath());

    query.exec();

}

void DAOGames::update(Game *obj)
{
    QSqlQuery query;
    query.prepare("UPDATE GAMES SET "
                  "CONSOLE_ID =?,"
                  "GAME_NAME = ?,"
                  "PATH_IMG = ?,"
                  "PATH = ? "
                  "WHERE ID = ? ");

    query.addBindValue(obj->getConsoleId());
    query.addBindValue(obj->getName());
    query.addBindValue(obj->getPathImg());
    query.addBindValue(obj->getPath());
    query.addBindValue(obj->getId());

    query.exec();
}

Game *DAOGames::find(unsigned id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM GAMES WHERE ID = ?");

    query.addBindValue(id);

    query.exec();

    Game *game = new Game();

    if(query.next())
    {
        this->setValues(query,game);
    }

    return game;

}

QVector<Game> DAOGames::getAll()
{
    QSqlQuery query;
    query.exec("SELECT * FROM GAMES");

    QVector<Game> games;

    while (query.next()) {
        Game game;
        this->setValues(query,&game);
        games.append(game);
    }

    return games;
}

QVector<Game> DAOGames::getAllForConsole(unsigned consoleId)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM GAMES WHERE CONSOLE_ID = ?");
    query.addBindValue(consoleId);

    query.exec();
    QVector<Game> games;

    while (query.next()) {
        Game game;
        this->setValues(query,&game);
        games.append(game);
    }

    return games;
}

void DAOGames::setValues(QSqlQuery query, Game *obj)
{
    unsigned int id = query.value(query.record().indexOf("ID")).toInt();
    unsigned int consoleId = query.value(query.record().indexOf("CONSOLE_ID")).toInt();

    QString gameName = query.value(query.record().indexOf("GAME_NAME")).toString();
    QString pathImg = query.value(query.record().indexOf("PATH_IMG")).toString();
    QString path = query.value(query.record().indexOf("PATH")).toString();

    obj->setId(id);
    obj->setConsoleId(consoleId);
    obj->setName(gameName);
    obj->setPathImg(pathImg);
    obj->setPath(path);

}
