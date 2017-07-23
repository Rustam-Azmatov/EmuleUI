#include "dialoggame.h"
#include "ui_dialoggame.h"

DialogGame::DialogGame(int consoleId, QWidget *parent) :
    QDialog(parent),    
    ui(new Ui::DialogGame)
{
    ui->setupUi(this);
    game = new Game();
    game->setConsoleId(consoleId);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    checkEnabled();
}

DialogGame::DialogGame(Game* game, QWidget *parent) :
      QDialog(parent),
      ui(new Ui::DialogGame)
{
    ui->setupUi(this);
    this->game = game;

    ui->leName->setText(game->getName());
    ui->leFilePath->setText(game->getPath());
    ui->leImagePath->setText(game->getPathImg());
    loadImage(game->getPathImg());


    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    checkEnabled();
}

DialogGame::~DialogGame()
{
    delete ui;
}

void DialogGame::on_btnViewImage_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выбрать файл обложку",
                                                    QDir::homePath(),"Images (*.jpg *.jpeg *.png *.gif)");

    ui->leImagePath->setText(fileName);

    loadImage(fileName);
}

void DialogGame::checkEnabled()
{
    bool enable = !ui->leName->text().trimmed().isEmpty();

    QString fileName = ui->leFilePath->text();
    QFile rom(fileName);
    QFileInfo infoRom(rom);

    enable &= !fileName.trimmed().isEmpty() && infoRom.exists() && !infoRom.isDir();

    ui->btnOk->setEnabled(enable);
}

void DialogGame::on_leName_textChanged(const QString &arg1)
{
    checkEnabled();
}

void DialogGame::on_leFilePath_textChanged(const QString &arg1)
{
    checkEnabled();
}

void DialogGame::on_btnViewFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Выбрать файл рома",
                                                    QDir::homePath(),"All (*.*)");

    ui->leFilePath->setText(fileName);
}

void DialogGame::loadImage(QString pathImg)
{
    QPixmap image(pathImg);
    image = image.scaled(ui->lblImagePreVIew->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);


    ui->lblImagePreVIew->setPixmap(image);
}

Game* DialogGame::getGame() const
{
    game->setName(ui->leName->text());
    game->setPath(ui->leFilePath->text());
    game->setPathImg(ui->leImagePath->text());

    return game;
}

void DialogGame::setGame(Game* value)
{
    game = value;
}
