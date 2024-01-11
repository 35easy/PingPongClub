#include "groupnode.h"
#include "ui_groupnode.h"

GroupNode::GroupNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupNode)
{
    ui->setupUi(this);
}

GroupNode::~GroupNode()
{
    delete ui;
}
