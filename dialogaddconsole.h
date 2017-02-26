#ifndef DIALOGADDCONSOLE_H
#define DIALOGADDCONSOLE_H

#include <QDialog>
#include "db/console.h"

namespace Ui {
class DialogAddConsole;
}

class DialogAddConsole : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddConsole(QWidget *parent = 0);
    ~DialogAddConsole();

    Console *getConsole();
    void setConsole(Console *value);

private slots:
    void on_teName_textChanged(const QString &str);

    void on_teCmd_textChanged(const QString &str);

private:
    Ui::DialogAddConsole *ui;
    Console* console;
};

#endif // DIALOGADDCONSOLE_H
