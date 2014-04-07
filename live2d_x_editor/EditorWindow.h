#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();
    static EditorWindow* getInstance();
    void setSizeOrgin(int,int);
    void getGLWidgetOffset(int *left, int *top, int *right, int *bottom);
private slots:
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
private:
    Ui::EditorWindow *ui;
};

#endif // EDITORWINDOW_H
