#include "eliminationnode.h"
#include "ui_eliminationnode.h"

EliminationNode::EliminationNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EliminationNode)
{
    ui->setupUi(this);
    player=NULL;
//    setWindowFlags(Qt::FramelessWindowHint);//无边框
}

EliminationNode::EliminationNode(Player *player, QWidget *parent) :
    QWidget(parent),ui(new Ui::EliminationNode)
{
    ui->setupUi(this);
    setPlayer(player);
}

void EliminationNode::setPlayer(Player *player)
{
    this->player=player;
    if(player!=NULL)
         ui->nameEdit->setText(player->getName());
}

int EliminationNode::getScore() const
{
    return ui->scoreEdit->value();
}

EliminationNode::~EliminationNode()
{
    delete ui;
}
