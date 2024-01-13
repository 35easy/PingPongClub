#include "groupnode.h"
#include "ui_groupnode.h"

#include <QPainter>
#include <QTimeEdit>

GroupNode::GroupNode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupNode)
{
    ui->setupUi(this);
}

GroupNode::GroupNode(int size,int winSize, QWidget *parent):
    QWidget(parent),
    ui(new Ui::GroupNode)
{
    ui->setupUi(this);
    this->size=size;
    this->winSize=winSize;
}

void GroupNode::addPlayer(Player *player)
{
    groupPlayers.append(player);
}

void GroupNode::initTableWidget()
{
    size=groupPlayers.size();


    // 创建表格
    ui->tableWidget->setRowCount(size);  // 设置行数
    ui->tableWidget->setColumnCount(size);  // 设置列数


    // 设置表格的固定大小
    int cellSize = 120;
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(cellSize);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(cellSize);

    int tableWidth = size * cellSize+300;
    int tableHeight = size * cellSize+300;
    this->setFixedSize(tableWidth,tableHeight);

    QTimeEdit* scoreEdit;
    //初始化每一项
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i!=j){
                scoreEdit= new QTimeEdit();
                scoreEdit->setDisplayFormat("H:m");
                ui->tableWidget->setCellWidget(i, j, scoreEdit);
                // 为每个 QTimeEdit 添加时间变化的信号连接
                connect(scoreEdit, SIGNAL(timeChanged(const QTime &)), this, SLOT(onTimeChanged()));
            }else{

            }
        }
    }

    // 设置表头
    QStringList headers;

    for(auto it:groupPlayers){
        headers <<it->getName();
    }
    //纵向和横向表头
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setVerticalHeaderLabels(headers);

}

void GroupNode::onTimeChanged() {
       QTimeEdit *changedTimeEdit = qobject_cast<QTimeEdit*>(QObject::sender());
       if (changedTimeEdit) {
           // 查找给定 QTimeEdit* 所在的行
           int row = ui->tableWidget->rowAt(changedTimeEdit->geometry().top());
           int col = ui->tableWidget->columnAt(changedTimeEdit->geometry().left());
           QTime time=changedTimeEdit->time();
           // 更新对角位置上的 QTimeEdit 的时间值
           int diagonalRow = col;
           int diagonalCol = row;
           QTimeEdit *diagonalTimeEdit = qobject_cast<QTimeEdit*>(ui->tableWidget->cellWidget(diagonalRow, diagonalCol));
           if (diagonalTimeEdit) {
               diagonalTimeEdit->setTime(QTime(time.minute(),time.hour()));
           }
       }
}
GroupNode::~GroupNode()
{
    delete ui;
}

//晋级
void GroupNode::on_btAdvance_clicked()
{
   //<players索引,分数>
   QVector<QPair<int, int>> pairs;
   int score=0;
   QTimeEdit *scoreEdit;
   for (int i=0;i<size;i++){
       score=0;
       for (int j=0;j<size;j++) {
           if(i!=j){
              scoreEdit= qobject_cast<QTimeEdit*>(ui->tableWidget->cellWidget(i,j));
              score+=scoreEdit->time().hour();
              qDebug()<<scoreEdit->time();
           }

       }
       pairs.append(QPair<int,int>(i,score));
   }

   // 按照分数降序排序
   std::sort(pairs.begin(), pairs.end(), [](const QPair<int, int> &a, const QPair<int, int> &b){        return a.second > b.second;});
    int index;


   for (int i=0;i<winSize;i++) {

       // 更改第 n 列的表头字体颜色
        index=pairs[i].first;
        winners.append(groupPlayers[index]);

       QFont font = ui->tableWidget->horizontalHeaderItem(index)->font();
       font.setBold(true);

       QBrush brush(Qt::red); // 设置颜色为红色

       ui->tableWidget->horizontalHeaderItem(index)->setForeground(brush);
       ui->tableWidget->verticalHeaderItem(index)->setForeground(brush);

   }

    ui->btAdvance->hide();
}

void GroupNode::on_tableWidget_cellChanged(int row, int column)
{
    qDebug()<<"cellChanged:"<<row<<","<<column;
}

void GroupNode::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"itemChanged:"<<item;
}


//弃用的分配方式
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

void  GroupNode::paintEvent(QPaintEvent *event)
{

       QPainter painter(this);  // 使用 this 作为绘图设备
       painter.setPen(Qt::blue);


       // 画斜对角线
       painter.drawLine(ui->tableWidget->geometry().topLeft(), ui->tableWidget->geometry().bottomRight());
}
