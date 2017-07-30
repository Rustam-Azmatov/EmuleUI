#include "gamerunner.h"

GameRunner::runGame(Console *console, Game *game)
{
    QString command = console->getCommand();

    command = command.replace("{%f}",game->getPath());

    QProcess process;
    process.startDetached(command);
    qDebug() << command;
}
