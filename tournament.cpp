#include "tournament.h"
#include "ui_tournament.h"

Tournament::Tournament(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tournament)
{
    ui->setupUi(this);
}

Tournament::~Tournament()
{
    delete ui;
}

void Tournament::on_btPlayer_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void Tournament::on_btSeedPlayer_clicked()
{
    ui->tabWidget->setCurrentIndex(3);

}

void Tournament::on_btYes_clicked()
{

}

void Tournament::on_btFixture_clicked()
{
    ui->tabWidget->setCurrentIndex(0);

}

