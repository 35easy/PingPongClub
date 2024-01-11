#ifndef GROUPLIST_H
#define GROUPLIST_H

#include "player.h"

#include <QGridLayout>
#include <QWidget>

#include "groupnode.h"
namespace Ui {
class GroupList;
}

class GroupList : public QWidget
{
    Q_OBJECT

public:
    explicit GroupList(QWidget *parent = nullptr);
    ~GroupList();
    QGridLayout *pLayout;
    void init(int count,int contain,int winSize);
    void GenerateList(QVector<Player*>& players);
private:
    Ui::GroupList *ui;
    int groupCount;
    int contain;
    int winSize;
    QVector<GroupNode*>list;
};

#endif // GROUPLIST_H
