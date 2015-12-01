#include "cgcommon.h"
#include "BallObject.h"

BallObject::BallObject()
{
    mRadius = 5;
    mTx = 100;
    mTy = 100;
    mColor = QColor(255,0,0,255);
}

/*
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
*/
