#include "GravityMainWindow.h"
#include "ui_gravitymainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsLineItem"

#include <QGLWidget>
#include "BallObject.h"
#include <QDebug>
GravityMainWindow::GravityMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GravityMainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));

    ui->widget->drawContents();
    ui->widget->updateGL();

    //Create scene
    QGraphicsScene* scene = new QGraphicsScene();

    //Temporary
    //Add a line to the scene
    QGraphicsLineItem* ground = new QGraphicsLineItem();
    ground->setLine(0, 400, 490, 400);

    scene->addItem(ground);
    //Create a ball at position (50,50) with w=25 and h=25
    BallObject* lBall = new BallObject();
    lBall->setRect(50, 50, 25, 25);


    //add item to scene
    scene->addItem(lBall);

    lBall->setFlag(QGraphicsItem::ItemIsFocusable);
    lBall->setFocus();

    //Add the scene to the graphics view
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->show();
}

GravityMainWindow::~GravityMainWindow()
{
    delete ui;
}

void GravityMainWindow::on_pushButton_clicked()
{
    qDebug() << "Button Pressed";
    QCoreApplication::postEvent(ui->graphicsView, new QKeyEvent(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier));


}
