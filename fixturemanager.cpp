#include "fixturemanager.h"
#include "ui_fixturemanager.h"

FixtureManager::FixtureManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixtureManager)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
}

FixtureManager::~FixtureManager()
{
    delete ui;
}

void FixtureManager::on_btCreateFixture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void FixtureManager::on_btImportPlayer_clicked()
{
    emit gotoPlayerManager();
}

void FixtureManager::on_btYes_clicked()
{
    //关闭playermanager

    //获得players
    QVector<Player> players=DataBase::getInstance().getAllPlayers();


    //随机分配
//    std::shuffle(players.begin(), players.end(), std::default_random_engine());

    //画图
    eTree=new EliminationTree();
    eTree->init(5);
    eTree->drawTree(players);
    eTree->show();

}
