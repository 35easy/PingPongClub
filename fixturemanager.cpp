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

void FixtureManager::EliminationStart(QVector<Player*>& players,int level)
{
    //画图
    eTree=new EliminationTree();
    eTree->init(level);
    eTree->drawTree(players);
    eTree->show();
}

void FixtureManager::GroupStart(QVector<Player*> &players,int groupCount,int groupContain,int winSize)
{
    gList=new GroupList();
    gList->init(groupCount,groupContain,winSize);
    gList->GenerateList(players);
    gList->show();

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
    QVector<Player*> players=DataBase::getInstance().getAllPlayers("player");
    //获得seeds
    QVector<Player*> seeds=DataBase::getInstance().getAllPlayers("seed");
    QVector<Player*> arrange;

    //随机分配
    std::shuffle(players.begin(), players.end(), std::default_random_engine());



    if( ui->radioElimination->isChecked()){
        //计算层数
        int level=1,size=players.size()+seeds.size();
        while (pow(2,level-1)<size) {
            level++;
        }

        //种子选手间隔
        int distance=pow(2,level-1)/seeds.size();
        int i=0,j=0;
        while(i+j<size){
            for(int k=0;k<distance-1;k++){
                if(i+k<players.size())
                    arrange.append(players[i+k]);
            }
            i+=distance-1;
            if(j<seeds.size())
                arrange.append(seeds[j++]);
        }

        EliminationStart(arrange,level);
    }else{
        int groupCount=4,groupContain=5,winSize=2;
        for(auto it:seeds){
            arrange.append(it);
        }
        for(auto it:players){
            arrange.append(it);
        }


        GroupStart(arrange,groupCount,groupContain,winSize);
    }

}
