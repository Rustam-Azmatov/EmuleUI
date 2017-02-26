#ifndef CONSOLE_H
#define CONSOLE_H

#include <QString>
class Console
{
public:
    Console();
    Console(const Console &console);

    Console& operator =(const Console& right);
    bool operator ==(const Console& right);

    unsigned int getId() const;
    void setId(unsigned int value);

    QString getConsoleName() const;
    void setConsoleName(const QString &value);

    QString getCommand() const;
    void setCommand(const QString &value);

private:
    unsigned int id;
    QString consoleName;
    QString command;
};

#endif // CONSOLE_H
