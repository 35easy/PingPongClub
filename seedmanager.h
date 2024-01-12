#ifndef SEEDMANAGER_H
#define SEEDMANAGER_H
#include "playermanager.h"
#include <QWidget>
namespace Ui {
class PlayerManager;
}
class SeedManager : public PlayerManager
{
    Q_OBJECT
public:
    SeedManager(QWidget *parent = nullptr);
    void initUI();
    ~SeedManager();
    void initDataBase() ;

private:

//    Ui::PlayerManager *ui;  // 添加 ui 指针，确保声明

};

#endif // SEEDMANAGER_H
