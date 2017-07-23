#include "game.h"

Game::Game()
{
    id = 0;
}

Game::Game(const Game &game)
{
    this->setConsoleId(game.getConsoleId());
    this->setId(game.getId());
    this->setName(game.getName());
    this->setPath(game.getPath());
    this->setPathImg(game.getPathImg());
}

Game &Game::operator =(const Game &right)
{
    if(this == &right)
    {
        return *this;
    }

    this->setConsoleId(right.getConsoleId());
    this->setId(right.getId());
    this->setName(right.getName());
    this->setPath(right.getPath());
    this->setPathImg(right.getPathImg());
    return *this;
}

bool Game::operator ==(const Game& right)
{
    return id == right.id &&
            consoleId == right.consoleId &&
            name == right.name &&
            path == right.path &&
            pathImg == right.pathImg;
}

QString Game::getPath() const
{
    return path;
}

void Game::setPath(const QString &value)
{
    path = value;
}

QString Game::getPathImg() const
{
    return pathImg;
}

void Game::setPathImg(const QString &value)
{
    pathImg = value;
}

QString Game::getName() const
{
    return name;
}

void Game::setName(const QString &value)
{
    name = value;
}

unsigned int Game::getConsoleId() const
{
    return consoleId;
}

void Game::setConsoleId(unsigned int value)
{
    consoleId = value;
}

unsigned int Game::getId() const
{
    return id;
}

void Game::setId(unsigned int value)
{
    id = value;
}
