#include "OpenGLView.h"
#include "EditorWindow.h"

OpenGLView::OpenGLView(QWidget* parent)
    :QGLWidget(parent)
{
//    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    m_primary = new Live2dXSprite();
}

bool OpenGLView::loadImages(const QString& imagepath,const QString& configPath)
{
    m_primary->initWithConfig(configPath.toStdString().c_str());
    timer.start(1000/30.0f,this);
}

void OpenGLView::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    repaint();
}

static GLuint m_id=0;
void OpenGLView::initializeGL()
{
//    loadImages(":/image/temp.jpg",":image/temp.plist");
    //这里用QT的数据初始化一个Texture指针
    QImage tex,buf;
    if(!buf.load(":/image/temp.jpg"))
    {
        qWarning("没找到图片");
        QImage dummy(128,128,QImage::Format_ARGB32);
        dummy.fill(Qt::green);
        buf = dummy;
    }
    tex = QGLWidget::convertToGLFormat(buf);
        
    //创建一个纹理,并指定其地址为--
    glGenTextures(1,&m_id);
    
    //绑定纹理
    glBindTexture(GL_TEXTURE_2D,m_id);
    
    //正式创建纹理
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,tex.width(),tex.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,tex.bits());
    
//    ((EditorWindow*)window())->setSizeOrgin(tex.width(),tex.height());
    //设置纹理缩放显示时的模式
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    m_primary->m_pobTexture->m_name = m_id;
    setGeometry(0,0,tex.width(),tex.height());
    setMinimumSize(tex.width(),tex.height());
    setMaximumSize(tex.width(),tex.height());
    glEnable(GL_TEXTURE_2D);
     
    //启用阴影平滑
    glShadeModel(GL_SMOOTH);
    
    //初始化底板颜色RGBA
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    
    //设置深度缓存
    glClearDepth(1.0f);
    //启用深度测试
    glEnable(GL_DEPTH_TEST);
    //设置深度测试类型
    glDepthFunc(GL_LEQUAL);
    //上面三行是必须的,是关于深度缓存depath buffer的,它影响哪个先画哪个后画
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.1f);
}

void OpenGLView::paintGL()
{
    //清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //重置当前的模型观察矩阵
    glLoadIdentity();
    int left,top,right,bottom;
    EditorWindow::getInstance()->getGLWidgetOffset(&left,&top,&right,&bottom);
    glViewport(left,bottom,m_primary->getBaseSize().width,m_primary->getBaseSize().height);
    
    m_primary->draw();
}

