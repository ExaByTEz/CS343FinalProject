#include "GravityMainWindow.h"
#include "ui_gravitymainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsLineItem"
#include "BallObject.h"

#include <QMainWindow>
#include <QGLWidget>
#include <QPalette>
GravityMainWindow::GravityMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GravityMainWindow)
{
    ui->setupUi(this);

#ifndef _WIN32   // The cross cursor is all-black and invisible on windows (boo)
    ui->mainGLWidget->setCursor(Qt::CrossCursor);
#endif

    timer = new QTimer(this);

    connect(this, SIGNAL(newBall(QPoint, int, double, double, int)), ui->mainDrawingWidget, SLOT(addBall(QPoint, int, double, double, int)));
    //the timer will call these methods every 50 ms
    connect(timer, SIGNAL(timeout()), ui->mainDrawingWidget, SLOT(updateBall()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGUI()));
}

GravityMainWindow::~GravityMainWindow()
{
    delete timer;
    delete ui;
}

void GravityMainWindow::enableGUI(bool pEnabled)
{
    ui->gravitySpinBox->setEnabled(pEnabled);
    ui->massSpinBox->setEnabled(pEnabled);
    ui->radiusSpinBox->setEnabled(pEnabled);
    ui->yVelocitySpinBox->setEnabled(pEnabled);
    ui->xVelocitySpinBox->setEnabled(pEnabled);
    ui->startButton->setText((pEnabled ? "Start" : "Stop"));
    ui->timeStepSpinBox->setEnabled(pEnabled);
}

void GravityMainWindow::on_mainDrawingWidget_newPointRequested(const QPoint &pPos)
{
    if(mStartSimulation) return; //Don't allow user to add a ball while running
    emit newBall(pPos,ui->radiusSpinBox->value(), ui->massSpinBox->value(), 0, ++mNumItems);
    ui->mainDrawingWidget->updateGravity(ui->gravitySpinBox->value()); //update gravity on new ball
    ui->mainDrawingWidget->updateTimeStep(ui->timeStepSpinBox->value());

    ui->comboBox->addItem("Ball " + QString::number(mNumItems));
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1); //Set focus to most recent item
}

void GravityMainWindow::on_comboBox_currentIndexChanged(int pIndex)
{
    if(pIndex < 0) return; //when the combobox is cleared
    if(mActiveIndex >= 0) ui->mainDrawingWidget->getBall(mActiveIndex)->setColor(QColor(255, 100, 100, 255)); //set the previous ball to a default color
    mActiveIndex = pIndex; //Update the new active index to the one passed from the parameter

    BallObject *lBall = ui->mainDrawingWidget->getBall(mActiveIndex);

    ui->yVelocitySpinBox->setValue(lBall->getVerticalVelocity()); //update the spinboxes
    ui->radiusSpinBox->setValue(lBall->getRadius());
    ui->massSpinBox->setValue(lBall->getMass());
    ui->timeSpinBox->setValue(lBall->getTime());

    lBall->setColor(QColor(100, 100, 255, 255)); //set the active ball to a blue color

    ui->mainDrawingWidget->updateGL();
}

void GravityMainWindow::on_radiusSpinBox_valueChanged(int pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->getBall(mActiveIndex)->setRadius(pValue);
    ui->mainDrawingWidget->updateGL();
}

void GravityMainWindow::on_massSpinBox_valueChanged(double pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->getBall(mActiveIndex)->setMass(pValue);
}

void GravityMainWindow::on_yVelocitySpinBox_valueChanged(double pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->getBall(mActiveIndex)->setVerticalVelocity(pValue);
}

void GravityMainWindow::on_xVelocitySpinBox_valueChanged(double pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->getBall(mActiveIndex)->setHorizontalVelocity(pValue);
}

void GravityMainWindow::on_gravitySpinBox_valueChanged(double pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->updateGravity(pValue);
}

void GravityMainWindow::on_timeStepSpinBox_valueChanged(double pValue)
{
    if(mActiveIndex < 0) return;
    ui->mainDrawingWidget->updateTimeStep(pValue);
}

void GravityMainWindow::updateGUI() //Updates GUI with the ball update
{
    if(mActiveIndex >= 0)
    {
        BallObject *lBall = ui->mainDrawingWidget->getBall(mActiveIndex);
        ui->timeStepSpinBox->setValue(lBall->getTimeStep());
        ui->timeSpinBox->setValue(lBall->getTime());
        ui->yVelocitySpinBox->setValue(lBall->getVerticalVelocity());
        ui->xVelocitySpinBox->setValue(lBall->getHorizontalVelocity());
    }
}

void GravityMainWindow::on_resetButton_clicked()
{
    timer->stop();
    mStartSimulation = false;
    mActiveIndex = -1;
    mNumItems = 0;
    ui->comboBox->clear();
    ui->mainDrawingWidget->clearScene();
    enableGUI(true);
}

void GravityMainWindow::on_startButton_clicked()
{
    if(!mStartSimulation)
    {
        timer->start(50); //Update every 50 ms
        enableGUI(false); //Do not allow changes while the simulation is running
    }
    else
    {
        timer->stop();
        enableGUI(true); //Allow updates to the GUI again
    }
    mStartSimulation = !mStartSimulation;

}
// Closes program when exit option is selected from Menu
void GravityMainWindow::on_actionExit_triggered()
{
    exit(0);
}

