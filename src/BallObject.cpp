#include "cgcommon.h"
#include "BallObject.h"
#include <QDataStream>
#include <QDebug>

BallObject::BallObject(const QPoint &pP1, const int pRadius, const double pMass, const double pYvelocity, const int pID)
{
    mTime = 0;
    mVerticalAcceleration  = 0;
    mRadius = pRadius;
    mMass = pMass;
    mCenter = pP1;
    mColor = QColor(255,100,100,255);
    mID = pID;
    mFrame = 0;
    mInitialVelocity = pYvelocity;
    mLossValue = 0.5;
    mCurrentVelocity = pYvelocity;
    mInitialHeight = pP1.y();
}

void BallObject::setColor(const QColor &pColor)
{
    mColor = pColor;
}

void BallObject::setRadius(int pRadius)
{
    mRadius = pRadius;
}

void BallObject::setMass(double pMass)
{
    mMass = pMass;
}

void BallObject::setVerticalVelocity(double pVerticalVelocity)
{
    //mInitialVelocity = pVerticalVelocity;
    mCurrentVelocity = pVerticalVelocity;
}

void BallObject::setGravity(double pGravity)
{
    mVerticalAcceleration = pGravity; //i.e. -9.81 m/s/s by default
}

void BallObject::setTime(double pTime)
{
    mTime = pTime;
}



int BallObject::getRadius() const
{
    return mRadius;
}

double BallObject::getMass() const
{
    return mMass;
}

double BallObject::getTime() const
{
    return mTime;
}



double BallObject::getVerticalVelocity()
{
    return mCurrentVelocity;
    //return mInitialVelocity;
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

void BallObject::postdraw() const
{
    // Restore previous color and polygon fill state
    glPopAttrib();
}

int BallObject::getID()
{
    return mID;
}

//Updates the ball
void BallObject::update()
{

    //Calculate seconds since impact
    mTime = (mFrame * 50.)/1000.; //since update is called every 50 ms, 1000 ms = 1 sec


    // Execute gravity
   // mCurrentVelocity = mCurrentVelocity + mTime * mVerticalAcceleration;
   // mCenter.ry() += mCurrentVelocity;
    mCenter.ry() += mTime*(mInitialVelocity+mVerticalAcceleration*mTime/2);
    mCurrentVelocity = mInitialVelocity + mVerticalAcceleration*mTime;

    //TODO: Check for terminal velocity

    // Iterate up one frame
    mFrame++;
    if(mFrame >= pow(2, 31)-1) mFrame = 0; //Temporary fail safe

    // If ball is below screen at all bounce ball
    if(mCenter.y() - mRadius < 0)
    {
        mCenter.ry() = mRadius;
        mInitialVelocity = -mCurrentVelocity*mLossValue;
        //mCurrentVelocity = -mCurrentVelocity*mLossValue; //temporary
        //mFrame = 0; //will reset the time back to 0

    }
}
