#include "cgcommon.h"
#include "BallObject.h"
#include <QDataStream>


BallObject::BallObject()
{
    mVerticalVelocity = -2.4;
    mRadius = 5;
    mTx = 25;
    mTy = 25;
    mColor = QColor(255,0,0,255);
}

//test comment
void BallObject::keyPressEvent(QKeyEvent *pEvent)
{
    if(pEvent->key() == Qt::Key_Space)
    {
        setPos(x(), y()-mVerticalVelocity);
    }
}


void BallObject::predraw() const
{
    // Save the curent color and polygon fill state
    glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

    // Set current OpenGL color and fill mode
    glColor3ub(mColor.red(), mColor.green(), mColor.blue());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BallObject::draw() const
{
    glBegin(GL_LINE_LOOP);

    for(int i = 0; i < 360; i++)
    {
        //TODO: Change to center instead of x and y
        glVertex2f(mTx + cos(i*(M_PI/180))*mRadius, mTy + sin(M_PI/180)*mRadius);
    }

    glEnd();
}

void BallObject::postdraw() const
{
    // Restore previous color and polygon fill state
    glPopAttrib();
}

