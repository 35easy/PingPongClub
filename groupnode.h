#ifndef GROUPNODE_H
#define GROUPNODE_H

#include "player.h"

#include <QWidget>

namespace Ui {
class GroupNode;
}

class GroupNode : public QWidget
{
    Q_OBJECT

public:
    explicit GroupNode(QWidget *parent = nullptr);
    GroupNode(int size,QWidget *parent = nullptr);
    ~GroupNode();

    void setPlayers(const QVector<Player*> &groupPlayers);
private:
    QVector<Player*> groupPlayers;
    int size;
    Ui::GroupNode *ui;
};

#endif // GROUPNODE_H
