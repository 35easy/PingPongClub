
#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "player.h"
#include "fixture.h"
class DataBase : public QObject
{
    Q_OBJECT
public:
    //这个函数用于访问类的单一实例。它被声明为静态函数，因此可以在不创建类实例的情况下调用。
    static DataBase& getInstance()
    {
        static DataBase instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    void initDataBase();
    bool initModel(QString tableName);
    bool insertPlayer(const Player& player);  // 插入选手数据
    bool submitPlayer();
    void clearPlayer(QString tableName);
    bool openConnection();
    void closeConnection();
    void appendBySql(QString tableName,const Player& player);
    void clearBySql(QString tableName);

    void copyRecord(bool isFromplayer);
    bool createTables();  // 创建数据库表格
    bool updatePlayer(const Player& player);  // 更新选手数据
    bool deletePlayer(int playerId);  // 删除选手数据
    QVector<Player*> getAllPlayers(QString tableName);  // 获取所有选手数据



    bool insertFixture(const Fixture& Fixture);  // 插入赛事数据
    bool updateFixture(const Fixture& Fixture);  // 更新赛事数据
    bool deleteFixture(int FixtureId);  // 删除赛事数据
    QVector<Fixture> getAllFixtures();  // 获取所有赛事数据

    QSqlTableModel *playerTabModel;       //数据模型
    QItemSelectionModel *playerSelection;  //选择模型
    QSqlTableModel *seedTabModel;       //数据模型
    QItemSelectionModel *seedSelection;  //选择模型


private:
    //DataBase类的构造函数是私有的，意味着无法从类外部调用它。
    explicit DataBase(QObject *parent = nullptr);


    //阻止了类的拷贝构造函数（copy constructor）和拷贝赋值运算符（copy assignment operator）的使用,
    //这样的删除操作告诉编译器不允许通过拷贝的方式创建类的新实例或进行拷贝赋值操作。
    DataBase(DataBase const&)               = delete;
    void operator=(DataBase const&)  = delete;


    QSqlDatabase db;

};

#endif // DataBase_H
