#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "QPointF"
#include "QColor"

class BallObject
{
public:
    BallObject();

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

    //virtual void predraw() const;
    //virtual void draw() const;
    //virtual void postdraw() const;

protected:
    QPointF mCenter;

    // What is the object's radius? (only makes sense for a circle)
    int mRadius;

    // The components of the transformations
    double mTx, mTy;
    double mThetaInDegrees;
    double mSx, mSy;

    // The color of this object
    QColor mColor;

//signals:

//public slots:
};

#endif // BALLOBJECT_H
