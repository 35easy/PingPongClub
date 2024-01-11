#include "eliminationnode.h"
#include "ui_eliminationnode.h"

EliminationNode::EliminationNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EliminationNode)
{
    ui->setupUi(this);
//    setWindowFlags(Qt::FramelessWindowHint);//无边框

}

EliminationNode::EliminationNode(Player *player, QWidget *parent) :
    QWidget(parent),ui(new Ui::EliminationNode)
{
    ui->setupUi(this);

    this->player=player;
    ui->nameEdit->setText(player->getName());
}



EliminationNode::~EliminationNode()
{
    delete ui;
}
