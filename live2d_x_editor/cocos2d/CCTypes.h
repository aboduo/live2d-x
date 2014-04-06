#ifndef CCTYPES_H
#define CCTYPES_H

#include <QOpenGLFunctions>
#include <QDataStream>
#include <QTextStream>
#include <QSize>
#include <QGLWidget>
#include <QGLFunctions>
#include <QTime>
#include <QFile>
#include <QGLShaderProgram>
#include <QGLShader>
#include <QDebug>

#include <math.h>

enum {
    kCCVertexAttrib_Position,
    kCCVertexAttrib_Color,
    kCCVertexAttrib_TexCoords,

    kCCVertexAttrib_MAX,
};


typedef struct _ccTex2F {
     GLfloat u;
     GLfloat v;
} ccTex2F;
typedef struct _ccColor4B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
} ccColor4B;

static inline ccColor4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
    ccColor4B c = {r, g, b, o};
    return c;
}

typedef struct _ccVertex3F
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
} ccVertex3F;


struct CCSize
{
    float width;
    float height;
};

#define CC_ASSERT(o) Q_ASSERT(o)
#define CCAssert(a,b) Q_ASSERT_X(a,b,"")

#define CC_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define CC_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define CC_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define CC_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define CC_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)
#define CC_BREAK_IF(cond)            if(cond) break

#define NS_CC_BEGIN
#define NS_CC_END
#define CC_UNUSED_PARAM
#define CCRANDOM_0_1() ((float)rand()/RAND_MAX)
#define CCLOG

#define CC_GL_DEPTH24_STENCIL8      -1


#define glDeleteVertexArrays            glDeleteVertexArraysAPPLE
#define glGenVertexArrays               glGenVertexArraysAPPLE
#define glBindVertexArray               glBindVertexArrayAPPLE

#endif // CCTYPES_H
