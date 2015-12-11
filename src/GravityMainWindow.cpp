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

#ifndef _WIN32   // The cross cursor is all-black and invisible on windows (boo)
    ui->mainGLWidget->setCursor(Qt::CrossCursor);
#endif
    connect(this, SIGNAL(newBall(QPoint)), ui->mainDrawingWidget, SLOT(addBall(QPoint)));
}

GravityMainWindow::~GravityMainWindow()
{
    delete ui;
}

void GravityMainWindow::on_mainDrawingWidget_newPointRequested(const QPoint &pPos)
{
    qDebug() << "GravityMainWindow.cpp: on_mainDrawingWidget_newPointRequested at " << pPos.x() <<"," << pPos.y();
    emit newBall(pPos);
}

void GravityMainWindow::on_pushButton_clicked()
{
    if(!mStartSimulation)
    {
        qDebug() << "GravityMainWindow: Button Pressed";
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), ui->mainDrawingWidget, SLOT(updateBall()));
        timer->start(50);
    }
    mStartSimulation = true;
}

