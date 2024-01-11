#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H

#include <QWidget>

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

private slots:
    void on_btCreateFixture_clicked();

    void on_btImportPlayer_clicked();

private:
    Ui::FixtureManager *ui;
};

#endif // FIXTUREMANAGER_H
