#include "tournamentSystem.h"
#include "ui_tournamentSystem.h"


TournamentSystem::TournamentSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TournamentSystem)
{
    ui->setupUi(this);
    playerManager=NULL;

}

TournamentSystem::~TournamentSystem()
{
    delete ui;
}



void TournamentSystem::on_btCreateFixture_clicked()
{
    ui->tabWidget->setCurrentIndex(1);


}


void TournamentSystem::on_btPlayer_clicked()
{
//    ui->tabWidget->setCurrentIndex(2);
    //记得在适当时候destroy
    if(playerManager!=NULL)
        return;
    playerManager=new PlayerManager();
    ui->tabWidget->addTab(playerManager,"参赛选手管理");
    ui->tabWidget->setCurrentWidget(playerManager);
}

void TournamentSystem::on_btSeedPlayer_clicked()
{
    ui->tabWidget->setCurrentIndex(3);

}

void TournamentSystem::on_btYes_clicked()
{
}

void TournamentSystem::on_btFixture_clicked()
{
    ui->tabWidget->setCurrentIndex(0);

}

