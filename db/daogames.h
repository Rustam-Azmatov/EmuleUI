#ifndef DAOGAMES_H
#define DAOGAMES_H

#include "connector.h"
#include "game.h"
#include <QVector>
#include <QSqlRecord>
#include <QVariant>
class DAOGames
{

public:
    DAOGames();
    void remove(unsigned id);
    void save(Game* obj);
    void update(Game* obj);

    Game* find(unsigned id);
    QVector<Game> getAll();
private:
    void setValues(QSqlQuery query,Game* obj);
};

#endif // DAOGAMES_H