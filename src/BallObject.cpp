#include "cgcommon.h"
#include "BallObject.h"
#include <QDataStream>
#include <QDebug>

BallObject::BallObject(const QPoint &pP1, const int pID)
{
    mRadius = 20;
    mCenter = pP1;
    mColor = QColor(255,100,100,255);
    mID = pID;
    mFrame = 0;
    mInitialVelocity = 0;
    mLossValue = 0.8;
    mCurrentVelocity = 0;
    mForces = 0;
    mGravity = 5;
    mTimeStep = 0.01;
    mMass = 1;
    mHorizontalVelocity = .1;
    mHorizontalLossValue = 1;
}

void BallObject::setColor(const QColor &pColor)
{
    mColor = pColor;
}

double BallObject::getVerticalVelocity()
{
    return mCurrentVelocity;
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
    /*if(mCenter.y() < mRadius)
    {
        mCenter.ry() = mRadius;
    }
    else
    {
        mForces += -mMass*mGravity;
    }
    mVerticalAcceleration = mForces / mMass;
    mFrame += mTimeStep;
    mCurrentVelocity += mFrame * mVerticalAcceleration;
    mCenter.ry() += (mFrame * mCurrentVelocity);


    if(mCenter.x()< mRadius || mCenter.x() > 500-mRadius)
    {
        mHorizontalVelocity = -(mHorizontalVelocity*mHorizontalLossValue);
    }
    else
    {
        mHorizontalVelocity = (mHorizontalVelocity*mHorizontalLossValue);
    }
    mCenter.rx() = mCenter.x()+mHorizontalVelocity/mTimeStep;*/

        mForces += -mMass*mGravity;
        mVerticalAcceleration = mForces / mMass;
        mFrame += mTimeStep;
        if(mCenter.y() < mRadius)
        {
            mCurrentVelocity = -mCurrentVelocity*mLossValue;
        }
        else
        {
            mCurrentVelocity += mFrame * mVerticalAcceleration;
        }

        mCenter.ry() += (mFrame * mCurrentVelocity);


        if(mCenter.x()< mRadius || mCenter.x() > 500-mRadius)
        {
            mHorizontalVelocity = -(mHorizontalVelocity*mHorizontalLossValue);
        }
        else
        {
            mHorizontalVelocity = (mHorizontalVelocity*mHorizontalLossValue);
        }
        mCenter.rx() = mCenter.x()+mHorizontalVelocity/mTimeStep;
}
