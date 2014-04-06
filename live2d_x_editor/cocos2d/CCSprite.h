#ifndef CCSPRITE_H
#define CCSPRITE_H

#include "CCObject.h"
#include "CCTypes.h"

struct Texture
{
    GLuint m_name;
    float height;
    float width;
};

class CCSprite : public CCObject
{
public:
    CCSprite();
    ~CCSprite();
    bool initWithFile(const char* path);
public:
    Texture* m_pobTexture;
    QGLShaderProgram* m_program;
};

#endif // CCSPRITE_H
