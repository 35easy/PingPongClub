#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H

#include <QWidget>
#include "eliminationtree.h"
#include "database.h"
namespace Ui {
class FixtureManager;
}

class FixtureManager : public QWidget
{
    Q_OBJECT

public:
    explicit FixtureManager(QWidget *parent = nullptr);
    ~FixtureManager();


signals:
    void gotoPlayerManager();
    void GenerateElimination();
private slots:
    void on_btCreateFixture_clicked();

    void on_btImportPlayer_clicked();

    void on_btYes_clicked();


private:
    Ui::FixtureManager *ui;
    EliminationTree *eTree;
};

#endif // FIXTUREMANAGER_H
