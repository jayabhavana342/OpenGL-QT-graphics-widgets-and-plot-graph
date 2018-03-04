#ifndef CUBE_H
#define CUBE_H

#include <QGLWidget>
#include <QtWidgets>
class Cube : public QGLWidget
{
    Q_OBJECT

public:
    Cube(QWidget *parent = 0);
    void orient(char scene);
    void rotate(int val);
    void Scale(int val);
    ~Cube();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    float sx;
    float sy;
    float sz;
    QColor faceColors[6];


};

#endif // CUBE_H
