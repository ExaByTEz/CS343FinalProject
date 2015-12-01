/*
 * CGCommon.h
 *
 * A general header file for use with computer graphics projects that
 * includes and defines a lot of commonly used stuff.
 */

#ifndef CGCOMMON_H_
#define CGCOMMON_H_

// Ensure PI and other constants get defined on microsoft compiler
#ifdef _MSC_VER
    #define _USE_MATH_DEFINES
#endif

// Needed throughout most C/C++ programs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <csignal>

// STL includes needed pretty much everywhere
#include <string>

// Fixed precision integer types (and the macros for use with printf)
#ifndef __STDC_FORMAT_MACROS
    #define __STDC_FORMAT_MACROS
#endif

// For Visual Studio ONLY
#ifdef _MSC_VER
    // Need a special header for Microsoft compiler
    //#include "msinttypes.h"
#else
    #include <inttypes.h>
#endif

// This must happen before glu on windows (both MS and MinGW)
#ifdef _WIN32
    #include <windows.h>
#endif

// Some handy utilities for OpenGL
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

// Because msvc is silly
#ifndef GL_MULTISAMPLE
    #define GL_MULTISAMPLE                    0x809D
#endif

// Because these should exist (but don't on many systems)
#ifndef MAX
#define MAX(X, Y) ((X)>(Y)?(X):(Y))
#endif

#ifndef MIN
#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#endif

// A nice default Field-of-view for projections
// (Corresponds to 35mm focal length on a 32mm film size)
#define GENERAL_FOV      49.13

// Easy macro for checking and printing the OpenGL error state
// (and possibly aborting when one has occured)
#define CG_BREAK_ON_GL_ERROR   false
#define CG_GL_ERROR_CHECK   { \
        int lGLErrorCode = glGetError(); \
        if(lGLErrorCode != GL_NO_ERROR) \
        { \
            printf("OpenGL Error @ %s(%d): %s\n", __FILE__, __LINE__, gluErrorString(lGLErrorCode)); \
            fflush(stdout); \
            if(CG_BREAK_ON_GL_ERROR) ::raise(SIGABRT); \
        } \
    }

#endif /* CGCOMMON_H_ */
