#include "seedmanager.h"
#include "ui_palyermanager.h"

SeedManager::SeedManager(QWidget *parent):PlayerManager(parent)
{
    initUI();
    tableName="seed";

}

void SeedManager::initUI()
{
    //更改界面
    ui->btIsSeed->setText("取消种子选手");
    ui->btAddAPlayer->setText("增加种子选手");
    ui->btFindPlayer->setText("查询种子选手");
    ui->btDeletPlayer->hide();
    ui->btAddFilePlayer->hide();

}


SeedManager::~SeedManager()
{
    delete ui;
}

void SeedManager::initDataBase()
{
    DataBase &DataBase = DataBase::getInstance();
    if(DataBase.initModel(tableName)){
        model=DataBase.seedTabModel;
        ui->tableView->setModel(DataBase.seedTabModel);
        ui->tableView->setSelectionModel(DataBase.seedSelection);
    }
    else{
        qDebug()<<"PlayerModel init failed";
    }
}
