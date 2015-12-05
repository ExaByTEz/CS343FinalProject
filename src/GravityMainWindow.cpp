#include "GravityMainWindow.h"
#include "ui_gravitymainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsLineItem"

#include <QGLWidget>
#include <QPalette>
#include "BallObject.h"
#include <QDebug>
GravityMainWindow::GravityMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GravityMainWindow)
{
    ui->setupUi(this);


    //ui->mainDrawingWidget->drawContents(); //make private

    connect(this, SIGNAL(newBall()), ui->mainDrawingWidget, SLOT(addBall()));

}

GravityMainWindow::~GravityMainWindow()
{
    delete ui;
}

void GravityMainWindow::on_mainDrawingWidget_newPointRequested(const QPoint &pPos)
{
    qDebug() << "new point requested at " << pPos.x() <<"," << pPos.y();
}

void GravityMainWindow::on_pushButton_clicked()
{
    qDebug() << "Button Pressed";
    //QCoreApplication::postEvent(ui->graphicsView, new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier));
    emit newBall();
}

