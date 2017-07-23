#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QPixmap>
#include "db/game.h"

namespace Ui {
class DialogGame;
}

class DialogGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGame(int consoleId, QWidget *parent = 0);
    explicit DialogGame(Game* game, QWidget *parent = 0);
    ~DialogGame();

    Game* getGame() const;
    void setGame(Game* value);

private slots:
    void on_btnViewImage_clicked();

    void on_leName_textChanged(const QString &arg1);

    void on_leFilePath_textChanged(const QString &arg1);

    void on_btnViewFile_clicked();

private:
    Ui::DialogGame *ui;
    Game* game;

    void loadImage(QString pathImg);
    void checkEnabled();
};

#endif // DIALOGGAME_H
