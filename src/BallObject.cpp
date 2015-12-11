#include "cgcommon.h"
#include "BallObject.h"
#include <QDataStream>
#include <QDebug>

BallObject::BallObject(const QPoint &pP1, const int pID)
{
    mVerticalAcceleration  = -1-(qrand() % 9); //random velocity
    mRadius = 20;
    mCenter = pP1;
    mColor = QColor(255,100,100,255);
    mID = pID;
    mFrame = 0;
    mInitialVelocity = 0;
    mLossValue = 0.5;
    mCurrentVelocity = 0;

}

void BallObject::setColor(const QColor &pColor)
{
    mColor = pColor;
}

double BallObject::getVerticalVelocity()
{
    return mCurrentVelocity;
}


void BallObject::predraw()
{
    // Save the curent color and polygon fill state
    glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

    // Execute gravity
    mCenter.ry() += mFrame*(mInitialVelocity+mVerticalAcceleration*mFrame/2);
    mCurrentVelocity = mInitialVelocity + mVerticalAcceleration*mFrame;

    // Set current OpenGL color and fill mode
    glColor3ub(mColor.red(), mColor.green(), mColor.blue());
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BallObject::draw() const
{
    // Approximate a circle with a bunch of triangles/line segments
    glBegin(GL_TRIANGLE_FAN);

    // Start with the center
    QPointF lPoint = mCenter;

    glVertex2d(lPoint.x(), lPoint.y());

    // Rotate around the circle adding triangles/line segments

    for(int lTheta = 0; lTheta <= 360; lTheta++)
    {
        double angle = lTheta/180.0*M_PI;
        QPointF lBefore(mCenter.x() + sin(angle)*mRadius, mCenter.y() + cos(angle)*mRadius);
        lPoint = lBefore;
        glVertex2d(lPoint.x(), lPoint.y());
    }

    glEnd();
}

void BallObject::postdraw()
{
    // Restore previous color and polygon fill state
    glPopAttrib();

    // Iterate up one frame
    mFrame++;

    // If ball is below screen at all bounce ball
    if(mCenter.y() - mRadius < 0)
    {
        mCenter.ry() = mRadius;
        mInitialVelocity = -mCurrentVelocity*mLossValue;
        mFrame = 0;

    }
}

int BallObject::getID()
{
    return mID;
}

//Updates the ball
void BallObject::update()
{
    //Only move the ball down until it reaches the edge of the screen for now
    //Note: Bottom Left (x, y) = (0, 0)
    if(mCenter.y() - mRadius + mCurrentVelocity > 0)
    {
        //qDebug() << "BallObject: ("+ QString::number(mCenter.x() + mRadius) + ","+QString::number(mCenter.y() + mRadius) + ")";
        mCenter.ry() += mCurrentVelocity;
    }
    else
    {
        double distToGround = mCenter.y() - mRadius;
        //qDebug() << "BallObject: Distance to ground before collision: " + QString::number(distToGround);
        //mVerticalVelocity *= -1;
    }
}
