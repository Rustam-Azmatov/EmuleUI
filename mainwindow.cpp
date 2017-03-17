#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    daoConsole = new DAOConsole();

    currentConsoleIndex = -1;
    loadConsole();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddConsole_clicked()
{
    DialogAddConsole* dlgAddConsole = new DialogAddConsole(this);

    if(QDialog::Accepted == dlgAddConsole->exec())
    {
        Console* console = dlgAddConsole->getConsole();

        if(console->getId())
        {
            daoConsole->update(console);
        }
        else
        {
            daoConsole->save(console);
            delete console;
        }

        loadConsole();
    }

    delete dlgAddConsole;
}

void MainWindow::loadConsole()
{
    listConsole = daoConsole->getAll();
    ui->cmbConsole->clear();

    foreach (Console console, listConsole) {
        ui->cmbConsole->addItem(console.getConsoleName());
    }

    if(listConsole.size() > currentConsoleIndex)
    {
        ui->cmbConsole->setCurrentIndex(currentConsoleIndex);
    }
    else{
        currentConsoleIndex = -1;
        ui->btnDelConsole->setEnabled(false);
    }
}

void MainWindow::on_cmbConsole_currentIndexChanged(int index)
{
    currentConsoleIndex = index;
    ui->btnDelConsole->setEnabled(true);
    ui->btnAddGame->setEnabled(true);
}

void MainWindow::on_btnDelConsole_clicked()
{
    daoConsole->remove(listConsole[currentConsoleIndex].getId());
    loadConsole();
}

void MainWindow::on_btnAddGame_clicked()
{
    DialogGame* dlgGame = new DialogGame();

    dlgGame->exec();
    delete dlgGame;
}
