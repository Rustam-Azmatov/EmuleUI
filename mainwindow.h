#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogaddconsole.h"
#include "db/connector.h"
#include "db/daoconsole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAddConsole_clicked();

    void on_cmbConsole_currentIndexChanged(int index);

    void on_btnDelConsole_clicked();

private:
    Ui::MainWindow *ui;
    DAOConsole* daoConsole;
    QVector<Console> listConsole;

    int currentConsoleIndex;
    void loadConsole();
};

#endif // MAINWINDOW_H
