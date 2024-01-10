#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QWidget>

namespace Ui {
class Tournament;
}

class Tournament : public QWidget
{
    Q_OBJECT

public:
    explicit Tournament(QWidget *parent = nullptr);
    ~Tournament();

private slots:
    void on_btPlayer_clicked();

    void on_btSeedPlayer_clicked();

    void on_btYes_clicked();

    void on_btFixture_clicked();

    void on_btHome_clicked();

private:
    Ui::Tournament *ui;
};

#endif // TOURNAMENT_H
