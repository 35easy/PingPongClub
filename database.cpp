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
}

bool DataBase::initPlayerModel()
{
    playerTabModel = new QSqlTableModel(this,db);
    playerTabModel->setTable("player");
    playerTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);                       //数据保存方式,OnManualSubmit, OnRowChange
    playerTabModel->setSort(playerTabModel->fieldIndex("id"),Qt::AscendingOrder);       //排序
    if (!(playerTabModel->select())) {
           // 如果表不存在，尝试创建表
           QSqlQuery createTableQuery(db);
           QString createTableSQL = "CREATE TABLE IF NOT EXISTS player "
                                    "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                    "name VARCHAR(50), "
                                    "sex VARCHAR(2))";
           if (!createTableQuery.exec(createTableSQL)) {
               // 创建表失败，输出错误信息
               qDebug() << "Error creating 'player' table:" << createTableQuery.lastError().text();
               return false;
           }
    }
    // 重新尝试查询数据
         if (!(playerTabModel->select())) {
             qDebug() << "Error selecting data from 'player' table:" << playerTabModel->lastError().text();
             return false;
         }

    playerSelection = new QItemSelectionModel(playerTabModel);
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

    if (!query.exec("CREATE TABLE IF NOT EXISTS tournaments ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "date DATE)")) {
        qDebug() << "Create Tournaments Table Error: " << query.lastError().text();
        return false;
    }


    return true;
}

bool DataBase::insertPlayer(const Player& player) {
    // 插入选手数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("INSERT INTO players (name, gender) VALUES (?, ?)");
    query.addBindValue(player.getName());
    query.addBindValue(player.getGender());

    if (!query.exec()) {
        qDebug() << "Insert Player Error: " << query.lastError().text();
        return false;
    }
    return true;
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

QVector<Player> DataBase::getAllPlayers() {
    // 获取所有选手数据的代码，根据需要修改
    QVector<Player> players;
    QSqlQuery query("SELECT id, name, gender FROM players");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString gender = query.value(2).toString();
        players.append(Player(id, name, gender));
    }
    return players;
}

bool DataBase::insertTournament(const Tournament& tournament) {
    // 插入赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("INSERT INTO tournaments (name, date) VALUES (?, ?)");
    query.addBindValue(tournament.getName());
    query.addBindValue(tournament.getDate());

    if (!query.exec()) {
        qDebug() << "Insert Tournament Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateTournament(const Tournament& tournament) {
    // 更新赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("UPDATE tournaments SET name = ?, date = ? WHERE id = ?");
    query.addBindValue(tournament.getName());
    query.addBindValue(tournament.getDate());
    query.addBindValue(tournament.getId());

    if (!query.exec()) {
        qDebug() << "Update Tournament Error: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::deleteTournament(int tournamentId) {
    // 删除赛事数据的代码，根据需要修改
    QSqlQuery query;
    query.prepare("DELETE FROM tournaments WHERE id = ?");
    query.addBindValue(tournamentId);

    if (!query.exec()) {
        qDebug() << "Delete Tournament Error: " << query.lastError().text();
        return false;
    }
    return true;
}

QVector<Tournament> DataBase::getAllTournaments() {
    // 获取所有赛事数据的代码，根据需要修改
    QVector<Tournament> tournaments;
    QSqlQuery query("SELECT id, name, date FROM tournaments");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QDate date = query.value(2).toDate();
        tournaments.append(Tournament(id, name, date));
    }
    return tournaments;
}


