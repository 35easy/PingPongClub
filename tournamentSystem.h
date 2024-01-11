#ifndef TOURNAMENTSYSTEM_H
#define TOURNAMENTSYSTEM_H

#include "playermanager.h"
#include "fixturemanager.h"
#include <QWidget>

namespace Ui {
class TournamentSystem;
}

class TournamentSystem : public QWidget
{
    Q_OBJECT

public:
    explicit TournamentSystem(QWidget *parent = nullptr);
    ~TournamentSystem();

private slots:
    void on_btPlayer_clicked();

    void on_btSeedPlayer_clicked();
    void on_btFixture_clicked();
    void GenerateElimination();
private:
    Ui::TournamentSystem *ui;
    PlayerManager* playerManager;
    FixtureManager* fixtureManager;

};

#endif // TOURNAMENTSYSTEM_H
