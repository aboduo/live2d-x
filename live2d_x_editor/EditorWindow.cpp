#include "EditorWindow.h"
#include "ui_EditorWindow.h"

EditorWindow::EditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorWindow)
{
    ui->setupUi(this);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

static QTimer* timer = NULL;
void EditorWindow::on_pushButton_clicked()
{
    ui->widget->loadImages(":/image/temp.jpg",
                           ":/image/temp.plist");
//    ui->widget->repaint();
}

void EditorWindow::setSizeOrgin(int w,int h)
{
    ui->scrollArea->setMinimumSize(w,h);
}

void EditorWindow::on_pushButton_2_clicked()
{
    ui->widget->m_primary->runAnimation("ruyao");
}
