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
//    ui->view_area_scroll->setWidgetResizable(false);
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
    QRect rect = ui->view_area_glwidget->visibleRegion().boundingRect();
    *left = -rect.left();
    *bottom = rect.height() - ui->view_area_glwidget->geometry().height() + rect.top();
}


void EditorWindow::on_pushButton_2_clicked()
{
    ui->view_area_glwidget->m_primary->runAnimation("ruyao");
}
