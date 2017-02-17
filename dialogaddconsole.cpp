#include "dialogaddconsole.h"
#include "ui_dialogaddconsole.h"

DialogAddConsole::DialogAddConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddConsole)
{
    ui->setupUi(this);
}

DialogAddConsole::~DialogAddConsole()
{
    delete ui;
}
