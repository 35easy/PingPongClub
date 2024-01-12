#include "grouplist.h"
#include "ui_grouplist.h"

#include <QFileDialog>

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

void GroupList::init(int count,int contain,int winSize)
{
    groupCount=count;
    this->contain=contain;
    this->winSize=winSize;
}

void GroupList::GenerateList(QVector<Player*>& players)
{
    GroupNode* node;
    //初始化list
    for (int i=0;i<groupCount;i++) {
        node=new GroupNode(contain,winSize);
        list.append(node);
        pLayout->addWidget(node);
    }

    int start=0;
    //分配选手,这种分配方法好处是使每一组人数更平均,避免人数不够导致最后一组人数极少的情况
    for(int i=0;i<players.size();i++){
        if(i%groupCount==0)
            start=i;
        list[i-start]->addPlayer(players[i]);
    }

    //初始化表每个节点表格
    for (auto it:list) {
        it->initTableWidget();
    }

//    return;
//    for (int i=0;i<groupCount;i++) {
//        node=new GroupNode(contain,winSize);
//        node->setPlayers(players.mid(i * contain, contain));
//        list.push_back(node);
//        pLayout->addWidget(node);
//    }
}

void GroupList::on_btOK_clicked()
{

    // 获取窗口截图
   QPixmap screenshot =ui->scrollAreaWidgetContents->grab();
   // 获取用户选择的保存路径
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), "", tr("Images (*.png)"));
   // 保存截图到文件
   screenshot.save(filePath);

   //更新到数据库
   DataBase& db=DataBase::getInstance();
   db.clearBySql("player");
    for(auto node:list){
        for(auto win:node->winners){
            db.appendBySql("player",*win);
        }
    }


    this->close();
    this->destroy();
}
