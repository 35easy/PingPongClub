
#include "playermanager.h"
#include "ui_palyermanager.h"
PlayerManager::PlayerManager(QWidget *parent)
    :   QWidget(parent),
 ui(new Ui::PlayerManager)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

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

//跳转回管理页
ui->stackedWidget->setCurrentIndex(0);
}

void PlayerManager::on_btAddFilePlayer_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "../", "文本文件 (*.xlsx);;所有文件 (*.*)");
    if (!fileName.isEmpty()) {
        xlsx=new QXlsx::Document(fileName);
        qDebug() << "选择的文件：" << fileName;
    } else {
        // 用户取消选择文件
        qDebug() << "用户取消选择文件";
        return;
    }

    if(!xlsx->load())
        qDebug()<<"excel打开失败";
    //处理表格除去前面的无用项
    int colSum=xlsx->dimension().columnCount(),rowSum=xlsx->dimension().rowCount();
    int row=1,col=colSum;
    while (!xlsx->read(row,col).isValid()) row++;
    row++;//去表头

    QString id,name,sex;
    for (;row<rowSum;row++) {
//        id=xlsx->read(row,1).toString();
        name=xlsx->read(row,2).toString();
        sex=xlsx->read(row,3).toString();
        DataBase::getInstance().insertPlayer(Player(name,sex));
        qDebug()<<id<<name<<sex;
    }

}

void PlayerManager::on_btClearPlayer_clicked()
{

    DataBase::getInstance().clearPlayer();
}

void PlayerManager::on_btPlayerOK_clicked()
{
    gotoFixturemanager();
}
