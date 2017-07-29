#ifndef GAMERUNNER_H
#define GAMERUNNER_H

#include "db/console.h"
#include "db/game.h"
#include <QProcess>
#include <QDebug>

class GameRunner
{
public:

    static runGame(Console* console,Game* game);
};

#endif // GAMERUNNER_H
