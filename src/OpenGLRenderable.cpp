#include "OpenGLRenderable.h"
#include <QGLShaderProgram>


OpenGLRenderable::OpenGLRenderable(double pFOV, double pNear, double pFar)
{
    mShader = NULL;

    mW = -1;
    mH = -1;
    mHorizFOV = pFOV;
    mNear = pNear;
    mFar = pFar;

    mOrtho2D = false;
}

OpenGLRenderable::OpenGLRenderable(bool p2DContent)
{
    if(!p2DContent) OpenGLRenderable();
    else
    {
        mW = -1;
        mH = -1;
        mShader = NULL;
        mHorizFOV = 0.0;
        mNear = 0.0;
        mFar = 0.0;
        mOrtho2D = true;
    }
}

OpenGLRenderable::~OpenGLRenderable()
{
    if(mShader != NULL) delete mShader;
}

void OpenGLRenderable::initializeGLRenderable(bool pAllowAliasing)
{
    // Basic OpenGL setup
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);

    if(!pAllowAliasing) glEnable(GL_MULTISAMPLE);
    else glDisable(GL_MULTISAMPLE);

    if(!mOrtho2D) glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderable::resizeGLRenderable(int w, int h)
{
    mW = w;
    mH = h;

    // Setup Viewport
    glViewport(0, 0, mW, mH);

    // Setup projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(mOrtho2D) gluOrtho2D(-mW/2.0, mW/2.0, -mH/2.0, mH/2.0);
    else
    {
        // Setup OpenGL projection Matrix
        double lAspect = mW/(double)mH;
        gluPerspective(mHorizFOV/lAspect, lAspect, mNear, mFar);
    }

    // Clean model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLRenderable::initShader(const QString &pVTXShader, const QString &pFRGShader, bool pWithTans)
{
    initShader(mShader, pVTXShader, pFRGShader, pWithTans);

    // Set default values
    setShaderDefaults();
}

void OpenGLRenderable::initShader(QGLShaderProgram* &pShader, const QString &pVTXShader, const QString &pFRGShader, bool pWithTans)
{
    // Make shader
    if(pShader != NULL) delete pShader;

    pShader = new QGLShaderProgram();

    if(pShader == NULL) return;

    // Compile and link
    if(!pShader->addShaderFromSourceFile(QGLShader::Vertex, pVTXShader) ||
       !pShader->addShaderFromSourceFile(QGLShader::Fragment, pFRGShader))
    {
        printf("Shader Compilation Error:\n%s\n", pShader->log().toLatin1().data());
        fflush(stdout);
        delete pShader;
        pShader = NULL;
        return;
    }

    if(pWithTans) pShader->bindAttributeLocation("tangent", 1);

    if(!pShader->link())
    {
        printf("Shader Linking Error:\n%s\n", pShader->log().toLatin1().data());
        fflush(stdout);
        delete pShader; pShader = NULL;
        return;
    }
}
