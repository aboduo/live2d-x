#include "EditorWindow.h"
#include "ui_EditorWindow.h"

static EditorWindow* _instace = 0;

EditorWindow* EditorWindow::getInstance()
{
    return _instace;
}

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
    _instace = this;
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

static QTimer* timer = NULL;
void EditorWindow::on_pushButton_clicked()
{
    ui->view_area_glwidget->loadImages(":/image/temp.jpg",
                           ":/image/temp.plist");
//    ui->widget->repaint();
}

void EditorWindow::setSizeOrgin(int w,int h)
{
    ui->view_area_scroll->setMinimumSize(w,h);
}

void EditorWindow::getGLWidgetOffset(int *left, int *top, int *right, int *bottom)
{
    ui->view_area_scroll->getContentsMargins(left,top,right,bottom);
}


void EditorWindow::on_pushButton_2_clicked()
{
    ui->view_area_glwidget->m_primary->runAnimation("ruyao");
}
