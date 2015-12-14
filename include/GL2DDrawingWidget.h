#ifndef GL2DDRAWINGWIDGET_H
#define GL2DDRAWINGWIDGET_H

#include "CGCommon.h"

#include <QGLWidget>
#include <QQueue>
#include <QTimer>
#include "OpenGLRenderable.h"

class BallObject;

class GL2DDrawingWidget : public QGLWidget, OpenGLRenderable
{
    Q_OBJECT

public:
    GL2DDrawingWidget(QWidget *parent = 0, QGLWidget *share = 0);
    virtual ~GL2DDrawingWidget();
    void updateGravity(double pValue);
    void debugMessage(QString pMsg);
    BallObject* getBall(int pIndex);


signals:
    void newPointRequested(const QPoint &pPos);

protected:
    // QGLWidget overloaded functions
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mouseReleaseEvent(QMouseEvent *pEvent);

public slots:
    void addBall(QPoint pP1, int pRadius, double pMass, double pYvelocity, int pID);
    void updateBall();

private:
    // OpenGLRenderable overloaded functions
    virtual bool makeGLContextCurrent() { makeCurrent(); return true; }

    // Child widget should re-implement these as needed
    virtual void setupWidget() {}
    virtual void prePaint() {}
    virtual void postPaintPreSwap() {}

    virtual void drawContents();
    QList<BallObject*> mScene;
    int mActiveShapeIndex;
    int mW = 500;
    int mH = 500;
    QTimer *mIdleTimer;

    // Helper functions
    inline QPoint qtWidgetCoordsToOpenGLCoords(const QPoint &pPos);
};

#endif // GL2DDRAWINGWIDGET_H
