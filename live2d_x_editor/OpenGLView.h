#ifndef OPENGLVIEW_H
#define OPENGLVIEW_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QBasicTimer>
#include <QResizeEvent>
#include "../live2d_x/sources/Live2dXSprite.h"

class Live2dXSprite;
class OpenGLView:public QGLWidget, protected QGLFunctions
{
    Q_OBJECT
public:
    OpenGLView(QWidget* parent=NULL);
    bool loadImages(const QString& imagepath,const QString& configPath);
protected:
    virtual void timerEvent(QTimerEvent *);
    virtual void initializeGL();
    virtual void paintGL();
//    virtual void resizeGL(int w, int h);
//    virtual void resizeEvent(QResizeEvent *);
public:
    Live2dXSprite* m_primary;
    QBasicTimer timer;
};

#endif // OPENGLVIEW_H
