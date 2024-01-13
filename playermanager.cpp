
#include "playermanager.h"
#include "ui_palyermanager.h"
PlayerManager::PlayerManager(QWidget *parent)
    :   QWidget(parent),
 ui(new Ui::PlayerManager)
{
    tableName="player";
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    tableView=ui->tableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setAlternatingRowColors(true);
    int cellSize = 180;
    ui->tableView->horizontalHeader()->setDefaultSectionSize(cellSize);


}

void PlayerManager::initDataBase()
{

    DataBase &DataBase = DataBase::getInstance();
    if(DataBase.initModel(tableName)){
        model=DataBase.playerTabModel;
        ui->tableView->setModel(DataBase.playerTabModel);
        ui->tableView->setSelectionModel(DataBase.playerSelection);
    }
    else{
        qDebug()<<"PlayerModel init failed";
    }
    ui->playerCount->setText(QString::number(model->rowCount()));

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

    DataBase::getInstance().clearBySql(tableName);
    if(tableName=="player")
        initDataBase();
}

void PlayerManager::on_btPlayerOK_clicked()
{
    gotoFixturemanager();
}

void PlayerManager::on_btIsSeed_clicked()
{
    // 获取选中的行
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    QString insertName;
    if(tableName=="player")
        insertName="seed";
    else
        insertName="player";
    QString name, sex;
    // 遍历选中的每一行
      for (const QModelIndex &index : selectedIndexes)
      {
          // 获取行号
          int row = index.row();

          // 使用视图的数据提取相应的数据
         name = ui->tableView->model()->data(ui->tableView->model()->index(row, 1), Qt::DisplayRole).toString();
         sex = ui->tableView->model()->data(ui->tableView->model()->index(row, 2), Qt::DisplayRole).toString();

          DataBase::getInstance().appendBySql(insertName,Player(name,sex));
      }

    //从表删除
    on_btDeletPlayer_clicked();
    qDebug()<<ui->btAddAPlayer->text();

}

void PlayerManager::on_btDeletPlayer_clicked()
{
        // 获取选中的行
        QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
        // 如果没有选中的行，直接返回
        if (selectedIndexes.isEmpty())
            return;


        // 逆序删除选中的行，避免删除后索引错乱
        for (int i = selectedIndexes.count() - 1; i >= 0; --i)
        {
            model->removeRow(selectedIndexes.at(i).row());
        }

        // 提交更改到数据库
        if (model->submitAll())
        {
            qDebug() << "删除成功";
        }
        else
        {
            qDebug() << "删除失败: " << model->lastError().text();
            // 如果删除失败，可以进行一些处理，例如撤销已删除的行
            model->revertAll();
        }
}
