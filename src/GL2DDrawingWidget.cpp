#include "BallObject.h"

#include "GL2DDrawingWidget.h"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QGLShaderProgram>
#include <QGuiApplication>
#include <QWindow>

GL2DDrawingWidget::GL2DDrawingWidget(QWidget *parent, QGLWidget *share) :
    QGLWidget(QGLFormat(QGL::SingleBuffer | QGL::SampleBuffers), parent, share), OpenGLRenderable(true)
{
    mActiveShapeIndex = -1;

    // For mouse move events and keyboard presses
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

GL2DDrawingWidget::~GL2DDrawingWidget()
{
    while(!mScene.isEmpty())
    {
        delete mScene.last();
        mScene.removeLast();
    }
}

// GL Widget Functions
void GL2DDrawingWidget::initializeGL()
{
    CG_GL_ERROR_CHECK
    OpenGLRenderable::initializeGLRenderable(false);

    CG_GL_ERROR_CHECK
    glDisable(GL_TEXTURE_2D);

    CG_GL_ERROR_CHECK
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    CG_GL_ERROR_CHECK
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    CG_GL_ERROR_CHECK

    glPointSize(1.0);
    glEnable(GL_LINE_SMOOTH);
}


void GL2DDrawingWidget::resizeGL(int pW, int pH)
{
    mW = pW; mH = pH;

    // Accont for hi-DPI displays (Retina Displays)

    if(windowHandle() != NULL)
    {
        double lPixelScale = windowHandle()->devicePixelRatio();
        mW /= lPixelScale;
        mH /= lPixelScale;
    }

    // Setup viewport
    glViewport(0, 0, (GLint)mW, (GLint)mH);

    // Setup Orthographic 2D projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, mW-1, 0.0, mH-1);

    // Identity modelview transform
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GL2DDrawingWidget::paintGL()
{
    // If it's not yet visible don't try and draw (you can upset OpenGL on some systems if you do)
    if(!isVisible()) return;

    CG_GL_ERROR_CHECK

    // Make sure this OpenGL context is current
#ifdef GLCONTEXT_DEBUG
    fprintf(stderr, "Making current (%s:%d)\n", __FILE__, __LINE__);
    fflush(stderr);
#endif
    makeGLContextCurrent();
    CG_GL_ERROR_CHECK

    // Allow special processing before drawContents() (implement in child)
    // Note: buffer clears before but not after, shader is not bound
    if(mShader != NULL) mShader->release();
    CG_GL_ERROR_CHECK
    prePaint();

    CG_GL_ERROR_CHECK

    // Bind the shader and draw the maincontents
    if(mShader != NULL) mShader->bind();
    else glColor4f(0.0, 0.0, 0.0, 1.0);
    drawContents();

    CG_GL_ERROR_CHECK

    // Allow special procesing after drawContents() but before buffer swap (implement in child)
    // Note: shader is not bound
    if(mShader != NULL) mShader->release();
    postPaintPreSwap();

    CG_GL_ERROR_CHECK
}

void GL2DDrawingWidget::drawContents()
{
    // Clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Setup modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();
    glTranslatef(0.5f, 0.5f, 0.0f);

    // Draw the scene one shape at a time
    for(int i=0; i<mScene.size(); i++)
    {
        mScene[i]->predraw();
        mScene[i]->draw();
        mScene[i]->postdraw();
    }

    glPopMatrix();
}

void GL2DDrawingWidget::mouseReleaseEvent(QMouseEvent *pEvent)
{
    // For left-button clicks, signal the request for a new mouse point
    if(pEvent->button() == Qt::LeftButton)
    {
        if(pEvent->pos().x() >= 0 && pEvent->pos().x() < mW &&
           pEvent->pos().y() >= 0 && pEvent->pos().y() < mH)
        {
            emit newPointRequested(qtWidgetCoordsToOpenGLCoords(pEvent->pos()));
        }
    }

    // Pass event up the inheritance chain
    QGLWidget::mouseReleaseEvent(pEvent);
}

inline QPoint GL2DDrawingWidget::qtWidgetCoordsToOpenGLCoords(const QPoint &pPos)
{
    // Invert the Y value by subtracing from 'height'
    return QPoint(pPos.x(), (mH - 1) - pPos.y());
}


void GL2DDrawingWidget::addBall(QPoint pP1)
{

    BallObject *newBall = new BallObject(pP1);
    mScene.push_back((BallObject*)newBall); //Add ball to the scene
    debugMessage(QString("GL2DDrawingWidget: addBall() called, created ball at ") + QString::number(newBall->mCenter.x()) + QString(",") + QString::number(newBall->mCenter.y()));

    updateGL();
}

void GL2DDrawingWidget::updateBall()
{
    //Update every ball
    for(int i=0; i<mScene.size(); i++)
    {
        mScene[i]->update();
    }
    updateGL();
}

void GL2DDrawingWidget::debugMessage(QString pMsg)
{
    qDebug() << pMsg;
}

