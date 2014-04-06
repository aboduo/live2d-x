#include "CCSprite.h"

CCSprite::CCSprite()
    :m_pobTexture(NULL)
{
//    QGLShader * vertex_shader = new QGLShader(QGLShader::Vertex);
//    QGLShader * frag_shader = new QGLShader(QGLShader::Fragment);
//    if(!vertex_shader->compileSourceFile(":/shader/vshader.glsl"))
//    {
//        Q_ASSERT(0);
//    }
//    if(!frag_shader->compileSourceFile(":/shader/fshader.glsl"))
//    {
//        Q_ASSERT(0);
//    }
//    m_program = new QGLShaderProgram();
//    m_program->addShader(vertex_shader);
//    m_program->addShader(frag_shader);
//    m_program->link();
//    m_program->bind();
    
    m_pobTexture = new Texture();
    m_pobTexture->m_name=0;
    m_pobTexture->width = 0;
    m_pobTexture->height = 0;
}

CCSprite::~CCSprite()
{
    if(m_pobTexture) delete m_pobTexture;
}

bool CCSprite::initWithFile(const char* path)
{
    
//    glEnable(GL_TEXTURE_2D);
    //这里用QT的数据初始化一个Texture指针
    QImage tex,buf;
    if(!buf.load(path))
    {
        qWarning("没找到图片");
        QImage dummy(128,128,QImage::Format_ARGB32);
        dummy.fill(Qt::green);
        buf = dummy;
    }
    tex = QGLWidget::convertToGLFormat(buf);
    
    //创建一个纹理,并指定其地址为--
    glGenTextures(1,&m_pobTexture->m_name);
    
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D,m_pobTexture->m_name);
    
    //正式创建纹理
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,tex.width(),tex.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,tex.bits());
    
    //设置纹理缩放显示时的模式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    return true;
}
