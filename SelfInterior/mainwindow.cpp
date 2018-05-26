#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionPrint_triggered()
{
    if(mScreenshot != NULL){
        delete mScreenshot;
    }
    mScreenshot = new Screenshot(this->x(),this->y(),this->x()+this->width(),this->y()+this->height());
    mScreenshot->move(QApplication::desktop()->availableGeometry(mScreenshot).topLeft() + QPoint(20, 20));
    mScreenshot->show();
}
