#include "fixturemanager.h"
#include "ui_fixturemanager.h"

FixtureManager::FixtureManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixtureManager)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
}

FixtureManager::~FixtureManager()
{
    delete ui;
}

void FixtureManager::on_btCreateFixture_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void FixtureManager::on_btImportPlayer_clicked()
{
    emit gotoPlayerManager();
}
