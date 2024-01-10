
#include "playermanager.h"
#include "ui_palyermanager.h"
PlayerManager::PlayerManager(QWidget *parent)
    :   QWidget(parent),
 ui(new Ui::PlayerManager)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);          //不可修改
    ui->tableView->setAlternatingRowColors(true);

    DataBase &DataBase = DataBase::getInstance();
    if(DataBase.initPlayerModel()){
        ui->tableView->setModel(DataBase.playerTabModel);
        ui->tableView->setSelectionModel(DataBase.playerSelection);
    }
    else{
        qDebug()<<"PlayerModel init failed";
    }
//    setupPlayersModel();
}

void PlayerManager::on_btAddAPlayer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QSqlTableModel *playersModel = DataBase::getInstance().playerTabModel;    //QModelIndex是用来表示model位置的类

    //在末尾添加一个
//    if(!playersModel->insertRow(playersModel->rowCount(),QModelIndex())){
//           qDebug()<<"创建行失败!";
//    }
//    QModelIndex curIndex = playersModel->index(playersModel->rowCount()-1,1);//创建最后一行的modelIndex
//    int curRecNo=curIndex.row();
//    QSqlRecord curRec=playersModel->record(curRecNo);        //获取当前记录
//    curRec.setValue("name",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
//    curRec.setValue("id",QUuid::createUuid().toString(QUuid::WithoutBraces));
//    playersModel->setRecord(curRecNo,curRec);

    // 创建新记录
    QSqlRecord newRecord = playersModel->record();
    playersModel->insertRecord(-1, newRecord);

    //数据映射
    dataMapper =new QDataWidgetMapper();
    QSqlTableModel *tableModel = DataBase::getInstance().playerTabModel;
    dataMapper->setModel(DataBase::getInstance().playerTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    int index=playersModel->rowCount()-1;
    dataMapper->setCurrentIndex(index);
    dataMapper->addMapping(ui->editPlayerName,tableModel->fieldIndex("name"));
    dataMapper->addMapping(ui->editSex,tableModel->fieldIndex("sex"));

}


//添加单个
void PlayerManager::on_BTBoxAddPlayer_accepted()
{
//保存
    dataMapper->submit();
    DataBase::getInstance().submitPlayer();



//清除缓存数据
//跳转回管理页
ui->stackedWidget->setCurrentIndex(0);

//    int count = ui->stackedWidget->count();

//    if(count>1){
//        ui->stackedWidget->setCurrentIndex(count - 2);
//        ui->label->setText(ui->stackedWidget->currentWidget()->windowTitle());
//    }
    //把原窗口删除
    //QWidget *widget = ui->stackedWidget->widget(count-1);
    //ui->stackedWidget->removeWidget(widget);
    //delete widget;
}

//QSqlTableModel* PlayerManager::getAllPlayersModel() {
//    playersModel->select();
//    return playersModel;
//}

//bool PlayerManager::addPlayer(const QString &name, int seed) {
//    QSqlRecord record = playersModel->record();
//    record.setValue("name", name);
//    record.setValue("seed", seed);

//    if (playersModel->insertRecord(-1, record)) {
//        return playersModel->submitAll();
//    }

//    return false;
//}

//bool PlayerManager::deletePlayer(int playerId) {
//    if (playersModel->removeRow(playerId)) {
//        return playersModel->submitAll();
//    }

//    return false;
//}

//bool PlayerManager::updatePlayer(int playerId, const QString &name, int seed) {
//    QSqlRecord record = playersModel->record(playerId);
//    record.setValue("name", name);
//    record.setValue("seed", seed);

//    if (playersModel->setRecord(playerId, record)) {
//        return playersModel->submitAll();
//    }

//    return false;
//}

//void PlayerManager::setupPlayersModel() {
//    playersModel = new QSqlTableModel(this, QSqlDatabase::database());
//    playersModel->setTable("players");
//    playersModel->select();



//}
