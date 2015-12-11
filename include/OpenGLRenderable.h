#ifndef OPENGLRENDERABLE_H
#define OPENGLRENDERABLE_H

#include "CGCommon.h"
#include <QString>

class QGLShaderProgram;

class OpenGLRenderable
{
public:
    OpenGLRenderable(double pFOV = GENERAL_FOV, double pNear = 0.1, double pFar = 100.0);
    OpenGLRenderable(bool p2DContent);
    ~OpenGLRenderable();

    // General function to read and compile a shader
    static void initShader(QGLShaderProgram* &pShader, const QString &pVTXShader, const QString &pFRGShader, bool pWithTans);

protected:
    // Camera parameters
    double mHorizFOV;
    double mNear;
    double mFar;
    bool mOrtho2D;

    // Last seen width and height from resizeGL()
    int mW;
    int mH;

    // GLSL Shader
    QGLShaderProgram* mShader;

    // Implement this in your child if you don't want to use the
    // currently enabled context or your child has it's own context.
    virtual bool makeGLContextCurrent() { return true; }

    // Internal OpenGL Initialization
    virtual void initializeGLRenderable(bool pAllowAliasing);
    virtual void resizeGLRenderable(int w, int h);
    virtual void initShader(const QString &pVTXShader, const QString &pFRGShader, bool pWithTans = false);

    // Customize for your shader (if any)
    virtual void setShaderDefaults() {}
};
#endif // OPENGLRENDERABLE_H
