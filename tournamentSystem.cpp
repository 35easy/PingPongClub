#include "tournamentSystem.h"
#include "ui_tournamentSystem.h"


TournamentSystem::TournamentSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TournamentSystem)
{
    ui->setupUi(this);
    playerManager=NULL;
    fixtureManager=new FixtureManager();
    ui->tabWidget->addTab(fixtureManager,"赛程管理");
    ui->tabWidget->setCurrentWidget(fixtureManager);

    connect(fixtureManager,&FixtureManager::gotoPlayerManager,this,&TournamentSystem::on_btPlayer_clicked);
}

TournamentSystem::~TournamentSystem()
{
    delete ui;
}





void TournamentSystem::on_btPlayer_clicked()
{
//    ui->tabWidget->setCurrentIndex(2);
    //记得在适当时候destroy
    if(playerManager!=NULL){
        return;
        ui->tabWidget->setCurrentWidget(playerManager);

    }
    playerManager=new PlayerManager();
    ui->tabWidget->addTab(playerManager,"参赛选手管理");
    ui->tabWidget->setCurrentWidget(playerManager);
    connect(playerManager,&PlayerManager::gotoFixturemanager,this,&TournamentSystem::on_btFixture_clicked);

}

void TournamentSystem::on_btSeedPlayer_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}


void TournamentSystem::on_btFixture_clicked()
{
    qDebug()<<"导入";
    ui->tabWidget->setCurrentWidget(fixtureManager);

}
