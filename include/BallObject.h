#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "QGraphicsEllipseItem"
#include "QKeyEvent"
#include "QPointF"
#include "QColor"

class BallObject:public QGraphicsEllipseItem
{

public:
    BallObject(const QPoint &pP1);

    void keyPressEvent(QKeyEvent *pEvent); //i.e. when simulation starts

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

    int getRotationAngle() const;

    void update();

    virtual void predraw();
    virtual void draw() const;
    virtual void postdraw();

    double mCenterX() const;
    double mCenterY() const;

    void setMCenterX(double x) const;
    void setMCenterY(double y) const;

    QPointF getMCenter() const;



protected:
    int mRadius;

    // The components of the transformations
    double mTx;
    double mTy;
    double mVerticalAcceleration;
    double mThetaInDegrees;
    double mSx;
    double mSy;
    int mFrame;
    double mInitialVelocity;
    double mLossValue;
    double mCurrentVelocity;

    // The color of this object
    QColor mColor;
        QPointF mCenter; //Move to protected
};

#endif // BALLOBJECT_H
