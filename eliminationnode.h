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
    ~EliminationNode();
    Player* player;

private:
    Ui::EliminationNode *ui;
    int score;
    EliminationNode* parent;
    EliminationNode* left;
    EliminationNode* right;
    int level;

};

#endif // ELIMINATION_H
