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
    currentGameIndex = -1;

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
        daoConsole->save(dlgAddConsole->getConsole());

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

    bool canSelectItem = listConsole.size() > 0 &&
            listConsole.size() > currentConsoleIndex;

    if(canSelectItem)
    {
        ui->cmbConsole->setCurrentIndex(currentConsoleIndex);
    }
    else{
        currentConsoleIndex = -1;
        ui->btnDelConsole->setEnabled(false);
        ui->btnAddGame->setEnabled(false);
    }
}

void MainWindow::loadGames()
{
    listGames = daoGame->getAll();

    ui->lstGames->clear();

    foreach (Game game, listGames) {
        ui->lstGames->addItem(game.getName());
    }

    bool canSelectItem = listGames.size() > 0 &&
            listGames.size() > currentGameIndex;

    if(canSelectItem)
    {
        ui->lstGames->setCurrentRow(currentGameIndex);
    }
    else{
        currentGameIndex = -1;
        ui->btnDelGame->setEnabled(false);
        ui->btnEdtGame->setEnabled(false);
    }

}

void MainWindow::on_cmbConsole_currentIndexChanged(int index)
{
    if(currentConsoleIndex != index)
    {
        currentGameIndex = -1;
    }
    loadGames();

    currentConsoleIndex = index;

    ui->btnDelConsole->setEnabled(true);
    ui->btnAddGame->setEnabled(true);
}

void MainWindow::on_btnDelConsole_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle("Удаление");
    msgBox.setText(QString("Удалить настройки консоли %1?")
                   .arg(listConsole[currentConsoleIndex].getConsoleName()));

    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        daoConsole->remove(listConsole[currentConsoleIndex].getId());
        loadConsole();
        loadGames();
    }

}

void MainWindow::on_btnAddGame_clicked()
{
    DialogGame* dlgGame = new DialogGame(listConsole[currentConsoleIndex].getId());

    bool resultDialog = dlgGame->exec();

    Game* game = dlgGame->getGame();

    if(QDialog::Accepted == resultDialog)
    {
        daoGame->save(game);
        loadGames();
    }
    else
    {
        delete game;
    }


    delete dlgGame;
}
