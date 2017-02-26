#ifndef DAOCONSOLE_H
#define DAOCONSOLE_H

#include "console.h"
#include "connector.h"
#include <QVector>
#include <QSqlRecord>
#include <QVariant>

class DAOConsole
{
public:
    DAOConsole();
    void remove(unsigned id);
    void save(Console* obj);
    void update(Console* obj);

    Console* find(unsigned id);
    QVector<Console> getAll();
private:
    void setValues(QSqlQuery query,Console* obj);
};

#endif // DAOCONSOLE_H
