#ifndef GAME_H
#define GAME_H

#include <QString>

class Game
{
public:
    Game();
    Game(const Game &game);

    Game& operator =(const Game& right);
    bool operator ==(const Game& right);

    QString getPath() const;
    void setPath(const QString &value);

    QString getPathImg() const;
    void setPathImg(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    unsigned int getConsoleId() const;
    void setConsoleId(unsigned int value);

    unsigned int getId() const;
    void setId(unsigned int value);

private:
    unsigned int id;
    unsigned int consoleId;
    QString name;
    QString pathImg;
    QString path;
};

#endif // GAME_H
