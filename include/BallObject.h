#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "QGraphicsEllipseItem"
#include "QKeyEvent"
#include "QPointF"
#include "QColor"

class BallObject:public QGraphicsEllipseItem
{

public:
    BallObject(const QPoint &pP1, const int pRadius, const double pMass, const double pYvelocity, const int pID);

    // Set base properties
    void setColor(const QColor &pColor);
    void setRadius(int pRadius);
    void setMass(double pMass);
    void setVerticalVelocity(double pVerticalVelocity);
    void setGravity(double pGravity);
    void setTime(double pTime);

    // Move or rotate the object
    void translate(double pTx, double pTy);
    void rotate(double pThetaInDegrees);
    void scale(double pSx, double pSy);

    // Reset the transformation to nothing
    void resetTransformation();

    // Getters for all properties
    QColor getColor() const;
    int getRadius() const;
    double getMass() const;

    double getTx() const;
    double getTy() const;

    double getSx() const;
    double getSy() const;

    double getTime() const;

    double getVerticalVelocity();

    int getRotationAngle() const;

    void update();

    virtual void predraw() const;
    virtual void draw() const;
    virtual void postdraw() const;

    int getID();

    QPointF mCenter; //Move to protected
protected:
    int mRadius;

    // The components of the transformations
    double mTx;
    double mTy;
    double mVerticalAcceleration;
    double mThetaInDegrees;
    double mSx;
    double mSy;
    double mFrame;
    double mInitialVelocity;
    double mLossValue;
    double mCurrentVelocity;
    double mMass;
    double mForces;
    double mGravity;
    double mTimeStep;
    double mHorizontalVelocity;
    double mHorizontalLossValue;
    int mID;

    // The color of this object
    QColor mColor;

private:
    double mTime;
    double mInitialHeight;
};

#endif // BALLOBJECT_H
