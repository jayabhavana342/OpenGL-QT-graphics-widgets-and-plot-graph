#include "cube.h"
#include<GL/glu.h>
#include<QTimer>
#include<QMouseEvent>

Cube::Cube(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::cyan;
    faceColors[4] = Qt::yellow;
    faceColors[5] = Qt::magenta;
    sx=1.5;
    sy=1.5;
    sz=1.5;

}

Cube::~Cube()
{

}

void Cube::initializeGL()
{
qglClearColor(Qt::black);
glClearDepth(1.0f);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
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

static const GLfloat coords[6][4][3] ={
    { { +0.2, -0.2, +0.2 }, { +0.2, -0.2, -0.2 },
    { +0.2, +0.2, -0.2 }, { +0.2, +0.2, +0.2 } },
    { { -0.2, -0.2, -0.2 }, { -0.2, -0.2, +0.2 },
    { -0.2, +0.2, +0.2 }, { -0.2, +0.2, -0.2 } },
    { { +0.2, -0.2, -0.2 }, { -0.2, -0.2, -0.2 },
    { -0.2, +0.2, -0.2 }, { +0.2, +0.2, -0.2 } },
    { { -0.2, -0.2, +0.2 }, { +0.2, -0.2, +0.2 },
    { +0.2, +0.2, +0.2 }, { -0.2, +0.2, +0.2 } },
    { { -0.2, -0.2, -0.2 }, { +0.2, -0.2, -0.2 },
    { +0.2, -0.2, +0.2 }, { -0.2, -0.2, +0.2 } },
    { { -0.2, +0.2, +0.2 }, { +0.2, +0.2, +0.2 },
    { +0.2, +0.2, -0.2 }, { -0.2, +0.2, -0.2 } }
};
glMatrixMode(GL_MODELVIEW);

glLoadIdentity();
glTranslatef(0.0, 0.0, -10.0);
glRotatef(rotationX, 1.0, 0.0, 0.0);
glRotatef(rotationY, 0.0, 1.0, 0.0);
glRotatef(rotationZ, 0.0, 0.0, 1.0);
glScalef(sx,sy,sz);

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
    //drawing a triangle
   glBegin(GL_TRIANGLES);
   glColor3f(1.0f,0.0f,0.0f);
   glVertex3f(-0.6,0.8,0.0);
   glColor3f(0.0f,1.0f,0.0f);
   glVertex3f(-0.8,0.6,0.0);
   glColor3f(0.0f,0.0f,1.0f);
   glVertex3f(-0.4,0.6,0.0);
   glEnd();

   //drawing a line
glBegin(GL_LINES);
glLineWidth(2.0f);
glColor3f(1.0f,1.0f,0.0f);
//Horizontal line
glVertex3f(-0.9,-0.6,0.0);
glVertex3f(-0.7,-0.6,0.0);

glEnd();
   //drawing a Quadrilateral
   glBegin(GL_QUADS);
   glColor3f(0.0f,0.0f,1.0f);
   glVertex3f(0.6,0.5,0.0);
   glVertex3f(0.9,0.5,0.0);
   glVertex3f(0.8,0.8,0.0);
   glVertex3f(0.7,0.8,0.0);
   glEnd();
   //drawing a point
       glBegin(GL_POINTS);
       glPointSize(4.0f);
       glColor3f(1.0f,1.0f,1.0f);
       glVertex3f(-0.9,-0.9,0.0);
       glEnd();

   //drawing a Hexagon
       glBegin(GL_POLYGON);
       glColor3f(0.0f,1.0f,0.0f);
       glVertex3f(0.6,-0.3,0.0);
       glVertex3f(0.4,-0.4,0.0);
       glVertex3f(0.4,-0.6,0.0);
       glVertex3f(0.6,-0.7,0.0);
       glVertex3f(0.8,-0.6,0.0);
       glVertex3f(0.8,-0.4,0.0);
       glEnd();

       glFlush();
}

void Cube::rotate(int val)
{
    for(int i=0;i<val;i++)
    {
        rotationX+=0.8f;
        rotationY+=0.8f;
        rotationZ+=0.8f;
        paintGL();
        updateGL();

    }
}

void Cube::Scale(int val)
{
    if((sx<val)&&(sy<val)&&(sz<val))
    {
        sx += val;
        sy+= val;
        sz += val;
    }
    else if((sx>val)&&(sy>val)&&(sz>val))
    {
        sx -=val;
        sy-= val;
        sz -= val;
    }
    else
    {
        sx =val;
        sy= val;
        sz = val;
    }
    paintGL();
    updateGL();
}

void Cube::orient(char scene)
{
    switch(scene)
    {
    case 'p':
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0,0,400,500);
        paintGL();
        break;
    case 'l':
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0,0,500,400);
        paintGL();
        break;
    default:
        break;
    }
}
