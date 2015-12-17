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
    mHorizontalVelocity = .001;
    mHorizontalLossValue = .999;
    mForces = 0;
    mMass = 10;
    mGravity = 0; //Set externally from GL2DDrawingWidget
}

// Retrieve the ball's color
void BallObject::setColor(const QColor &pColor)
{
    mColor = pColor;
}

// Set the ball's radius
void BallObject::setRadius(int pRadius)
{
    mRadius = pRadius;
}

// Set the ball's mass
void BallObject::setMass(double pMass)
{
    mMass = pMass;
}

// Set the ball's vertical velocity
void BallObject::setVerticalVelocity(double pVerticalVelocity)
{
    //mInitialVelocity = pVerticalVelocity;
    mCurrentVelocity = pVerticalVelocity;
}

// Set The value for Gravity
void BallObject::setGravity(double pGravity)
{
    mGravity = pGravity; //i.e. -9.81 m/s/s by default
}

// Set the current time or the ball
void BallObject::setTime(double pTime)
{
    mTime = pTime;
}

// Set the ball's horizontal velocity
void BallObject::setHorizontalVelocity(double pHorizontalVelocity)
{
    mHorizontalVelocity = pHorizontalVelocity;
}

// Set the amount by which time iterates up
void BallObject::setTimeStep(double pTimeStep)
{
    mTimeStep = pTimeStep;
}

// Retrieve the ball's radius
int BallObject::getRadius() const
{
    return mRadius;
}

// Retrieve the ball's mass
double BallObject::getMass() const
{
    return mMass;
}

// Retrieve the current time
double BallObject::getTime() const
{
    return mTime;
}

// Retrieve the vertical velocity
double BallObject::getVerticalVelocity()
{
    return mCurrentVelocity;
    //return mInitialVelocity;
}

// Retrieve the loss value
double BallObject::getLossValue()
{
    return mLossValue;
}

// Retrieve the vertical acceleration
double BallObject::getVerticalAcceleration()
{
    return mVerticalAcceleration;
}

// Retrieve the horizontal velocity
double BallObject::getHorizontalVelocity()
{
    return mHorizontalVelocity;
}

// Retrieve the timestep value
double BallObject::getTimeStep()
{
    return mTimeStep;
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
    // Calculate forces based on gravity
    mForces = -mMass*mGravity;
    mVerticalAcceleration = mForces / mMass;

    // Update the time by the timestep
    mTime += mTimeStep;

    // If ball hits the floor, reverse the direction and reduce by the loss value
    if(mCenter.y() < 2*mRadius)
    {
        mCurrentVelocity = -mCurrentVelocity*mLossValue;
    }
    else
    {
        mCurrentVelocity += mTime * mVerticalAcceleration;
    }

    // Update vertical component's position
    mCenter.ry() += mTime * mCurrentVelocity;

    // If the ball hits one of the sides, bounce it off
    if(mCenter.x()< mRadius || mCenter.x() > 500-mRadius)
    {
        mHorizontalVelocity = -(mHorizontalVelocity*mHorizontalLossValue);
    }

    // Otherwise, just move the horizontal componenet
    else
    {
        mHorizontalVelocity = (mHorizontalVelocity*mHorizontalLossValue);
    }
    // Add the new distance to the horizontal ball movement
    mCenter.rx() = mCenter.x()+mHorizontalVelocity/mTimeStep;

    // If the ball is moving slow enough in the horizontal direction, just stop it
    if(abs(mCurrentVelocity) <= 0.02 && mCenter.y() < mRadius)
    {
        mCurrentVelocity = 0;
    }
}
