#include "dialoggame.h"
#include "ui_dialoggame.h"

DialogGame::DialogGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGame)
{
    ui->setupUi(this);

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

    QPixmap image(fileName);
    image = image.scaled(ui->lblImagePreVIew->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);


    ui->lblImagePreVIew->setPixmap(image);
}

void DialogGame::checkEnabled()
{
    bool enable = !ui->leName->text().trimmed().isEmpty();

    QString fileName = ui->leFilePath->text();
    QFile rom(fileName);

    enable &= !fileName.trimmed().isEmpty() && rom.exists();

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
