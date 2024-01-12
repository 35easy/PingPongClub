#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "player.h"

#include <QWidget>
#include <QDebug>
#include <QTableWidget>
namespace Ui {
class GroupNode;
}

class GroupNode : public QWidget
{
    Q_OBJECT

public:
    explicit GroupNode(QWidget *parent = nullptr);
    GroupNode(int size,int winSize,QWidget *parent = nullptr);
    void addPlayer(Player *player);
    void initTableWidget();
    ~GroupNode();
    void setPlayers(const QVector<Player*> &groupPlayers);

    QVector<Player*> winners;

private slots:
    void onTimeChanged();

    void on_btAdvance_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    QVector<Player*> groupPlayers;
    int size;
    int winSize;
    Ui::GroupNode *ui;

};

#endif // GROUPNODE_H
