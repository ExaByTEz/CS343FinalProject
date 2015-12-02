#include "BallObject.h"
#include "GL2DDrawingWidget.h"

GL2DDrawingWidget::GL2DDrawingWidget(QWidget *parent, QGLWidget *share) :
    QGLWidget(QGLFormat(QGL::SingleBuffer | QGL::SampleBuffers), parent, share)
{
    //mActiveShapeIndex = -1;

    // For mouse move events and keyboard presses
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    //Temp, add ball object to scene
    BallObject *newBall = new BallObject();
    mScene.push_back((BallObject*)newBall);
}

GL2DDrawingWidget::~GL2DDrawingWidget()
{
    //while(!mScene.isEmpty())
   // {
    //    delete mScene.last();
    //    mScene.removeLast();
   // }
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
