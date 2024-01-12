#include "database.h"


DataBase::DataBase(QObject *parent) : QObject(parent)
{
    initDataBase();
}

//初始话连接
void DataBase::initDataBase()
{
    db=QSqlDatabase::addDatabase("QSQLITE"); //添加sql lite数据库驱动
    QString aFile="PingPong.db";
    db.setDatabaseName(aFile);//设置数据库路径，不存在则创建

    if(db.open()){
        qDebug()<<"open DataBase is ok!";
    }
    else{
        qDebug()<<"failed to open DataBase";
    }
    playerTabModel=new QSqlTableModel(this,db);
    seedTabModel=new QSqlTableModel(this,db);
}

bool DataBase:: initModel(QString tableName)
{
    QSqlTableModel *model;
    if(tableName=="player"){
        model=playerTabModel;
        playerSelection = new QItemSelectionModel(model);

    }
    else{
        model=seedTabModel;
        seedSelection = new QItemSelectionModel(model);

    }

    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);                       //数据保存方式,OnManualSubmit, OnRowChange
    model->setSort(model->fieldIndex("id"),Qt::AscendingOrder);       //排序
    if (!(model->select())) {
           // 如果表不存在，尝试创建表
           QSqlQuery createTableQuery(db);
           QString createTableSQL = "CREATE TABLE IF NOT EXISTS "+tableName+
                                    "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "name VARCHAR(50), "
                                    "sex VARCHAR(2))";
           if (!createTableQuery.exec(createTableSQL)) {
               // 创建表失败，输出错误信息
               qDebug() << "Error creating '"+tableName+"' table:" << createTableQuery.lastError().text();
               return false;
           }
    }
    // 重新尝试查询数据
         if (!(model->select())) {
             qDebug() << "Error selecting data from '"+tableName+"' table:" << model->lastError().text();
             return false;
         }

    return true;
}

bool DataBase::submitPlayer()
{

    if (playerTabModel->isDirty()) {
        if (playerTabModel->submitAll()) {
            qDebug() << "提交成功!";
            return true;
        } else {
            qDebug() << "提交失败:" << playerTabModel->lastError().text();
            return false;
        }
    } else {
        qDebug() << "没有需要提交的更改。";
        return false;
    }

}

void DataBase::clearPlayer(QString tableName)
{
   playerTabModel->removeRows(0,playerTabModel->rowCount());
   if(playerTabModel->submitAll()){
       qDebug() << "删除成功!";
   }else {
       qDebug() << "删除失败:" << playerTabModel->lastError().text();
   }

}


bool DataBase::openConnection() {
    // 打开数据库连接
    if (!db.open()) {
        qDebug() << "DataBase Error: " << db.lastError().text();
        return false;
    }
    return true;
}

void DataBase::closeConnection() {
    // 关闭数据库连接
    db.close();
}

void DataBase::appendBySql(QString tableName,const Player& player)
{

     //插入选手数据的代码，根据需要修改
        QSqlQuery query;
        query.prepare("INSERT INTO "+tableName+" (name, sex) VALUES (?, ?)");
        query.addBindValue(player.getName());
        query.addBindValue(player.getGender());

        if (!query.exec()) {
            qDebug() << "Insert Player Error: " << query.lastError().text();
        }
}

void DataBase::clearBySql(QString tableName)
{
        QSqlQuery query;
       if (query.exec("DELETE FROM "+tableName)) {
           qDebug() << " table records deleted successfully.";
       } else {
           qDebug() << "Failed to delete records from Player table:" << query.lastError().text();
       }
}

bool DataBase::insertPlayer(const Player& player) {
    // 假设 model 是一个已经与 player 表关联的 QSqlTableModel 对象
    QSqlRecord record = playerTabModel->record();

    // 在 model 中插入一行新的记录
//    playerTabModel->insertRow(-1);
    int row=playerTabModel->rowCount();
    playerTabModel->insertRecord(-1, record);

    // 设置新插入行的数据
    playerTabModel->setData(playerTabModel->index(row, 1), player.getName()); // 假设 name 列是第一列
    playerTabModel->setData(playerTabModel->index(row, 2), player.getGender()); // 假设 gender 列是第二列

    // 提交修改到数据库
    if (!playerTabModel->submitAll()) {
        qDebug() << "Insert Error: " << playerTabModel->lastError().text();
        playerTabModel->revertAll(); // 如果提交失败，回滚修改
        return false;
    }

    return true;
}



//弃用
void DataBase::copyRecord(bool isFromplayer)
{
    QSqlQuery query;
    QString from="player",to="seed";
    if(!isFromplayer){
        from=to;
        to="player";
}

// 执行 SQL 语句，复制记录
    query.prepare("INSERT INTO ? (id, name,sex)"
                  "SELECT id, name, sex"
                  "FROM ?"
                  "WHERE your_condition;");

   if (!query.exec())
   {
      qDebug()<<query.lastError().text();
   }
}




bool DataBase::updatePlayer(const Player& player) {
    // 更新选手数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("UPDATE players SET name = ?, gender = ? WHERE id = ?");
    query.addBindValue(player.getName());
    query.addBindValue(player.getGender());
    query.addBindValue(player.getId());

    if (!query.exec()) {
        qDebug() << "Update Player Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::deletePlayer(int playerId) {
    // 删除选手数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("DELETE FROM players WHERE id = ?");
    query.addBindValue(playerId);

    if (!query.exec()) {
        qDebug() << "Delete Player Error: " << query.lastError().text();
        return false;
    }
    return true;
}

QVector<Player*> DataBase::getAllPlayers(QString tableName) {
    // 获取所有选手数据的代码，根据需要修改
    QVector<Player*> players;
    QSqlQuery query("SELECT id, name, sex FROM "+tableName);
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString sex = query.value(2).toString();
        players.append(new Player(id, name, sex));
    }
    return players;
}


//弃用代码
bool DataBase::createTables() {
    // 创建数据库表格的代码，根据需要修改
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS players ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "gender TEXT)")) {
        qDebug() << "Create Players Table Error: " << query.lastError().text();
        return false;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS Fixtures ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "date DATE)")) {
        qDebug() << "Create Fixtures Table Error: " << query.lastError().text();
        return false;
    }


    return true;
}
bool DataBase::insertFixture(const Fixture& Fixture) {
    // 插入赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("INSERT INTO Fixtures (name, date) VALUES (?, ?)");
    query.addBindValue(Fixture.getName());
    query.addBindValue(Fixture.getDate());

    if (!query.exec()) {
        qDebug() << "Insert Fixture Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateFixture(const Fixture& Fixture) {
    // 更新赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("UPDATE Fixtures SET name = ?, date = ? WHERE id = ?");
    query.addBindValue(Fixture.getName());
    query.addBindValue(Fixture.getDate());
    query.addBindValue(Fixture.getId());

    if (!query.exec()) {
        qDebug() << "Update Fixture Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::deleteFixture(int FixtureId) {
    // 删除赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("DELETE FROM Fixtures WHERE id = ?");
    query.addBindValue(FixtureId);

    if (!query.exec()) {
        qDebug() << "Delete Fixture Error: " << query.lastError().text();
        return false;
    }
    return true;
}

QVector<Fixture> DataBase::getAllFixtures() {
    // 获取所有赛事数据的代码，根据需要修改
    QVector<Fixture> Fixtures;
    QSqlQuery query("SELECT id, name, date FROM Fixtures");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QDate date = query.value(2).toDate();
        Fixtures.append(Fixture(id, name, date));
    }
    return Fixtures;
}


