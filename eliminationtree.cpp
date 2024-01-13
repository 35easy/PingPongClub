#include "eliminationtree.h"
#include "ui_eliminationtree.h"


EliminationTree::EliminationTree(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EliminationTree)
{
    ui->setupUi(this);

}


EliminationTree::~EliminationTree()
{
    delete ui;
}

void EliminationTree::init(int level)
{
    this->setFixedSize(WIDGET_WIDTH,WIDGET_HEIGHT);           //设置页面长宽
//    this->showFullScreen();
    advance=new QPushButton(this);
    advance->setText("晋级");
    advance->setFont(QFont("宋体",15));
    advance->setGeometry(WIDGET_WIDTH/2-70,WIDGET_HEIGHT/3,140,50);
    connect(advance,&QPushButton::clicked,this,&EliminationTree::playerAdvance);


    root=new EliminationNode(this);
    root->setGeometry(WIDGET_WIDTH/2-70,WIDGET_HEIGHT/2-20,140,40);
    this->level=level;
}

void EliminationTree::drawTree(QVector<Player*>& players)
{

    //画图
    //初始化内层
    int size=pow(2,level)-1;
    int end=pow(2,level-1)-1;
    //设置索引0
    nodes.push_back(new EliminationNode(this));
    nodes[0]->hide();
    nodes.push_back(root);
    for (int i = 1; i <end; ++i) {
        nodes.push_back(new EliminationNode(this));
    }

    //初始化最外层参赛选手结点
    for(int i=0;i<players.size();i++){
        nodes.push_back(new EliminationNode(players[i],this));
    }



    //最外层数
    int outSum=size-end;
    qDebug()<<"outSum:"<<outSum;

    int x=root->geometry().x();
    int y=root->geometry().y();
    //当前层数,1开始计
    nodes[2]->move(x-WIDGET_WIDTH/(level*2-1),y);
    nodes[3]->move(x+WIDGET_WIDTH/(level*2-1),y);
    int currentLevel=3;
    float h= WIDGET_HEIGHT/4;
    for (int i=4;i<nodes.size();i++) {

        //区分左右用当前层数
        //第一个往左结点是2,第一个往右结点是3
        //更新层数
        if(pow(2,currentLevel)-1<i){
            currentLevel++;
            h=WIDGET_HEIGHT/(i+1);
        }

        //左
        if(i>>(currentLevel-2)==2){
            x=nodes[i/2]->geometry().x()-WIDGET_WIDTH/(level*2);

        }//右
        else if(i>>(currentLevel-2)==3){
            x=nodes[i/2]->geometry().x()+WIDGET_WIDTH/(level*2);
        }

        if(i%2==0)
            y=nodes[i/2]->geometry().y()-h;
        else{
            y=nodes[i/2]->geometry().y()+h;
        }
//        qDebug()<<x<<"<<<"<<y;

        nodes[i]->move(x,y);
    }
    return;
}

void EliminationTree::saveResult()
{
    // 获取窗口截图
   QPixmap screenshot = this->grab();

   // 获取用户选择的保存路径
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), "", tr("Images (*.png)"));

   // 保存截图到文件
    screenshot.save(filePath);
}
//
void EliminationTree::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setPen(QPen(Qt::black,2));//设置画笔形式
    int size=nodes.size();
    for (int i=1;i*2+1<size;i++) {
       if(i*2<size){
             painter.drawLine(nodes[i]->geometry().center(),nodes[i*2]->geometry().center());
       }

       if(i*2+1<size){
           painter.drawLine(nodes[i]->geometry().center(),nodes[i*2+1]->geometry().center());

       }
    }
}

void EliminationTree::playerAdvance()
{
    if(level<=1)
    {
        qDebug()<<"比赛已经晋级完毕";
        saveResult();
        return;
    }
    //最外层起始数
    int i=pow(2,level-1),size=nodes.size();
    while (i<size) {
        if(i+1>=size||nodes[i]->getScore()>nodes[i+1]->getScore()||nodes[i+1]->player==NULL){
            nodes[i/2]->setPlayer(nodes[i]->player);
        }else{
            nodes[i/2]->setPlayer(nodes[i+1]->player);

        }
        i+=2;
    }
    level--;
    qDebug()<<"晋级";
}

