#ifndef ELIMINATIONTREE_H
#define ELIMINATIONTREE_H
#define WIDGET_WIDTH 1680
#define WIDGET_HEIGHT 980
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QDebug>
#include <QtMath>
#include "eliminationnode.h"
#include "player.h"
namespace Ui {
class EliminationTree;
}

class EliminationTree : public QWidget
{
    Q_OBJECT

public:
    explicit EliminationTree(QWidget *parent = nullptr);
    ~EliminationTree();
    void init(int level);
    void drawTree( QVector<Player>& players);
    void drawNode();
private:
    Ui::EliminationTree *ui;
    EliminationNode *root;
    QPushButton *advance;//晋级
    QVector<EliminationNode*> nodes;
    int level;
};

#endif // ELIMINATIONTREE_H
