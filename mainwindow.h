#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dialogaddconsole.h"
#include "db/connector.h"
#include "db/daoconsole.h"
#include "db/game.h"
#include "db/daogames.h"
#include "dialoggame.h"
#include "gamerunner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Console* getCurrentConsole();
    Game* getCurrentGame();
private slots:
    void on_btnAddConsole_clicked();

    void on_cmbConsole_currentIndexChanged(int index);

    void on_btnDelConsole_clicked();

    void on_btnAddGame_clicked();

    void on_lstGames_currentRowChanged(int currentRow);

    void on_btnEdtGame_clicked();

    void on_btnDelGame_clicked();

    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
    DAOConsole* daoConsole;
    DAOGames* daoGame;

    QVector<Console> listConsole;
    QVector<Game> listGames;

    int currentConsoleIndex;
    int currentGameIndex;

    void loadConsole();
    void loadGames();


};

#endif // MAINWINDOW_H
