#include "GravityMainWindow.h"
#include "ui_gravitymainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsEllipseItem"
#include "QGraphicsLineItem"

#include <QGLWidget>
//#include "BallObject.h"

GravityMainWindow::GravityMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GravityMainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));

    //Create scene
    QGraphicsScene* scene = new QGraphicsScene();

    //Temporary
    //Create a ball at position (50,50) with w=25 and h=25
    QGraphicsEllipseItem* ball = new QGraphicsEllipseItem();
    ball->setRect(50, 50, 25, 25);


    //add item to scene
    scene->addItem(ball);

    //Add a line to the scene
    QGraphicsLineItem* ground = new QGraphicsLineItem();
    ground->setLine(0, 400, 490, 400);

    scene->addItem(ground);

    //Add the scene to the graphics view
    ui->graphicsView->setScene(scene);
}

GravityMainWindow::~GravityMainWindow()
{
    delete ui;
}
