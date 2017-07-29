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

    listGames = daoGame->getGamesByNameForConsole(consoleId,ui->leSearchGame->text());

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

        ui->lblImg->setPixmap(QPixmap());
        ui->lblTitle->setText("");
    }

}

void MainWindow::loadImage(QString fileName)
{
    if(!fileName.isEmpty())
    {
        QPixmap image(fileName);
        image = image.scaled(ui->lblImg->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);

        ui->lblImg->setPixmap(image);
    }
    else{
        ui->lblImg->setPixmap(QPixmap());
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
    Console* console = getCurrentConsole();

    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(tr("Удаление"));
    msgBox.setText(QString(tr("Удалить настройки консоли %1? Список игр пропадет."))
                   .arg(console->getConsoleName()));

    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        daoConsole->remove(console->getId());
        daoGame->removeInConsole(console->getId());

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

    if(getCurrentGame())
    {
        ui->btnStart->setEnabled(true);
        ui->btnEdtGame->setEnabled(true);
        ui->btnDelGame->setEnabled(true);

        ui->lblTitle->setText(getCurrentGame()->getName());
        loadImage(getCurrentGame()->getPathImg());
    }
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

void MainWindow::on_btnDelGame_clicked()
{
    Game* game = getCurrentGame();

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(tr("Удаление"));
    msgBox.setText(QString(tr("Удалить игру %1 из списка?"))
                   .arg(game->getName()));

    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        daoGame->remove(game->getId());

        loadGames();
    }
}

void MainWindow::on_btnStart_clicked()
{
    GameRunner::runGame(getCurrentConsole(),getCurrentGame());
}

void MainWindow::on_leSearchGame_textChanged(const QString &arg1)
{
    loadGames();
}
