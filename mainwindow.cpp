#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tournamentSystem=new TournamentSystem();
    ui->stackedWidget->addWidget(tournamentSystem);
    ui->stackedWidget->setCurrentIndex(2);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btTournament_clicked(bool checked)
{
<<<<<<< HEAD
    ui->stackedWidget->setCurrentIndex(1);

=======

    ui->stackedWidget->setCurrentIndex(2);
>>>>>>> main
}
