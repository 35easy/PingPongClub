#include "tournament.h"
#include "ui_tournament.h"

Tournament::Tournament(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tournament)
{
    ui->setupUi(this);
}

Tournament::~Tournament()
{
    delete ui;
}
