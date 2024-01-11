#include "grouplist.h"
#include "ui_grouplist.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);
     pLayout = new QGridLayout();//网格布局
     ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
}



GroupList::~GroupList()
{
    delete ui;
}

void GroupList::init(int count,int contain)
{
    groupCount=count;
    this->contain=contain;
}

void GroupList::GenerateList(QVector<Player*>& players)
{
    GroupNode* node;
    for (int i=0;i<groupCount;i++) {
        node=new GroupNode(contain);
        node->setPlayers(players.mid(i * contain, contain));
        list.push_back(node);
        pLayout->addWidget(node);
    }
}
