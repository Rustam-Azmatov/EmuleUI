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

Console *MainWindow::getCurrentConsole()
{
    if(currentConsoleIndex > -1 &&
            currentConsoleIndex < listConsole.size())
    {
        return &(listConsole[currentConsoleIndex]);
    }
    return 0;
}

Game *MainWindow::getCurrentGame()
{
    if(currentGameIndex> -1 &&
            currentGameIndex< listGames.size())
    {
        return &(listGames[currentGameIndex]);
    }
    return 0;
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

    bool canSelectItem = currentConsoleIndex > -1 && listConsole.size() > 0 &&
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
    unsigned consoleId = 0;

    Console* console = getCurrentConsole();

    if(console)
    {
        consoleId = console->getId();
    }

    listGames = daoGame->getAllForConsole(consoleId);

    int tempIndex = currentGameIndex;
    ui->lstGames->clear();

    foreach (Game game, listGames) {
        ui->lstGames->addItem(game.getName());
    }

    currentGameIndex = tempIndex;

    bool canSelectItem = currentGameIndex > -1 && listGames.size() > 0 &&
            listGames.size() > currentGameIndex;

    if(canSelectItem)
    {
        ui->lstGames->setCurrentRow(currentGameIndex);
    }
    else{
        currentGameIndex = -1;

        ui->btnDelGame->setEnabled(false);
        ui->btnEdtGame->setEnabled(false);
        ui->btnStart->setEnabled(false);
        ui->btnEdtGame->setEnabled(false);
    }

}

void MainWindow::on_cmbConsole_currentIndexChanged(int index)
{
    if(currentConsoleIndex != index)
    {
        currentGameIndex = -1;
    }

    currentConsoleIndex = index;

    ui->btnDelConsole->setEnabled(true);
    ui->btnAddGame->setEnabled(true);

    loadGames();
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
    DialogGame* dlgGame = new DialogGame(getCurrentConsole()->getId());

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

void MainWindow::on_lstGames_currentRowChanged(int currentRow)
{
    currentGameIndex = currentRow;

    ui->btnStart->setEnabled(true);
    ui->btnEdtGame->setEnabled(true);
}

void MainWindow::on_btnEdtGame_clicked()
{
    Game* game = getCurrentGame();
    if(game)
    {
        DialogGame* dlgGame = new DialogGame(game);

        if(dlgGame->exec() == QDialog::Accepted)
        {
            game = dlgGame->getGame();
            daoGame->update(game);

            loadGames();
        }

        delete dlgGame;
    }
}
