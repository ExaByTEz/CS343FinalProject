#ifndef GL2DDRAWINGWIDGET_H
#define GL2DDRAWINGWIDGET_H

#include "CGCommon.h"

#include <QGLWidget>
#include <QQueue>
//#include "OpenGLRenderable.h"

class BallObject;

class GL2DDrawingWidget : public QGLWidget
{
public:
    GL2DDrawingWidget(QWidget *parent = 0, QGLWidget *share = 0);
    virtual ~GL2DDrawingWidget();

//signals:

//public slots:

    virtual void drawContents();
private:
    QList<BallObject*> mScene;
};

#endif // GL2DDRAWINGWIDGET_H
