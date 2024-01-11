#include "groupnode.h"
#include "ui_groupnode.h"

GroupNode::GroupNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupNode)
{
    ui->setupUi(this);
}

GroupNode::GroupNode(int size, QWidget *parent):
    QWidget(parent),
    ui(new Ui::GroupNode)
{
    ui->setupUi(this);
    this->size=size;
    // 创建表格
    ui->tableWidget->setRowCount(size);  // 设置行数
    ui->tableWidget->setColumnCount(size);  // 设置列数
    // 设置表格的固定大小
    int cellSize = 120;
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(cellSize);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(cellSize);

    int tableWidth = size * cellSize+100;
    int tableHeight = size * cellSize+100;
    ui->tableWidget->setFixedSize(tableWidth, tableHeight);


}




GroupNode::~GroupNode()
{
    delete ui;
}

void GroupNode::setPlayers(const QVector<Player *> &groupPlayers)
{
    this->groupPlayers=groupPlayers;
    // 设置表头
    QStringList headers;

    for(auto it:groupPlayers){
        headers <<it->getName();
    }
    //纵向和横向表头
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setVerticalHeaderLabels(headers);
}
