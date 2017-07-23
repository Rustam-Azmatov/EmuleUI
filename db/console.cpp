#include "console.h"

Console::Console()
{
    id = 0;
}

Console::Console(const Console &console)
{
    this->setId(console.getId());
    this->setConsoleName(console.getConsoleName());
    this->setCommand(console.getCommand());
}



Console &Console::operator =(const Console &right)
{
    if(this == &right)
    {
        return *this;
    }

    this->setId(right.getId());
    this->setConsoleName(right.getConsoleName());
    this->setCommand(right.getCommand());

    return *this;
}

bool Console::operator ==(const Console& right)
{
    return id == right.id &&
            consoleName == right.consoleName &&
            command == right.command;
}

unsigned int Console::getId() const
{
    return id;
}

void Console::setId(unsigned int value)
{
    id = value;
}

QString Console::getConsoleName() const
{
    return consoleName;
}

void Console::setConsoleName(const QString &value)
{
    consoleName = value;
}

QString Console::getCommand() const
{
    return command;
}

void Console::setCommand(const QString &value)
{
    command = value;
}
