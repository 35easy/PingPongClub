#ifndef GROUPNODE_H
#define GROUPNODE_H

#include <QWidget>

namespace Ui {
class GroupNode;
}

class GroupNode : public QWidget
{
    Q_OBJECT

public:
    explicit GroupNode(QWidget *parent = nullptr);
    ~GroupNode();

private:
    Ui::GroupNode *ui;
};

#endif // GROUPNODE_H
