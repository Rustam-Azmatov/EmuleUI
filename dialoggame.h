#ifndef DIALOGGAME_H
#define DIALOGGAME_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QPixmap>

namespace Ui {
class DialogGame;
}

class DialogGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGame(QWidget *parent = 0);
    ~DialogGame();

private slots:
    void on_btnViewImage_clicked();

    void on_leName_textChanged(const QString &arg1);

    void on_leFilePath_textChanged(const QString &arg1);

    void on_btnViewFile_clicked();

private:
    Ui::DialogGame *ui;

    void checkEnabled();
};

#endif // DIALOGGAME_H
