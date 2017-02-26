#include "dialogaddconsole.h"
#include "ui_dialogaddconsole.h"

DialogAddConsole::DialogAddConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddConsole)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    console = 0;
}

DialogAddConsole::~DialogAddConsole()
{
    delete ui;    
}

void DialogAddConsole::on_teName_textChanged(const QString &str)
{
    ui->btnOk->setEnabled(!ui->teCmd->text().isEmpty() &&
                          !str.isEmpty());
}

void DialogAddConsole::on_teCmd_textChanged(const QString &str)
{
    ui->btnOk->setEnabled(!ui->teName->text().isEmpty() &&
                          !str.isEmpty());
}

Console *DialogAddConsole::getConsole()
{
    if(!console)
    {
        console = new Console();
        console->setCommand(ui->teCmd->text());
        console->setConsoleName(ui->teName->text());
    }
    return console;
}

void DialogAddConsole::setConsole(Console *value)
{
    console = value;

    ui->teCmd->setText(console->getCommand());
    ui->teName->setText(console->getConsoleName());
}
