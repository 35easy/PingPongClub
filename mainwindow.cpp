#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tournament=new Tournament();
    ui->stackedWidget->addWidget(tournament);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btTournament_clicked(bool checked)
{

    ui->stackedWidget->setCurrentIndex(1);
}
