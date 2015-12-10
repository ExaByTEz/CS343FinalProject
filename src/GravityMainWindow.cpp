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

    timer = new QTimer(this);

    connect(this, SIGNAL(newBall(QPoint, int)), ui->mainDrawingWidget, SLOT(addBall(QPoint, int)));
    //the timer will call these methods every 50 ms
    connect(timer, SIGNAL(timeout()), ui->mainDrawingWidget, SLOT(updateBall()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
}

GravityMainWindow::~GravityMainWindow()
{
    delete timer;
    delete ui;
}

void GravityMainWindow::on_mainDrawingWidget_newPointRequested(const QPoint &pPos)
{
    //qDebug() << "GravityMainWindow.cpp: on_mainDrawingWidget_newPointRequested at " << pPos.x() <<"," << pPos.y();
    emit newBall(pPos, ++mNumItems);
    ui->comboBox->addItem("Ball " + QString::number(mNumItems));
}

void GravityMainWindow::on_comboBox_currentIndexChanged(int pIndex)
{
    //qDebug() << "GravityMainWindow: Selection changed to " + QString::number(pIndex);
    if(mActiveIndex >= 0) ui->mainDrawingWidget->getBall(mActiveIndex)->setColor(QColor(255, 100, 100, 255)); //set the previous ball to a default color
    mActiveIndex = pIndex; //Update the new active index to the one passed from the parameter
    ui->textEdit_3->setText(QString::number(ui->mainDrawingWidget->getBall(mActiveIndex)->getVerticalVelocity()));
    ui->mainDrawingWidget->getBall(mActiveIndex)->setColor(QColor(100, 100, 255, 255)); //set the active ball to a blue color

    ui->mainDrawingWidget->updateGL();
}

void GravityMainWindow::updateGUI()
{
    if(mActiveIndex >= 0) ui->textEdit_3->setText(QString::number(ui->mainDrawingWidget->getBall(mActiveIndex)->getVerticalVelocity()));
}

void GravityMainWindow::on_pushButton_clicked()
{
    if(!mStartSimulation)
    {
        //qDebug() << "GravityMainWindow: Starting";
        timer->start(50); //Update every 50 ms
    }
    else
    {
        //qDebug() <<"GravityMainWindow: Pausing";
        timer->stop();
    }
    mStartSimulation = !mStartSimulation;
}

