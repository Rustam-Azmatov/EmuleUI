#ifndef DIALOGADDCONSOLE_H
#define DIALOGADDCONSOLE_H

#include <QDialog>

namespace Ui {
class DialogAddConsole;
}

class DialogAddConsole : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddConsole(QWidget *parent = 0);
    ~DialogAddConsole();

private:
    Ui::DialogAddConsole *ui;
};

#endif // DIALOGADDCONSOLE_H
