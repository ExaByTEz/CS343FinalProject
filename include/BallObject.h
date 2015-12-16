#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "QGraphicsEllipseItem"
#include "QKeyEvent"
#include "QPointF"
#include "QColor"

class BallObject:public QGraphicsEllipseItem
{

public:
    BallObject(const QPoint &pP1, const int pID);

    // Set base properties
    void setColor(const QColor &pColor);
    void setRadius(int pRadius);

    // Move or rotate the object
    void translate(double pTx, double pTy);
    void rotate(double pThetaInDegrees);
    void scale(double pSx, double pSy);

    // Reset the transformation to nothing
    void resetTransformation();

    // Getters for all properties
    QColor getColor() const;
    int getRadius() const;

    double getTx() const;
    double getTy() const;

    double getSx() const;
    double getSy() const;

    double getVerticalVelocity();
    double getInitialVelocity();
    double getLossValue();
    double getVerticalAcceleration();

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
    double mLossValue;
    double mCurrentVelocity;
    double mForces;
    double mGravity;
    double mMass;
    double mTimeStep;
    double mHorizontalVelocity;
    double mHorizontalLossValue;

    int mID;

    // The color of this object
    QColor mColor;
};

#endif // BALLOBJECT_H
