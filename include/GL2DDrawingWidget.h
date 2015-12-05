#ifndef GL2DDRAWINGWIDGET_H
#define GL2DDRAWINGWIDGET_H

#include "CGCommon.h"

#include <QGLWidget>
#include <QQueue>
//#include "OpenGLRenderable.h"

class BallObject;

class GL2DDrawingWidget : public QGLWidget
{
    Q_OBJECT

public:
    GL2DDrawingWidget(QWidget *parent = 0, QGLWidget *share = 0);
    virtual ~GL2DDrawingWidget();

    virtual void drawContents();

signals:
    void newPointRequested(const QPoint &pPos);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *pEvent);

public slots:
    void addBall();
    void debugMessage(QString pMsg);

private:
    QList<BallObject*> mScene;
    int mW = 500;
    int mH = 500;
};

#endif // GL2DDRAWINGWIDGET_H
