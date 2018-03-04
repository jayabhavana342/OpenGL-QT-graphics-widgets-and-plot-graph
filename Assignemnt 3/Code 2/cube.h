#ifndef CUBE_H
#define CUBE_H

#include <QGLWidget>
#include <QtWidgets>
class Cube : public QGLWidget
{
    Q_OBJECT

public:
    Cube(QWidget *parent = 0);
    //A variable named scene for Cube Orientation.
	char scene;
	//function for resizing the cube.
    void new_size(int val);
    //function for rotating the cube.
	void rotate();
    ~Cube();
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[6];
    QPoint lastPos;

};

#endif // CUBE_H
