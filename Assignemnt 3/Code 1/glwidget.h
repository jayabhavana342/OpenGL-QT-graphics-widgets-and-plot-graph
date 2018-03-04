#ifndef GLWIDGET_H
#define GLWIDGET_H

#include<QColor>
#include<QtWidgets>
#include<QGLWidget>
#include<QtOpenGL/QGLWidget>
class glwidget : public QGLWidget
{
public:
    glwidget(QWidget *parent=0);

    QColor faceColors[6];

    char scene;
protected:
    void initializeGL();
    void resizeGL(int width,int height);
    void paintGL();

private:
    void draw();

};

#endif // GLWIDGET_H
