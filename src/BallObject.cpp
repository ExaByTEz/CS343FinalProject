#include "cgcommon.h"
#include "BallObject.h"
#include <QDataStream>
#include <QDebug>

BallObject::BallObject(const QPoint &pP1, const int pRadius, const double pMass, const double pInitialYvelocity, const int pID)
{
    mTime = 0;
    mVerticalAcceleration  = 0;
    mRadius = pRadius;
    mMass = pMass;
    mCenter = pP1;
    mColor = QColor(255,100,100,255);
    mID = pID;
    mInitialHeight = pP1.y();
    mLossValue = 0.8;
    mCurrentVelocity = pInitialYvelocity;
    mForces = 0;
    mTimeStep = 0.001;
    mMass = 1;
    mHorizontalVelocity = .009;
    mHorizontalLossValue = .999;
    mForces = 0;
    mMass = 10;
    mGravity = 0; //Set externally from GL2DDrawingWidget
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
    mGravity = pGravity; //i.e. -9.81 m/s/s by default
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

double BallObject::getLossValue()
{
    return mLossValue;
}

double BallObject::getVerticalAcceleration()
{
    return mVerticalAcceleration;
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
        mForces += -mMass*mGravity;
        mVerticalAcceleration = mForces / mMass;
        mTime += mTimeStep;
        if(mCenter.y() < 2*mRadius)
        {
            mCurrentVelocity = -mCurrentVelocity*mLossValue;
        }
        else
        {
            mCurrentVelocity += mTime * mVerticalAcceleration;
        }

        mCenter.ry() += (mTime * mCurrentVelocity);


        if(mCenter.x()< mRadius || mCenter.x() > 500-mRadius)
        {
            mHorizontalVelocity = -(mHorizontalVelocity*mHorizontalLossValue);
        }
        else
        {
            if(mHorizontalVelocity <= 0.0001)
            {
                mHorizontalVelocity = 0;
            }
            else
            {
                mHorizontalVelocity = (mHorizontalVelocity*mHorizontalLossValue);
            }
        }
        mCenter.rx() = mCenter.x()+mHorizontalVelocity/mTimeStep;


}
