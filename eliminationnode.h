#ifndef ELIMINATION_H
#define ELIMINATION_H

#include <QWidget>
#include <player.h>
namespace Ui {
class EliminationNode;
}

class EliminationNode : public QWidget
{
    Q_OBJECT

public:
    explicit EliminationNode(QWidget *parent = nullptr);
     EliminationNode(Player* player,QWidget *parent = nullptr);
     void setPlayer(Player* player);
     int getScore() const;
    ~EliminationNode();
    Player* player;
private:
    Ui::EliminationNode *ui;
};

#endif // ELIMINATION_H
