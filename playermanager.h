#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include <QObject>
#include <QWidget>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include "player.h"
#include <QDataWidgetMapper>
#include "database.h"
#include "xlsxdocument.h"
namespace Ui {
class PlayerManager;
}
class PlayerManager : public QWidget {
    Q_OBJECT

public:
    explicit PlayerManager(QWidget *parent = nullptr);
    // 查询所有选手
    QSqlTableModel* getAllPlayersModel();


    // 删除选手
    bool deletePlayer(int playerId);

    // 更新选手信息
    bool updatePlayer(int playerId, const QString &name, int seed);

    void initDataBase();
    QTableView *tableView;

signals:
    void gotoFixturemanager();

private slots:
    void on_btAddAPlayer_clicked();


    void on_BTBoxAddPlayer_accepted();

    void on_btAddFilePlayer_clicked();

    void on_btClearPlayer_clicked();

    void on_btPlayerOK_clicked();

    void on_btIsSeed_clicked();

    void on_btDeletPlayer_clicked();

protected:
    Ui::PlayerManager *ui;
    QString tableName;
    QSqlTableModel *model;
    QDataWidgetMapper *dataMapper;  //数据映射
    QXlsx::Document* xlsx = nullptr;

};

#endif // PLAYERMANAGER_H
