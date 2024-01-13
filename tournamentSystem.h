#ifndef TOURNAMENTSYSTEM_H
#define TOURNAMENTSYSTEM_H
#include "ui_fixturemanager.h"
#include "playermanager.h"
#include "seedmanager.h"
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

    void on_btSeed_clicked();

private:
    Ui::TournamentSystem *ui;
    PlayerManager* playerManager;
    SeedManager* seedManager;
    FixtureManager* fixtureManager;

};

#endif // TOURNAMENTSYSTEM_H
