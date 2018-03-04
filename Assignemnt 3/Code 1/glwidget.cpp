#include "glwidget.h"

#include<math.h>

#include<QtGui>
#include<QtOpenGL>
glwidget::glwidget(QWidget *parent):QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{

}

void glwidget::initializeGL()
{
    qglClearColor(Qt::black);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_SCISSOR_TEST);
}

void glwidget::resizeGL(int width, int height)
{
    //if(width>height)
        glViewport(0,0,height/2,width/2);
        glScissor(0,0,width,height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    //else
//        glViewport(0,(height-width)/2,width,width);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
}

void glwidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    switch(scene)
    {
    case 'p':
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0,0,400,500);
        draw();
        glFlush();
        break;
    case 'l':
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0,0,500,400);
        draw();
        glFlush();
        break;
    default:
        break;
    }
}

void glwidget::draw()
{

    //drawing a point
    glBegin(GL_POINTS);
    glPointSize(4.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(-0.9,0.8,0.0);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(-0.85,0.8,0.0);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex3f(-0.8,0.8,0.0);
    glEnd();

    //drawing a line
    glBegin(GL_LINES);
    glLineWidth(2.0f);
    glColor3f(1.0f,1.0f,0.0f);
    //Horizontal line
    glVertex3f(-0.9,0.6,0.0);
    glVertex3f(-0.7,0.6,0.0);
    //Vertical line
    glVertex3f(-0.6,0.6,0.0);
    glVertex3f(-0.6,0.8,0.0);
    glEnd();

    //drawing a triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.3,0.5,0.0);
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(-0.3,0.5,0.0);
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0,0.8,0.0);
    glEnd();

    //drawing a Quadrilateral
    glBegin(GL_QUADS);
    glColor3f(0.0f,1.0f,1.0f);
    glVertex3f(0.6,0.5,0.0);
    glVertex3f(0.9,0.5,0.0);
    glVertex3f(0.8,0.8,0.0);
    glVertex3f(0.7,0.8,0.0);
    glEnd();
    //drawing a cube

    static const GLfloat coords[6][4][3]= {
            {{-0.3,-0.3,0.3},{-0.3,-0.3,-0.7},{-0.7,-0.3,-0.7},{-0.7,-0.3,0.3}},
            {{-0.3,-0.3,-0.7},
             {-0.3,-0.7,-0.7},
             {-0.7,-0.7,-0.7},
             {-0.7,-0.3,-0.7}},
            {{-0.3,-0.3,0.3},
             {-0.3,-0.7,0.3},
             {-0.3,-0.7,-0.7},
             {-0.3,-0.3,-0.7}},
            {{-0.3,-0.3,0.3},
             {-0.3,-0.7,0.3},
             {-0.7,-0.7,0.3},
             {-0.7,-0.3,0.3}},
            {{-0.7,-0.3,0.3},
             {-0.7,-0.7,0.3},
             {-0.7,-0.7,-0.7},
             {-0.7,-0.3,-0.7}},
            {{-0.3,-0.7,0.3},
             {-0.3,-0.7,-0.7},
             {-0.7,-0.7,-0.7},
             {-0.7,-0.7,0.3}}
        };

        faceColors[0]=Qt::red;
        faceColors[1]=Qt::green;
        faceColors[2]=Qt::blue;
        faceColors[3]=Qt::magenta;
        faceColors[4]=Qt::yellow;
        faceColors[5]=Qt::cyan;

    for(int i=0;i<6;++i)
    {
        glLoadName(i);
        glBegin(GL_QUADS);
        qglColor(faceColors[i]);
        for(int j=0;j<4;++j)
        {
            glVertex3f(coords[i][j][0],coords[i][j][1],coords[i][j][2]);
        }
        glEnd();
    }

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

 //   glFlush();
}

