#include "cube.h"
#include<GL/glu.h>
#include<QTimer>
#include<QMouseEvent>

Cube::Cube(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    makeCurrent();
    //Assigning the initial angle values for rotation
	rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
	//Assigning different colors for different sides of the cube.
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::cyan;
    faceColors[4] = Qt::yellow;
    faceColors[5] = Qt::magenta;

}

Cube::~Cube()
{

}

void Cube::initializeGL()
{
qglClearColor(Qt::black);
glShadeModel(GL_FLAT);
glEnable(GL_DEPTH_TEST);
glEnable(GL_CULL_FACE);

//Allows the cube to rotate for certain time.
QTimer *timer = new QTimer(this);
connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
timer->start(20);

}

void Cube::resizeGL(int width, int height)
{
glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

GLfloat x = (GLfloat)width / height;
glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

}

void Cube::paintGL()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
switch(scene)
{
case 'p':
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,400,500);
    draw();
    break;
case 'l':
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,500,400);
    draw();
    break;
default:
    break;
}
}

//funtion to draw the cube on drawing window
void Cube::draw()
{
    static const GLfloat coords[6][4][3] ={
        { { +0.3, -0.3, +0.3 }, { +0.3, -0.3, -0.3 },
        { +0.3, +0.3, -0.3 }, { +0.3, +0.3, +0.3 } },
        { { -0.3, -0.3, -0.3 }, { -0.3, -0.3, +0.3 },
        { -0.3, +0.3, +0.3 }, { -0.3, +0.3, -0.3 } },
        { { +0.3, -0.3, -0.3 }, { -0.3, -0.3, -0.3 },
        { -0.3, +0.3, -0.3 }, { +0.3, +0.3, -0.3 } },
        { { -0.3, -0.3, +0.3 }, { +0.3, -0.3, +0.3 },
        { +0.3, +0.3, +0.3 }, { -0.3, +0.3, +0.3 } },
        { { -0.3, -0.3, -0.3 }, { +0.3, -0.3, -0.3 },
        { +0.3, -0.3, +0.3 }, { -0.3, -0.3, +0.3 } },
        { { -0.3, +0.3, +0.3 }, { +0.3, +0.3, +0.3 },
        { +0.3, +0.3, -0.3 }, { -0.3, +0.3, -0.3 } }
    };
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);

    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);
    for (int i = 0; i < 6; ++i)
    {
        glLoadName(i);
        glBegin(GL_QUADS);
        qglColor(faceColors[i]);
        for (int j = 0; j < 4; ++j)
        {
            glVertex3f(coords[i][j][0], coords[i][j][1],coords[i][j][2]);
        }
        glEnd();
    }


    glPopMatrix();
    glFlush();
}

void Cube::new_size(int val)
{
    resizeGL((val*800)/100,(val*800)/100);
    updateGL();
}

void Cube::rotate()
{
        rotationX+=0.8f;
        rotationY+=0.8f;
        rotationZ+=0.8f;
        draw();
}
